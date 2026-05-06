#include <iostream>
#include <vector>
#include <utility>
#include <string>
using namespace std;

/* 键值对 */
struct Pair{
   int key;
   string val;
   Pair(int key, string val){
      this->key = key;
      this->val = val;
   }
};

/* 基于数组实现的哈希表 */
class ArrayHashMap{
private:
    vector<Pair*> buckets;
public:
    ArrayHashMap(){
        // 初始化数组，包含 100 个桶
        buckets = vector<Pair*>(100);
    }
    
    ~ArrayHashMap(){
        for(const auto &bucket : buckets){
            delete bucket;
        }
        vector<Pair*>().swap(buckets);
    }
    
     /* 哈希函数 */
     int hashFunc(int key){
        int index = key % 100;
        return index;
     }
     
     /* 查询操作 */
     string getVal(int key){
        int index = hashFunc(key);
        Pair *pair = buckets[index];
        if(pair == nullptr){
            return "";
        }
        return pair->val;
     }
     
     /* 添加操作 */
     void put(int key, string val){
        Pair *pair = new Pair(key,val);
        int index = hashFunc(key);
        buckets[index] = pair;
     }
     
     /* 删除操作 */
     void remove(int key){
        int index = hashFunc(key);
        delete buckets[index];
        buckets[index] = nullptr;
     }
     
     /* 获取所有键值对 */
     vector<Pair*> pairSet(){
        vector<Pair*> pairSet;
        for(Pair *pair : buckets){
            if(pair != nullptr){
              pairSet.push_back(pair);
            }
        }
        return pairSet;
     }
     
     /* 获取所有键 */
     vector<int> keySet(){
        vector<int> keySet;
        for(Pair *pair : buckets){
          if(pair != nullptr){
              keySet.push_back(pair->key);
          }
        }
        return keySet;
     }
     
     /* 获取所有值 */
     vector<string> valSet(){
        vector<string> valSet;
        for(Pair *pair : buckets){
            if(pair != nullptr){
                valSet.push_back(pair->val);
            }
        }
        return valSet;
     }
     
     /* 打印哈希表 */
     void print(){
        for(Pair *pair : buckets){
          if(pair != nullptr){
              cout << pair->key << " -> " << pair->val << endl;
          }
        }
     }
};

/* --- Driver Code --- */
int main() {
    cout << "=== 初始化哈希表 ===" << endl;
    ArrayHashMap map;

    cout << "\n=== 测试 1：添加元素 (put) ===" << endl;
    map.put(1, "Apple");
    map.put(2, "Banana");
    map.put(103, "Cherry"); // 103 % 100 = 3，哈希值为 3
    map.print();

    cout << "\n=== 测试 2：更新元素 (覆盖旧指针测试) ===" << endl;
    map.put(1, "Avocado"); // 覆盖 Apple，此时旧的 Pair 内存被安全释放
    map.print();

    cout << "\n=== 测试 3：查询元素 (getVal) ===" << endl;
    cout << "Key 103 的值为: " << map.getVal(103) << endl;
    cout << "Key 99 的值为 (不存在): " << map.getVal(99) << endl;

    cout << "\n=== 测试 4：遍历键和值 (keySet / valSet) ===" << endl;
    cout << "所有的 Key: ";
    for (int k : map.keySet()) cout << k << " ";
    cout << "\n所有的 Value: ";
    for (string v : map.valSet()) cout << v << " ";
    cout << endl;

    cout << "\n=== 测试 5：删除元素 (remove) ===" << endl;
    cout << "删除 Key 2..." << endl;
    map.remove(2);
    map.print();

    cout << "\n=== 退出作用域，测试析构函数 ===" << endl;
    return 0;
}