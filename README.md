# skiplist的实现  

##使用方法
make   

##定义的接口
namespace skiplst  
class skipList  
bool Search(const KeyType& key, ValueType& value);  
bool Insert(const KeyType& key, const ValueType& value);  
bool Delete(const KeyType& key, const ValueType& value);  
size_t size(){return size_;}

##测试代码  
skiptest.cc  
##随机数生成式从leveldb中扒下来的
