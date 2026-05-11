#include <iostream>
#include <vector>
using namespace std;

/* 二分查找（双闭区间） */
int binarySearch(const vector<int> &nums, int target){
    int i=0, j=nums.size()-1;
    // 循环，当搜索区间为空时跳出（当 i > j 时为空）
    while(i<=j){
      int m = i + (j-i) / 2;
        if(nums[m] > target){
            j = m - 1;
        }else if(nums[m] < target){
            i = m + 1;
        }else{
            return m;
        }
    }
    return -1;
}

/* 二分查找（左闭右开区间） */
int binarySearchLcRo(const vector<int> &nums, int target){
    int i=0, j=nums.size();
    while(i<j){
        int m = i + (j-i) / 2;
        if(nums[m] < target){
            i = m + 1;
        }else if(nums[m] > target){
            j = m;
        }else{
            return m;
        }
    }
    return -1;
}

/* --- Driver Code --- */
int main() {
    // 沿用教材图解中的测试数组（必须是有序的）
    vector<int> nums = {1, 3, 6, 8, 12, 15, 23, 26, 31, 35};
    
    cout << "=== 测试数组 ===" << endl;
    cout << "nums = [";
    for(int i = 0; i < nums.size(); i++) {
        cout << nums[i] << (i == nums.size() - 1 ? "" : ", ");
    }
    cout << "]\n" << endl;

    // 准备几组测试用例：常规命中、边界命中、不存在的元素
    vector<int> targets = {6, 1, 35, 10, 40};
    
    for(int target : targets) {
        cout << ">>> 查找目标 (Target): " << target << endl;
        
        // 分别调用两种实现方式
        int res1 = binarySearch(nums, target);
        int res2 = binarySearchLcRo(nums, target);
        
        cout << "  双闭区间结果   : 索引 " << res1;
        if(res1 != -1) cout << " (值为 " << nums[res1] << ")";
        cout << endl;
        
        cout << "  左闭右开区间结果: 索引 " << res2;
        if(res2 != -1) cout << " (值为 " << nums[res2] << ")";
        cout << endl;
        
        // 验证两者的结果是否绝对一致
        if(res1 == res2) {
            cout << "  ✅ 两种算法结果一致" << endl;
        } else {
            cout << "  ❌ 出现分歧！" << endl;
        }
        cout << "------------------------" << endl;
    }

    return 0;
}
