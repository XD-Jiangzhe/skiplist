/*
 * @Author: jiangzhe 
 * @Date: 2018-06-13 06:09:13 
 * @Last Modified by: jiangzhe
 * @Last Modified time: 2018-06-13 18:20:03
 */


#include "random.hpp"
#include "skiplist.hpp"

#include <iostream>
#include <string>
#include <memory>

using namespace std;
using namespace leveldb;
using namespace skiplist;

int const testnumber = 300;

int main(int argc, char const *argv[])
{
    skipList skiplist_;
    
    for(int i=0; i < testnumber; ++i)
    {
        skiplist_.Insert(i, i+10);
    }
    cout<<skiplist_.size()<<endl;
    
    bool isSearchSuccess = true; 
    for(int i=0; i<testnumber; ++i)
    {
        int value;
        if(!skiplist_.Search(i, value) || value!= i+10)
        {
            isSearchSuccess = false;
            break;
        }
        // cout<<value<<endl;
    }
    if(!isSearchSuccess)
        cout<<"failed"<<endl;
    else 
        cout<<"search success"<<endl;

    int s = 200;
    cout<< (skiplist_.Search(testnumber+1, s) ? "true" : "false")<<endl;

    bool isDeleteSuccess = true;
    for(int i=0; i<testnumber; ++i)
    {
        int  value ;
        if(!skiplist_.Delete(i, i+10))
        {
            isDeleteSuccess = false;
            break;
        }
    }
    cout<<"skiplist size: "<<skiplist_.size()<<endl;
    
    if(!isDeleteSuccess)
        cout<<"delete fail"<<endl;
    else 
        cout<<"delete success"<<endl;



    return 0;
}
