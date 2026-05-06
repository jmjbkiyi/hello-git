#include <iostream>
#include <vector>
#include <string>
#include <utility>
using namespace std;

struct Pair{
    int key;
    string val;
    Pair(int key, string val){
        this->key = key;
        this->val = val;
    } 
};

class HashMapOpenAddressing {
private:
    int size;
    int capacity = 4;
    const double loadThres = 2.0 / 3.0;
    const int extendRatio = 2;
    vector<Pair*> buckets;
    Pair *TOMBSTONE = new Pair(-1,"-1");  // 删除标记
public:
    HashMapOpenAddressing() : size(0), buckets(capacity,nullptr) {}
    ~HashMapOpenAddressing() {
        for(Pair *pair : buckets) {
            if(pair != nullptr && pair != TOMBSTONE){
                delete pair;
            }
        }
        delete TOMBSTONE;
    }
    
    /* 哈希函数 */
    int hashFunc(int key) {
        return key % capacity;
    }

    /* 负载因子 */
    double loadFactor() {
        return (double)size / capacity;
    }
    
    /* 扩容哈希表 */
    void extend(){
        vector<Pair*> tmp = buckets;
        capacity *= extendRatio;
        buckets = vector<Pair*>(capacity,nullptr);
        size = 0;
        for(Pair *&pair : tmp){
            if(pair != nullptr && pair != TOMBSTONE){
                put(pair->key, pair->val);
                delete pair;
            }
        }
    }
    
    /* 搜索 key 对应的桶索引 */
    int findBucket(int key){
        int index = hashFunc(key);
        int firstTombstone = -1;
        // 线性探测，当遇到空桶时跳出
        while(buckets[index] != nullptr){
            // 若遇到 key ，返回对应的桶索引
            if(buckets[index]->key == key){
                // 若之前遇到了删除标记，则将键值对移动至该索引处
                if(firstTombstone != -1) {
                    buckets[firstTombstone] = buckets[index];
                    buckets[index] = TOMBSTONE;
                    return firstTombstone;
                }
                return index;
            }
            // 记录遇到的首个删除标记
            if(firstTombstone == -1 && buckets[index] == TOMBSTONE) {
                firstTombstone = index;
            }
            // 计算桶索引，越过尾部则返回头部
            index = (index + 1) % capacity;
        }
        // 若 key 不存在，则返回添加点的索引
        return firstTombstone == -1 ? index : firstTombstone;
    }
    
    /* 添加操作 */
    void put(int key, string val){
        if(loadFactor() > loadThres){
            extend();
        }
        int index = findBucket(key);
        // 若找到键值对，则覆盖 val 并返回
        if(buckets[index] != nullptr && buckets[index] != TOMBSTONE){
            buckets[index]->val = val;
            return;
        }
        // 若键值对不存在，则添加该键值对
        buckets[index] = new Pair(key,val);
        size++;
    }
    
    /* 删除操作 */
    void remove(int key){
        int index = findBucket(key);
        // 若找到键值对，则用删除标记覆盖它
        if(buckets[index] != nullptr && buckets[index] != TOMBSTONE){
            delete buckets[index];
            buckets[index] = TOMBSTONE;
            size--;
        }
    }
    
    /* 打印哈希表 */
    void print(){
        for(Pair *pair : buckets){
            if(pair == nullptr){
                cout << "nullptr" << endl;
            }else if(pair == TOMBSTONE){
                cout << "TOMBSTONE" << endl;
            }else{
                cout << pair->key << " -> " << pair->val << endl;
            }
        }
    }
};

/* --- Driver Code --- */
int main() {
    HashMapOpenAddressing map;

    cout << "=== 测试 1：初始状态与线性探测 ===" << endl;
    // 初始容量 4，插入前两个元素不引发扩容
    map.put(1, "Apple");
    // hash(5) = 1，产生冲突！会向后线性探测放入索引 2
    map.put(5, "Banana"); 
    map.print();

    cout << "\n=== 测试 2：触发 TOMBSTONE 懒惰删除 ===" << endl;
    // 删除 key = 1 的元素，索引 1 处应该变为 TOMBSTONE
    map.remove(1);
    map.print();

    cout << "\n=== 测试 3：TOMBSTONE 的重用与路径压缩 ===" << endl;
    // 再次查询 key = 5 的元素，findBucket 发现前面有 TOMBSTONE，
    // 应该会把 Banana 挪到前面的 TOMBSTONE 位置上！
    map.put(5, "Banana_Updated"); // 执行 put 内部会调用 findBucket
    map.print();

    cout << "\n=== 测试 4：触发扩容机制 ===" << endl;
    // 当前 size = 1，容量 4。继续插入引发扩容 (loadFactor > 0.66)
    map.put(2, "Cherry");
    map.put(6, "Date");
    map.put(10, "Eggplant"); // 插入第 4 个元素，必然突破阈值，发生扩容！
    
    // 扩容后，所有的 TOMBSTONE 会被彻底清理，元素重新落位
    map.print();

    return 0;
}


