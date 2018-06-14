/*
 * @Author: jiangzhe 
 * @Date: 2018-06-13 06:10:27 
 * @Last Modified by: jiangzhe
 * @Last Modified time: 2018-06-13 18:20:57
 */


#ifndef SKIPLIST_HPP
#define SKIPLIST_HPP

#include "random.hpp"

#include <assert.h>
#include <limits.h>

#include <string>
#include <iostream>
#include <memory>

#define DEBUG

namespace skiplist{

    const int MAX_LEVEL = 16;

    using KeyType = int;
    using ValueType = int;

    //每个节点的结构
    struct node
    {
        KeyType key;
        ValueType  value;
        node* next[1];
        //该指针指向了下一个
    };

    
    struct listHead
    {
        //level表示当前表使用的最大的层数
        int level;
        node*  header;
        //指向了第一个节点.第一个节点是满层,即最大层MAX_LEVEL的节点
    };

    class skipList
    {
        public:
            skipList():size_(0), rnd_(0x7fffffffu)
            {
                newList();
            };
            ~skipList(){freeList();};
            
            //这里搜索key,并且返回value,如果找到就返回true
            bool Search(const KeyType& key, ValueType& value);
            bool Insert(const KeyType& key, const ValueType& value);
            bool Delete(const KeyType& key, const ValueType& value);

            //返回当前跳表的节点的个数
            size_t size(){return size_;}

        private:
            void newList();

            void freeList();

            void newNodeWithLevel(node** nodePtr_, const int& level);
        
            int randomLevel();        

        private:
            //跳表的头和尾
            listHead* list_;
            node* NIL_;
            //链表中包含的节点的数目
            size_t size_;
            leveldb::Random rnd_;
    };

}

#endif