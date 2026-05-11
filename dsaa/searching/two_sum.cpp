/*Question:
给定一个整数数组 nums 和一个目标元素 target ，请在数组中搜索“和”为 target 的两个元素，并返回它们的数组索引。返回任意一个解即可。
*/
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/* 方法一：暴力枚举 */
vector<int> twoSumBruteForce(const vector<int> &nums, int target){
    for(int i=0;i<nums.size()-1;i++){
        for(int j=i+1;j<nums.size();j++){
            if((nums[i] + nums[j]) == target){
                return {i,j};
            }
        }
    }
    return {};
}
/* 方法二：辅助哈希表 */
vector<int> twoSumHashTable(const vector<int> &nums, int target){
    unordered_map<int,int> dic;
    // 单层循环，时间复杂度为 O(n)
    for(int i=0;i<nums.size();i++){
        if(dic.find(target-nums[i]) != dic.end()){
            return{dic[target-nums[i]],i};
        }
        dic.emplace(nums[i],i);
    }
    return {};
}

/* --- Driver Code --- */
// 辅助打印函数
void printResult(const string& methodName, const vector<int>& res) {
    cout << methodName << " 结果: ";
    if(res.empty()) {
        cout << "未找到符合条件的两个元素" << endl;
    } else {
        cout << "[" << res[0] << ", " << res[1] << "]" << endl;
    }
}

int main() {
    cout << "=== 两数之和 (Two Sum) 测试 ===" << endl;

    // 测试用例 1：常规情况
    vector<int> nums1 = {2, 7, 11, 15};
    int target1 = 9;
    cout << "\n>>> 测试用例 1: nums = [2, 7, 11, 15], target = 9" << endl;
    printResult("暴力枚举法", twoSumBruteForce(nums1, target1));
    printResult("哈希表加速", twoSumHashTable(nums1, target1));

    // 测试用例 2：测试避免“自己加自己”的逻辑漏洞
    vector<int> nums2 = {3, 2, 4};
    int target2 = 6;
    cout << "\n>>> 测试用例 2: nums = [3, 2, 4], target = 6 (检验是否重复使用元素)" << endl;
    // 如果暴力法内层 j 从 0 开始，这里会错误输出 [0, 0]
    printResult("暴力枚举法", twoSumBruteForce(nums2, target2));
    printResult("哈希表加速", twoSumHashTable(nums2, target2));

    // 测试用例 3：包含相同的数字
    vector<int> nums3 = {3, 3};
    int target3 = 6;
    cout << "\n>>> 测试用例 3: nums = [3, 3], target = 6" << endl;
    printResult("暴力枚举法", twoSumBruteForce(nums3, target3));
    printResult("哈希表加速", twoSumHashTable(nums3, target3));

    // 测试用例 4：找不到解的情况
    vector<int> nums4 = {1, 2, 3, 4};
    int target4 = 100;
    cout << "\n>>> 测试用例 4: nums = [1, 2, 3, 4], target = 100 (无解)" << endl;
    printResult("暴力枚举法", twoSumBruteForce(nums4, target4));
    printResult("哈希表加速", twoSumHashTable(nums4, target4));

    return 0;
}
