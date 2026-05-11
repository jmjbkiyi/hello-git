#include <iostream>
#include <vector>
#include <utility>
using namespace std;

/* 冒泡排序 */
void bubbleSort(vector<int> &nums){
    for(int i=0;i<nums.size();i++){
        for(int j=0;j<nums.size()-i-1;j++){
            if(nums[j] > nums[j+1]) swap(nums[j],nums[j+1]);
        }
    }
}

/* 冒泡排序（标志优化）*/
void bubbleSortWithFlag(vector<int> &nums){
    for(int i = nums.size()-1; i > 0 ; i--){
        bool flag = false;
        for(int j = 0 ; j < i ; j++){
            if(nums[j] > nums[j+1]) {
                swap(nums[j],nums[j+1]);
                flag = true;
            }
        }
        if(!flag) break;  // 此轮“冒泡”未交换任何元素，直接跳出
    }
} 

/* Driver Code */
int main() {
    vector<int> nums = {4, 1, 3, 1, 5, 2};
    cout << "排序前 nums = " ;
    for(auto num : nums) {
        cout << num << " " ;
    }
    cout << endl;
    bubbleSort(nums);
    cout << "冒泡排序完成后 nums = ";
    for(auto num : nums) {
        cout << num << " " ;
    }
    cout << endl;

    vector<int> nums1 = {4, 1, 3, 1, 5, 2};
    cout << "排序前 nums1 = " ;
    for(auto num : nums1) {
        cout << num << " " ;
    }
    cout << endl;
    bubbleSortWithFlag(nums1);
    cout << "带标记的冒泡排序完成后 nums1 = ";
    for(auto num : nums1) {
        cout << num << " " ;
    }
    cout << endl;

    return 0;
}
