#include <iostream>
#include <vector>
using namespace std;

struct Treenode {
    int val;
    Treenode* left;
    Treenode* right;
    Treenode(int x) : val(x), left(nullptr), right(nullptr) {}
};

    vector<int> vec;
/*前序遍历*/
void preOrder(Treenode* root){
    if(root == nullptr) return;

    vec.push_back(root->val);
    preOrder(root->left);
    preOrder(root->right);
}
/*中序遍历*/
void inOrder(Treenode* root){
    if(root == nullptr) return;

    inOrder(root->left);
    vec.push_back(root->val);
    inOrder(root->right);
}
/*后序遍历*/
void postOrder(Treenode* root){
    if(root == nullptr) return;

    postOrder(root->left);
    postOrder(root->right);
    vec.push_back(root->val);
}

// 辅助函数：打印 vector 内容并清空
void printResult(string title) {
    cout << title << ": ";
    for (int v : vec) {
        cout << v << " ";
    }
    cout << endl;
    vec.clear(); // 清空全局变量，方便下次遍历
}

// --- Driver Code ---
int main() {
    /* 构建树结构：
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

    // 1. 测试前序
    preOrder(root);
    printResult("前序遍历 (Pre-order)");

    // 2. 测试中序
    inOrder(root);
    printResult("中序遍历 (In-order)");

    // 3. 测试后序
    postOrder(root);
    printResult("后序遍历 (Post-order)");

    // 释放内存（建议养成习惯）
    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}
