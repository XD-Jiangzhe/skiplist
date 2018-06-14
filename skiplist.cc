/*
 * @Author: jiangzhe 
 * @Date: 2018-06-13 08:21:53 
 * @Last Modified by: jiangzhe
 * @Last Modified time: 2018-06-13 18:53:28
 */


#include "skiplist.hpp"


namespace skiplist
{
    void Debug(const std::string& infomation)
    {
        std::cout<<infomation<<std::endl;
    }

    void skipList::newNodeWithLevel(node** nodePtr_, const int& level)
    {
        //这里占用的数据结构是
        /* -------->node*
            node*-->node*
            node*-->node*
            node--->node
        */
        int totalSize = sizeof(node)+level*(sizeof(node*));
        assert(sizeof(node*) == 8);
        
        *nodePtr_  = (node*)malloc(totalSize);
        assert((*nodePtr_) != nullptr);
    }

    void skipList::newList()
    {
        //初始化尾节点
        newNodeWithLevel(&NIL_, 0);
        NIL_->key = INT_MAX;
        
        //设置链表的头
        list_ = (listHead*)malloc(sizeof(listHead));
        list_->level = 0;
        //这里的层数指的是当前跳表中的最高的层数,不包括head

        //头部有最高的层数,将头结点的所有指向都指向了NIL_最后的节点
        newNodeWithLevel(&(list_->header), MAX_LEVEL);
        for(int i=0; i<MAX_LEVEL; ++i)
        {
            list_->header->next[i] = NIL_;
        }

    }

    void skipList::freeList()
    {
        node* p = list_->header;
        node* q;
        while(p!= NIL_)
        {
            q = p->next[0];
            free(p);
            p = q;
        }
        free(p);
        free(list_);
    }

    bool skipList::Search(const KeyType& key,ValueType& value)
    {
        node* start = list_->header;
        int i;

    /*
        从当前记录的最高层往下进行搜索
        如果高层搜索不到,就往下退一格继续搜索下一个
        直到查到跳一格的时候,那么下一个就一定是key
        要不然就是下一个是比k大的数,而非等于key的数

        这里可以进行优化,即如果当前值就是key,就可以直接退出
        从而防止后面的空查找
    */
        for(i=list_->level; i>=0; --i)
        {
            //当前层一直往前走
            while(start->next[i]->key < key)
            {
                start = start->next[i];
            }
        }
        start = start->next[0];
        if(start->key == key)
        {
            value = start->value;
            return true;
        }
        else 
        return false;
    }

    bool skipList::Insert(const KeyType& key, const ValueType& value)
    {
        node* update[MAX_LEVEL];
        node* start = list_->header;
        
        int i;
        for(i=list_->level; i>=0; --i)
        {
            while(start->next[i]->key < key)
            {
                start = start->next[i];
            }
        /*
            每往下一层,这里就填入了update[]的相应的位置,即当前节点的下一跳要比key大
            也就是新加入的节点可能会将这update数组中的节点给截断掉的位置
        */
       /*
            next[2]--->
            next[1]--->
            start       start->next[0]
        所以这里存放的start,因为start可以找到它的next
       */
            update[i] = start;
        }

        start = start->next[0];
        if(start->key == key)
        {
            //已经存在了
            start->value = value;
            return false;
        }

        int level = randomLevel();
        //如果随机出来的比当前最大的还要高,就比它高一层
        //将记录的最高的层数+1
        //并且前一层是链表头,因为这是第一层
        if(level > list_->level)
        {
            level = ++list_->level;
            update[level] = list_->header;
        }

        node* newnode;
        newNodeWithLevel(&newnode, level);
        newnode->key = key;
        newnode->value = value;

        for(int i=level; i>=0; --i)
        {
            /*
            从随机产生的level层往下走,改变每个之前存放的start的每一层的下一个
            update   newnode   newnode->next
            */
            start = update[i];
            newnode->next[i] = start->next[i];
            start->next[i] = newnode;
        }
        ++size_;
        return true;
    }

    bool skipList::Delete(const KeyType& key, const ValueType& value)
    {
        node* update[MAX_LEVEL];
        node* start = list_->header;
        
        int i;
        for(i=list_->level; i>=0; --i)
        {
            while(start->next[i]->key < key)
            {
                start = start->next[i];
            }
            update[i] = start;
        }
        start = start->next[0];
        if(start->key != key)
        {
            Debug("cannot find the key "+std::to_string(key));
            return false;
        }
        else 
        {
            //从下往上去找这个节点有几层
            for(int i=0; i<list_->level; ++i)
            {
                if(update[i]->next[i] != start)
                    break;
                //如果有该层,则直接将next指向key对应的next
                update[i]->next[i] = start->next[i];
            }
            free(start);

            /*
                这里更新该跳表的最高的层数
                如果最高层的下一跳就是最后的节点,则将当前的层数-1
                直到减到当前的层数
            */
            while(list_->level > 0
                && list_->header->next[list_->level] == NIL_)
                --list_->level;
            
            --size_;
            return true;
        }
    }

    int skipList::randomLevel()
    {
        //level 范围是 0 - MAX_LEVEL-1
        int level = static_cast<int>(rnd_.Uniform(MAX_LEVEL));
        if(level == 0)
            level =1;

        // Debug(std::to_string(level));
        return level;
    }

}

