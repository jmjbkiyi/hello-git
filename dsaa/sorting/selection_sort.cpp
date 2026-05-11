#include <iostream>
#include <vector>
#include <utility>
using namespace std;

/* 选择排序 */
void selectionSort(vector<int> &nums){
    for(int i=0;i<nums.size()-1;i++){
        int minidx = i;
        for(int j=i+1;j<nums.size();j++){
            if(nums[j] < nums[minidx]) minidx = j;
        }
        if(minidx != i){
            swap(nums[i],nums[minidx]);
        }
    }
}

/* Driver Code */
int main() {
    vector<int> nums = {4, 1, 3, 1, 5, 2};
    cout << "Original nums = ";
    for(auto num : nums){
        cout << num << " " ;
    }
    cout << endl;
    
    selectionSort(nums);

    cout << "选择排序完成后 nums = ";
    for(auto num : nums){
        cout << num << " " ;
    }
    cout << endl;

    return 0;
}