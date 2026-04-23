#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Treenode {
    int val;
    Treenode* left;
    Treenode* right;
    Treenode(int x) : val(x), left(nullptr), right(nullptr) {}
};

vector<int> levelOrder(Treenode* root){
    /*初始化列表，假如根节点*/
    queue<Treenode*> que;
    que.push(root);
    /*初始化一个数组，用来记录遍历序列*/
    vector<int> vec;

    while(!que.empty()){
        Treenode* node = que.front();
        que.pop();
        vec.push_back(node->val);
        if(node->left != nullptr){
            que.push(node->left);
        }
        if(node->right != nullptr){
            que.push(node->right);
        }
    }
    return vec;
}

/* Driver Code */
int main() {
    /* 构建一棵如下的二叉树:
             1
            / \
           2   3
          / \
         4   5
    */
    Treenode* root = new Treenode(1);
    root->left = new Treenode(2);
    root->right = new Treenode(3);
    root->left->left = new Treenode(4);
    root->left->right = new Treenode(5);

    cout << "开始层序遍历..." << endl;
    vector<int> result = levelOrder(root);

    // 打印结果
    cout << "遍历序列为: ";
    for (int v : result) {
        cout << v << " ";
    }
    cout << endl;

    // 提示：实际开发中记得 delete 释放内存
    // 这里为了简洁演示 Driver Code 逻辑，省略了手动回收 tree 的代码
    return 0;
}
