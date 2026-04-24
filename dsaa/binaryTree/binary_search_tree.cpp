/*
二叉树的中序遍历遵循“左<根<右”的遍历顺序，而二叉搜索树满足“左子节点<根节点<右子节点”的大小关系。
这意味着在二叉搜索树中进行中序遍历时，总是会优先遍历下一个最小节点，从而得出一个重要性质：二叉搜索树的中序遍历序列是升序的。
*/
#include <iostream>
#include <vector>
using namespace std;

struct Treenode {
    int val;
    Treenode* left;
    Treenode* right;
    Treenode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    Treenode* root;

    // 辅助方法：中序遍历打印
    void inOrderPrint(Treenode* node) {
        if (node == nullptr) return;
        inOrderPrint(node->left);
        cout << node->val << " ";
        inOrderPrint(node->right);
    }

    void destroyTree(Treenode* node){
        if(node == nullptr) return; //递归终止条件
        //摧毁左子树
        destroyTree(node->left);
        //摧毁右子树
        destroyTree(node->right);

        delete node;
    }
public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() {
        destroyTree(root);
        root = nullptr;
        cout << "Binary Tree completely destroyes." << endl;
    }

    // 打印整棵树（中序）
    void printTree() {
        cout << "In-Order Traversal: ";
        inOrderPrint(root);
        cout << endl;
    }

    //获取二叉树根节点
    Treenode* getRoot(){
        return root;
    }

    //查找节点
    Treenode* search(int num){
        Treenode* cur = root;
        while(cur != nullptr){
            if(cur->val < num){
                cur = cur->right;
            }else if(cur->val > num){
                cur = cur->left;
            }else{
                break;
            }
        }
        return cur;
    }

    //插入节点
    void insert(int num) {
        if(root == nullptr) {
            root = new Treenode(num);
            return;
        }
        Treenode *cur = root, *pre = nullptr;
        // 循环查找，越过叶节点后跳出
        while(cur != nullptr){
            if(cur->val > num){
                pre = cur;
                cur = cur->left;
            }else if(cur->val < num){
                pre = cur;
                cur = cur->right;
            }else{
                return;
            }
        }
        //插入
        Treenode *node = new Treenode(num);
        if(pre->val < num){
            pre->right = node;
        }else{
            pre->right = node;
        }
    }

    //删除节点
    void remove(int num){
        if(root == nullptr) return;
        Treenode *cur = root, *pre = nullptr;
        while(cur != nullptr){
            if(cur->val == num){
                break;
            }else if(cur->val < num){
                pre = cur;
                cur = cur->right;
            }else{
                pre = cur;
                cur = cur->left;
            }
        }
        //未找到直接返回
        if(cur == nullptr) {
            return;
        }
        //判断cur子节点数
        //(1)子节点数为0或1
        if(cur->left == nullptr || cur->right == nullptr){
            Treenode *child = cur->left == nullptr ? cur->right : cur->left;
            if(cur != root) {
                if(pre->right == cur){
                    pre->right = child;
                }else{
                    pre->left = child;
                }
            }else{
                root = child;
            }
            delete cur;
        }
        //(2)子节点数为2
        /*
        当待删除节点的度为2时，我们无法直接删除它，而需要使用一个节点替换该节点。
        由于要保持二叉搜索树“左子树<根节点<右子树”的性质，因此这个节点可以是右子树的最小节点或左子树的最大节点。
        假设选择右子树的最小节点（中序遍历的下一个节点）
        */
        else{
            Treenode *tmp = cur->right;
            while(tmp->left != nullptr){
                tmp = tmp->left;
            }
            int tmpVal = tmp->val;
            //delete tmp; 错！！！tmp只是左子树为空，右子树为知，所以使用递归删除tmp
            remove(tmpVal);
            //用tmp覆盖cur
            cur->val = tmpVal;
        }
    }
};

/* --- Driver Code (测试驱动程序) --- */
int main() {
    BinarySearchTree bst;

    cout << "--- 1. Testing Insertion ---" << endl;
    // 构建一棵 BST：
    //       50
    //     /    \
    //   30      70
    //  /  \    /  \
    // 20  40  60  80
    int nodes[] = {50, 30, 70, 20, 40, 60, 80};
    for (int num : nodes) {
        bst.insert(num);
    }
    bst.printTree(); // 预期输出有序序列：20 30 40 50 60 70 80

    cout << "\n--- 2. Testing Search ---" << endl;
    Treenode* found = bst.search(40);
    if (found) cout << "Node 40 found!" << endl;
    else cout << "Node 40 NOT found!" << endl;

    cout << "\n--- 3. Testing Deletion (Degree 0 - Leaf Node) ---" << endl;
    cout << "Deleting 20..." << endl;
    bst.remove(20);
    bst.printTree(); // 预期：20 消失

    cout << "\n--- 4. Testing Deletion (Degree 1) ---" << endl;
    // 先插入一个 35 制造度为 1 的节点 (30 的右子树现在只有 40，再在 40 左边挂 35)
    bst.insert(35);
    cout << "Inserted 35. Deleting 40 (which has one child 35)..." << endl;
    bst.remove(40);
    bst.printTree(); // 预期：40 消失，35 正常连接

    cout << "\n--- 5. Testing Deletion (Degree 2 - Root Node) ---" << endl;
    cout << "Deleting root 50..." << endl;
    bst.remove(50);
    bst.printTree(); // 预期：右子树最小节点 60 将上位替换 50

    // 程序结束，触发析构函数自动清理内存
    return 0;
}
