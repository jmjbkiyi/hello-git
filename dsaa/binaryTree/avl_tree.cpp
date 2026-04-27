//难点：rotate 里的旋转判断条件
#include <iostream>
using namespace std;

struct Treenode{
    int val{};
    int height{};
    Treenode *left{};
    Treenode *right{};
    Treenode() = default;
    explicit Treenode(int x) : val(x) {}
};

class AVLTree {
private:
    void destroy(Treenode *node){
      if(node == nullptr) return;
      
      destroy(node->left);
      destroy(node->right);
      
      delete node;
    }
    //update tree height
    void updateHeight(Treenode* node){
        node->height = max(height(node->left), height(node->right)) + 1;
    }
    
    Treenode* leftRotate(Treenode *node){
        Treenode *child = node->right;
        Treenode *grandchild = child->left;
        
        child->left = node;
        node->right = grandchild;
        
        updateHeight(node);
        updateHeight(child);
        
        return child;
    }
    
    Treenode* rightRotate(Treenode *node){
        Treenode *child = node->left;
        Treenode *grandchild = child->right;
        
        child->right = node;
        node->left = grandchild;
        
        updateHeight(node);
        updateHeight(child);
        
        return child;
    }
    
    Treenode* rotate(Treenode *node){
        int _balanceFactor = balanceFactor(node);
        if(_balanceFactor > 1){
            if(balanceFactor(node->left) < 0){
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }else{
                return rightRotate(node);
            }
        }else if(_balanceFactor < -1){
            if(balanceFactor(node->right) > 0) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }else{
                return leftRotate(node);
            }
        }
        return node;
    }
    
    Treenode* insertHelper(Treenode *node,int val){
        if(node == nullptr){
            return new Treenode(val);
        }
        if(node->val == val){
             return node;
         }else if(node->val > val){
            node->left = insertHelper(node->left,val);
        }else{
            node->right = insertHelper(node->right,val);  
        }
        updateHeight(node);
        node = rotate(node);
        return node;
    }
    
    Treenode* removeHelper(Treenode *node,int val){
        if(node == nullptr) return nullptr;
        
        if(node->val >val){
            node->left = removeHelper(node->left,val);
        }else if(node->val < val){
            node->right = removeHelper(node->right,val);
        }else{
            if(node->left == nullptr || node->right == nullptr){
                Treenode *child = node->left == nullptr ? node->right : node->left;
                if(child == nullptr){
                    delete node;
                    return nullptr;
                }else{
                    delete node;
                    node = child;
                    return node;
                }
            }else{
                Treenode *tmp = node->right;
                while(tmp->left != nullptr){
                    tmp = tmp->left;
                }
                int tmpVal = tmp->val;
                node->right = removeHelper(node->right,tmpVal);
                node->val = tmpVal;
            }
        }
        updateHeight(node);
        node = rotate(node);
        return node;
    }
    
    // 辅助方法：中序遍历打印
    void inOrderPrint(Treenode* node) {
        if (node == nullptr) return;
        inOrderPrint(node->left);
        cout << node->val << " ";
        inOrderPrint(node->right);
    }
        
public:
    Treenode *root;
    
    AVLTree() : root(nullptr) {}
    ~AVLTree() {
      destroy(root);
      root = nullptr;
      cout << "AVLTree completely destroyes." << endl;
    }
    
    void printTree() {
        cout << "In-Order Traversal: ";
        inOrderPrint(root);
        cout << endl;
    }

    
    int height(Treenode *node){
        //// 空节点高度为 -1 ，叶节点高度为 0
        return node == nullptr ? -1 : node->height;
    }
    
    int balanceFactor(Treenode *node){
        if(node == nullptr) return 0;
        return height(node->left) - height(node->right);
    }
    
    void insert(int val){
        root = insertHelper(root,val);
    }
    
    void remove(int val){
        root = removeHelper(root,val);
    }
    
    Treenode* search(int val){
        Treenode *cur = root;
        while(cur != nullptr){
            if(cur->val > val){
                cur = cur->left;
            }else if(cur->val <val){
                cur = cur->right;
            }else{
                break;
            }
        }
        return cur;
    }
};

/* --- Driver Code --- */
int main() {
    AVLTree avl;

    cout << "--- 1. Testing Insertions (Triggering Rotations) ---" << endl;
    // 插入 10, 20, 30 触发 RR 单旋 (Left Rotate)
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    cout << "After 10, 20, 30 (Expected root 20):" << endl;
    avl.printTree();

    // 插入 40, 50 继续触发 RR 单旋
    avl.insert(40);
    avl.insert(50);
    cout << "After 40, 50:" << endl;
    avl.printTree();

    // 插入 25 触发 RL 双旋 (Right-Left Rotate)
    avl.insert(25);
    cout << "After inserting 25 (RL case):" << endl;
    avl.printTree();

    cout << "\n--- 2. Testing Search ---" << endl;
    Treenode* found = avl.search(25);
    if (found) cout << "Node 25 successfully found!" << endl;
    else cout << "Node 25 NOT found!" << endl;

    cout << "\n--- 3. Testing Deletions (Maintaining Balance) ---" << endl;
    cout << "Deleting 40 (Degree 0/1)..." << endl;
    avl.remove(40);
    avl.printTree();

    cout << "Deleting 20 (Degree 2, Root)..." << endl;
    avl.remove(20);
    avl.printTree();

    cout << "\n--- 4. Exiting Program (Triggering Destructor) ---" << endl;
    return 0;
}
