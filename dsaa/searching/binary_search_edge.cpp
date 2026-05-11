#include <iostream>
#include <vector>
using namespace std;

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

/* 二分查找最左一个 target */
int binarySearchLeftEdge(const vector<int> &nums, int target) {
    // 等价于查找 target 的插入点
    int i = binarySearchInsertion(nums,target);
    // 未找到 target ，返回 -1
    if(i == nums.size() || nums[i] != target){
        return -1;
    }
    return i;
}

/* 二分查找最右一个 target */
//1.复用查找左边界
int binarySearchRightEdge(const vector<int> &nums,int target){
    // 转化为查找最左一个 target + 1
    int i = binarySearchInsertion(nums, target + 1);
    // j 指向最右一个 target ，i 指向首个大于 target 的元素
    int j = i - 1;
    if(j < 0 || nums[j] != target){
        return -1;
    }
    return j;
}
//2.转化为查找元素
// int binarySearchRightEdge_other(const vector<int> &nums,int target){
//     // 转化为查找不存在的元素 target+0.5
//     // 需要修改函数接口为 double
//     int i = binarySearchInsertion(nums, target + 0.5);
//     return j;
// }
//需要修改函数接口为 double
//相应的，寻找最云左端，转化为查找 target-0.5，返回 i
//给定数组不包含小数，这意味着我们无须关心如何处理相等的情况。


/* --- Driver Code --- */
int main() {
    cout << "=== 二分查找边界探测测试 ===" << endl;
    
    // 构建一个包含大量重复元素的有序数组
    vector<int> nums = {1, 3, 6, 6, 6, 6, 8, 12};
    cout << "测试数组: [1, 3, 6, 6, 6, 6, 8, 12]" << endl;
    cout << "索引参照:  0  1  2  3  4  5  6   7" << endl;
    
    // 测试 1：查找存在的元素边界
    int target1 = 6;
    cout << "\n>>> 测试查找 Target = " << target1 << endl;
    int leftIndex1 = binarySearchLeftEdge(nums, target1);
    int rightIndex1 = binarySearchRightEdge(nums, target1);
    cout << "最左侧边界索引: " << leftIndex1 << " (预期: 2)" << endl;
    cout << "最右侧边界索引: " << rightIndex1 << " (预期: 5)" << endl;

    // 测试 2：查找不存在的元素
    int target2 = 7;
    cout << "\n>>> 测试查找 Target = " << target2 << " (不存在的中间元素)" << endl;
    cout << "最左侧边界索引: " << binarySearchLeftEdge(nums, target2) << " (预期: -1)" << endl;
    cout << "最右侧边界索引: " << binarySearchRightEdge(nums, target2) << " (预期: -1)" << endl;

    // 测试 3：查找超出左右极值的元素
    int target3 = 0;
    int target4 = 20;
    cout << "\n>>> 测试查找 Target = " << target3 << " (越界极小值)" << endl;
    cout << "最左边界: " << binarySearchLeftEdge(nums, target3) << " | 最右边界: " << binarySearchRightEdge(nums, target3) << endl;
    
    cout << "\n>>> 测试查找 Target = " << target4 << " (越界极大值)" << endl;
    cout << "最左边界: " << binarySearchLeftEdge(nums, target4) << " | 最右边界: " << binarySearchRightEdge(nums, target4) << endl;

    return 0;
}
