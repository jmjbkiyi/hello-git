#include <iostream>
#include <vector>
#include <queue>
using namespace std;

priority_queue<int, vector<int>, greater<int>> topKheap(vector<int> nums, int k){
    //初始化小顶堆
    priority_queue<int, vector<int> ,greater<int>> heap;

    //将前k个数推入堆
    for(int i=0;i<k;i++){
        heap.push(nums[i]);
    }

    // 从第 k+1 个元素开始，保持堆的长度为 k
    for(int i = k ; i < nums.size() ; i++){
        if(nums[i] > heap.top()){
            heap.pop();
            heap.push(nums[i]);
        }
    }

    return heap;
}

/* --- Driver Code --- */

// 辅助打印函数（按值传递，不会破坏原堆）
void printTopK(priority_queue<int, vector<int>, greater<int>> heap) {
    // 因为是小顶堆，直接 pop 出来的数据是从小到大的。
    // 如果我们想看“最大的 K 个数”，直接打印即可。
    vector<int> res;
    while (!heap.empty()) {
        res.push_back(heap.top());
        heap.pop();
    }
    
    // 为了更符合人类直觉，我们倒序遍历（从大到小打印）
    cout << "[ ";
    for (int i = res.size() - 1; i >= 0; i--) {
        cout << res[i] << (i == 0 ? "" : ", ");
    }
    cout << " ]" << endl;
}

int main() {
    cout << "=== Top-K 问题测试 ===" << endl;

    // 测试用例 1：常规无序数组
    vector<int> nums1 = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    int k1 = 3;
    cout << "\n测试数组 1: {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5}" << endl;
    cout << "寻找最大的 " << k1 << " 个数..." << endl;
    auto result1 = topKheap(nums1, k1);
    cout << "结果: ";
    printTopK(result1); // 预期输出: [ 9, 6, 5 ]

    // 测试用例 2：包含负数
    vector<int> nums2 = {-10, 5, 0, -3, 8, 12, 4};
    int k2 = 4;
    cout << "\n测试数组 2: {-10, 5, 0, -3, 8, 12, 4}" << endl;
    cout << "寻找最大的 " << k2 << " 个数..." << endl;
    auto result2 = topKheap(nums2, k2);
    cout << "结果: ";
    printTopK(result2); // 预期输出: [ 12, 8, 5, 4 ]

    // 测试用例 3：k 大于数组总长度的极端情况
    vector<int> nums3 = {10, 20};
    int k3 = 5;
    cout << "\n测试数组 3: {10, 20} (极端情况：K=" << k3 << ")" << endl;
    auto result3 = topKheap(nums3, k3);
    cout << "结果: ";
    printTopK(result3); // 预期输出: [ 20, 10 ]

    return 0;
}

