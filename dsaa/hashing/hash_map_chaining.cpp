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

class HashMapChaining{
private:
    int size;                        // 键值对数量
    int capacity;                    // 哈希表容量
    double loadThres;                // 触发扩容的负载因子阈值
    int extendRatio;                 // 扩容倍数
    vector<vector<Pair*>> buckets;   // 桶数组
public:
    HashMapChaining() : size(0), capacity(4), loadThres(2.0/3.0), extendRatio(2) {
        buckets.resize(capacity);
    }
    
    ~HashMapChaining(){
        for(auto &bucket : buckets){
            for(Pair *pair : bucket){
                delete pair;
            }
            vector<Pair*>().swap(bucket);
        }
        vector<vector<Pair*>>().swap(buckets);
    }
    
    /* 哈希函数 */
    int hashFunc(int key){
        return key % capacity;
    }
    
    /* 负载因子 */
    double loadFactor(){
        return (double)size / (double)capacity;
    }
    
    /* 扩容哈希表 */
    void extend(){
        vector<vector<Pair*>> tmp = buckets;
        capacity *= extendRatio;
        buckets.clear();
        buckets.resize(capacity);
        size = 0;
        for(auto &bucket : tmp){
            for(Pair *pair : bucket){
                put(pair->key, pair->val);
                delete pair;
            }
        }
    }
    
    /* 查询操作 */
    string get(int key){
        int index = hashFunc(key);
        for(Pair *pair : buckets[index]){
            if(pair->key == key){
                return pair->val;
            }
        }
        // 若未找到 key ，则返回空字符串
        return "";
    }
    
    /* 添加操作 */
    void put(int key, string val){
        // 当负载因子超过阈值时，执行扩容
        if(loadFactor() > loadThres){
            extend();
        }
        int index = hashFunc(key);
        // 遍历桶，若遇到指定 key ，则更新对应 val 并返回
        for(Pair *pair : buckets[index]){
            if(pair->key == key){
                pair->val = val;
                return;
            }
        }
        // 若无该 key ，则将键值对添加至尾部
        buckets[index].push_back(new Pair(key,val));
        size++;
    }
    
    /* 删除操作 */
    void remove(int key){
        int index = hashFunc(key);
        auto &bucket = buckets[index];
        for(int i = 0;i < bucket.size();i++){
            if(bucket[i]->key == key){
                Pair *tmp = bucket[i];
                bucket.erase(bucket.begin() + i);
                delete tmp;
                size--;
                return;
            }
        }
    }
    
    /* 打印哈希表 */
    void print(){
        for(auto &bucket : buckets){
            cout << "[" ;
            for(Pair *pair : bucket){
                cout << pair->key << " -> " << pair->val << ", " ;
            }
            cout << "\b\b  \b\b]\n" ;
        }
    }
};

/* --- Driver Code --- */
int main() {
    HashMapChaining map;
    
    cout << "=== 测试 1：初始状态插入元素 ===" << endl;
    // 初始 capacity=4, loadThres=0.66, 插入第 3 个元素时触发扩容 (3/4 = 0.75 > 0.66)
    map.put(1, "Alan");
    map.put(2, "Bob");
    map.print();

    cout << "\n=== 测试 2：插入第 3 个元素，预期触发扩容 ===" << endl;
    map.put(3, "Charlie"); 
    map.print();

    cout << "\n=== 测试 3：哈希冲突与链表追加 ===" << endl;
    // 当前 capacity=8，hashFunc(11) = 3，hashFunc(3) = 3，这两个会挤在同一个桶里！
    map.put(11, "David"); 
    map.print();

    cout << "\n=== 测试 4：元素更新 (Update) ===" << endl;
    map.put(1, "Alan_Updated");
    map.print();

    cout << "\n=== 测试 5：删除元素 (Remove) ===" << endl;
    map.remove(3); // 删掉 3 之后，桶里的 11 会成为该桶唯一的元素
    map.print();

    return 0;
}