#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

class ArrayBinaryTree {
public:
    ArrayBinaryTree(vector<int> arr){
      tree = arr;
    }
    int Size(){
      return tree.size();
    }
    int val(int i){
        if(i < 0 || i >= Size()) return INT_MAX;
        return tree[i];
    }
    
    int left(int i){
        return i * 2 + 1;
    }
    int right(int i){
        return i * 2 + 2;
    }
    int parent(int i){
        return (i-1) / 2;
    }
    
    vector<int> levelOrder(){
        vector<int> vec;
        for(int i=0;i < Size();i++){
            if(val(i) != INT_MAX){
                vec.push_back(val(i));
            }
        }
        return vec;
    }
    
    vector<int> preOrder(){
        vector<int> vec;
        dfs(0,"pre",vec);
        return vec;
    }
    
    vector<int> inOrder(){
        vector<int> vec;
        dfs(0,"in",vec);
        return vec;
    }
    
    vector<int> postOrder(){
        vector<int> vec;
        dfs(0,"post",vec);
        return vec;
    }
    
private:
    vector<int> tree;
    void dfs(int i, string order, vector<int>& vec){
        if(val(i) == INT_MAX) return;
        //preOrder
        if(order == "pre"){
            vec.push_back(val(i));
        }
        dfs(left(i),order,vec);
        //inOrder
        if(order == "in"){
            vec.push_back(val(i));
        }
        dfs(right(i),order,vec);
        //postOrder
        if(order == "post"){
            vec.push_back(val(i));
        }
    }
};

/* --- Driver Code --- */

// 辅助打印函数
void printVector(const string& name, const vector<int>& vec) {
    cout << name << ": ";
    for(int num : vec) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    /*
     * 构建一个数组表示的完全二叉树
     * 逻辑结构如下：
     * 1
     * /   \
     * 2     3
     * / \   / \
     * 4   5 6   7
     */
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
    
    // 我们也可以测试包含“空节点”的情况，用 INT_MAX 占位
    // 比如：vector<int> arr = {1, 2, 3, INT_MAX, 5, 6, INT_MAX};
    
    // 实例化 ArrayBinaryTree
    ArrayBinaryTree abt(arr);
    
    // 测试节点数量
    cout << "Tree Size: " << abt.Size() << "\n\n";
    
    // 测试层序遍历（对于无空节点的数组二叉树，层序遍历就是数组原貌）
    printVector("Level-Order", abt.levelOrder());
    
    // 测试深度优先遍历 (DFS) 的三种形态
    printVector("Pre-Order  ", abt.preOrder());
    printVector("In-Order   ", abt.inOrder());
    printVector("Post-Order ", abt.postOrder());

    return 0;
}