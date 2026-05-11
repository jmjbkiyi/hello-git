#include <iostream>
#include <vector>
using namespace std;

/* 二分查找插入点（无重复元素） */
int binarySearchInsertionSimple(const vector<int> &nums, int target) {
    int i = 0, j = nums.size() - 1; // 初始化双闭区间 [0, n-1]
    while (i <= j) {
        int m = i + (j - i) / 2; // 计算中点索引 m
        if (nums[m] < target) {
            i = m + 1; // target 在区间 [m+1, j] 中
        } else if (nums[m] > target) {
            j = m - 1; // target 在区间 [i, m-1] 中
        } else {
            return m; // 找到 target ，返回插入点 m
        }
    }
    // 未找到 target ，返回插入点 i
    return i;
}

/* 二分查找插入点（存在重复元素） */
int binarySearchInsertion(const vector<int> &nums, int target){
   int i=0, j=nums.size()-1;
   while(i<=j){
      int m = i + (j-i) / 2;
      if(nums[m] < target){
          i = m + 1;
      }else{
          //由于要查找最左边的 target，所以 nums[m]>target 和 nums[m]==target 的操作都一样
          j = m - 1;
      }
   }
   // 返回插入点 i
   return i;
}

/* --- Driver Code --- */
int main() {
    cout << "=== 场景 1：无重复元素的有序数组 ===" << endl;
    vector<int> nums1 = {1, 3, 6, 8, 12, 15};
    cout << "数组 nums1 = [1, 3, 6, 8, 12, 15]" << endl;
    
    // 测试：插入已存在的元素、插入不存在的中间元素、插入超越边界的元素
    vector<int> targets1 = {6, 7, 20};
    for(int target : targets1) {
        int index = binarySearchInsertionSimple(nums1, target);
        cout << "  > 插入 target = " << target 
             << "，正确的插入点应为索引: " << index << endl;
    }

    cout << "\n=== 场景 2：存在大量重复元素的有序数组 ===" << endl;
    vector<int> nums2 = {1, 3, 6, 6, 6, 6, 8, 12};
    cout << "数组 nums2 = [1, 3, 6, 6, 6, 6, 8, 12]" << endl;
    // 索引对照表:   0, 1, 2, 3, 4, 5, 6,  7
    
    // 测试：插入存在的重复元素（应返回最左侧边界）、插入不存在的元素
    vector<int> targets2 = {6, 7, 0};
    for(int target : targets2) {
        int index = binarySearchInsertion(nums2, target);
        cout << "  > 插入 target = " << target 
             << "，最左侧的插入点应为索引: " << index << endl;
    }

    return 0;
}
