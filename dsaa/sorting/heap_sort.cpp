#include <iostream>
#include <vector>
#include <algorithm> // For std::swap
using namespace std;

// Helper function to print a vector (consistent with other sorting files)
void printVector(const string& msg, const vector<int>& vec) {
    cout << msg;
    for (int num : vec) {
        cout << num << " ";
    }
    cout << endl;
}

void siftDown(vector<int> &vec, int n, int i){
    /* 堆的长度为 n ，从节点 i 开始，从顶至底堆化 */
    while(true){
        int l = i * 2 + 1;
        int r = i * 2 + 2;
        int max = i;
        if(l < n && vec[l] > vec[max]){ // Compare with current max, not original i
            max = l;
        }
        if(r < n && vec[r] > vec[max]){ // Compare with current max
            max = r;
        }
        // 若节点 i 最大或索引 l, r 越界，则无须继续堆化，跳出
        if(max == i){
            break;
        }
        swap(vec[i],vec[max]);
        i = max;
    }
}
void heapSort(vector<int> &nums){
    // 建堆操作：堆化除叶节点以外的其他所有节点
    for(int i=nums.size() / 2 - 1 ; i >= 0 ; i--){
        siftDown(nums,nums.size(),i);
    }
    // 从堆中提取最大元素，循环 n-1 轮
    for(int i = nums.size() - 1 ; i > 0 ; --i){
        // 交换根节点与最右叶节点（交换首元素与尾元素）
        swap(nums[0],nums[i]);
        // 以根节点为起点，从顶至底进行堆化
        siftDown(nums,i,0);
    }
}

int main() {
    // 打印堆排序的标题
    cout << "=== 堆排序 (Heap Sort) 测试 ===" << endl;

    // 测试用例 1: 常规无序数组
    // 预期结果: 1 1 2 3 4 5
    vector<int> nums1 = {4, 1, 3, 1, 5, 2};
    cout << "\n>>> 测试 1: 常规无序数组" << endl;
    printVector("排序前: ", nums1); // 打印原始数组
    heapSort(nums1);                 // 执行堆排序
    printVector("排序后: ", nums1);  // 打印排序后的数组

    // 测试用例 2: 已排序数组
    // 预期结果: 1 2 3 4 5
    vector<int> nums2 = {1, 2, 3, 4, 5};
    cout << "\n>>> 测试 2: 已排序数组" << endl;
    printVector("排序前: ", nums2);
    heapSort(nums2);
    printVector("排序后: ", nums2);

    // 测试用例 3: 逆序数组
    // 预期结果: 1 2 3 4 5
    vector<int> nums3 = {5, 4, 3, 2, 1};
    cout << "\n>>> 测试 3: 逆序数组" << endl;
    printVector("排序前: ", nums3);
    heapSort(nums3);
    printVector("排序后: ", nums3);

    // 测试用例 4: 单元素数组
    // 预期结果: 42
    vector<int> nums4 = {42};
    cout << "\n>>> 测试 4: 单元素数组" << endl;
    printVector("排序前: ", nums4);
    heapSort(nums4);
    printVector("排序后: ", nums4);

    // 测试用例 5: 空数组
    // 预期结果: (空)
    vector<int> nums5 = {};
    cout << "\n>>> 测试 5: 空数组" << endl;
    printVector("排序前: ", nums5);
    heapSort(nums5);
    printVector("排序后: ", nums5);

    return 0; // 程序正常退出
}
