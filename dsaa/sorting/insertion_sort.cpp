#include <iostream>
#include <vector>
#include <utility>
using namespace std;

/* 插入排序 */
void insertionSort(vector<int> &nums){
    for(int i=1;i<nums.size();i++){
        int base = nums[i], j = i-1;
        while(j>=0 && nums[j] > base){
            nums[j+1] = nums[j];  // 将 nums[j] 向右移动一位
            j--;
        }
        nums[j+1] = base;
    }
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
    cout << "=== 插入排序 (Insertion Sort) 测试 ===" << endl;

    // 测试用例 1：常规无序数组（包含重复元素，验证稳定性）
    vector<int> nums1 = {4, 1, 3, 1, 5, 2};
    printVector("排序前: ", nums1);
    insertionSort(nums1);
    printVector("排序后: ", nums1);

    // 测试用例 2：完全逆序数组（测试最差情况 O(n^2)）
    cout << "\n=== 测试最差情况 (完全逆序) ===" << endl;
    vector<int> nums2 = {9, 7, 5, 3, 2};
    printVector("排序前: ", nums2);
    insertionSort(nums2);
    printVector("排序后: ", nums2);

    // 测试用例 3：已排序数组（测试最佳情况 O(n)）
    cout << "\n=== 测试最佳情况 (已排序) ===" << endl;
    vector<int> nums3 = {1, 2, 3, 4, 5};
    printVector("排序前: ", nums3);
    insertionSort(nums3);
    printVector("排序后: ", nums3);

    return 0;
}
