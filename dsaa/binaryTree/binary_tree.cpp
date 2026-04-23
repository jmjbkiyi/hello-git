#include <iostream>

using namespace std;

sturct  Treenode {
    int val;
    Treenode *left;
    Treenode *right;
    Treenode (int x) : val(x), left(nullptr), right(nullptr) {}
};

int main(){
    Treenode* n1 = new Treenode(1);
    Treenode* n2 = new Treenode(2);
    Treenode* n3 = new Treenode(3);
    Treenode* n4 = new Treenode(4);
    Treenode* n5 = new Treenode(5);

    //初始化二叉树
    n1->left = n2;
    n1->right = n3;
    n2->left = n4;
    n2->right = n5;

    /*插入与删除节点*/
    Treenode* P = new Treenode(0);
    /*在n1 n2间插入P*/
    n1->left = P;
    P->left = n2;
    /*删除节点P*/
    n1->left = n2;
    delete P;

    return 0;
}
