#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int> &nums, int left, int mid, int right){
    // 左子数组区间为 [left, mid], 右子数组区间为 [mid+1, right]
    // 创建一个临时数组 tmp ，用于存放合并后的结果
    // vector<int> tmp(nums.size()); 不可！因为 nums 从始至终都是原数组
    vector<int> tmp(right - left + 1);
    // 初始化左子数组和右子数组的起始索引
    int i = left, j = mid + 1, k = 0;
    // 当左右子数组都还有元素时，进行比较并将较小的元素复制到临时数组中
    while(i<=mid && j<=right){
        if(nums[i]<=nums[j]){
            tmp[k++] = nums[i++];
        }else{
            tmp[k++] = nums[j++];
        }
    }
    // 将左子数组和右子数组的剩余元素复制到临时数组中
    while(i<=mid){
        tmp[k++] = nums[i++];
    }
    while(j<=right){
        tmp[k++] = nums[j++];
    }
    // 将临时数组 tmp 中的元素复制回原数组 nums 的对应区间
    for(k=0;k<tmp.size();k++){
        nums[left + k] = tmp[k]; //细节 left+k，防止合并右子树组时索引错误
    }
}

void mergeSort(vector<int> &nums, int left, int right){
    // 终止条件
    if(left >= right){
      return; // 当子数组长度为 1 时终止递归
    }
    int mid = left + (right-left) / 2;
    // 划分阶段
    mergeSort(nums,left,mid);
    mergeSort(nums,mid+1,right);
    // 合并阶段
    merge(nums,left,mid,right);
}

/* --- Driver Code --- */
// 辅助打印函数
void printVector(const string& msg, const vector<int>& nums) {
    cout << msg << "[";
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << (i == nums.size() - 1 ? "" : ", ");
    }
    cout << "]" << endl;
}

int main() {
    cout << "=== 归并排序 (Merge Sort) 测试 ===" << endl;

    // 测试用例 1：常规无序数组
    vector<int> nums1 = {7, 3, 2, 6, 0, 1, 5, 4};
    cout << "\n>>> 测试 1: 常规无序数组" << endl;
    printVector("排序前: ", nums1);
    mergeSort(nums1, 0, nums1.size() - 1);
    printVector("排序后: ", nums1);

    // 测试用例 2：包含重复元素和负数
    vector<int> nums2 = {3, -1, 4, 3, 2, -1, 8, 3};
    cout << "\n>>> 测试 2: 包含重复元素和负数 (验证稳定性)" << endl;
    printVector("排序前: ", nums2);
    mergeSort(nums2, 0, nums2.size() - 1);
    printVector("排序后: ", nums2);

    // 测试用例 3：已经排序好的数组
    vector<int> nums3 = {1, 2, 3, 4, 5};
    cout << "\n>>> 测试 3: 已排序的数组" << endl;
    printVector("排序前: ", nums3);
    mergeSort(nums3, 0, nums3.size() - 1);
    printVector("排序后: ", nums3);

    return 0;
}
