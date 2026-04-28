#include <iostream> 
#include <vector>
#include <utility>    //std::swap在此
using namespace std;

class MaxHeap {
private:
    vector<int> maxheap;

    int left(int i){
        return i * 2 + 1 ;
    }

    int right(int i) {
        return i * 2 + 2 ;
    }

    int parent(int i) {
        return (i-1) / 2 ; //向下整除
    }

    void siftUp(int i){
        while(true){
        int p = parent(i);
        //当越过根节点或节点无需修复时结束循环
        if(p < 0 || maxheap[p] >= maxheap[i]) break;
        //否则交换两节点并向上堆化
        swap(maxheap[p],maxheap[i]);
        i = p;
        }
    }

    void siftDown(int i){
        while(true){
            //判断节点l,r,i中最大节点
            int l = left(i), r = right(i), max = i;
            //细节小于size()，防止越界
            if(l < size() && maxheap[l] >= maxheap[i]){
                max = l;
            }
            if(r < size() && maxheap[r] >= maxheap[i]){
                max = r;
            }
            //如果节点i最大，或l和r越界，则结束循环
            if(max == i) break;

            swap(maxheap[i],maxheap[max]);
            i = max;
        }
    }

public:
    MaxHeap(vector<int> nums){
        maxheap = nums;
        /* 构造方法，根据输入列表建堆 */
        // 堆化除叶节点以外的其他所有节点
        /*太牛逼了，从i = parent(size() - 1)开始，精准的找到了最后一个非叶子结点*/
        for (int i = parent(size() - 1); i >= 0; i--) {
            siftDown(i);
        }
        /*这也是完全二叉树最神奇的物理定律之一：一棵完全二叉树，它的叶子节点数量，永远约等于总节点数量的一半。*/
        /*更精确的数学结论是：在一个大小为n的数组表示的完全二叉树中，所有索引大于(n-2)/2（也就是最后一个非叶子节点）的节点，全部都是叶子节点。*/
    }

    int size() {
        return maxheap.size();
    }

    bool isEmpty(){
        return size() == 0;
    }

    int peek() {
        return maxheap[0];
    }

    void push(int val){
        maxheap.push_back(val);
        //从底至顶堆化
        siftUp(size() - 1);
    }

    void pop() {
        //！！！判空！！！
        if(isEmpty == 0) {
            throw out_of_range("堆为空");
        }
        swap(maxheap[0], maxheap[size() - 1]);
        maxheap.pop_back();
        siftDown(0);
    }

    /*打印堆（以数组或是数形式）*/
    void print(){
        cout << "堆中内容为：" ;
        for(int i : maxheap){
            cout << i << " ";
        }
        cout << endl;
    } 
};