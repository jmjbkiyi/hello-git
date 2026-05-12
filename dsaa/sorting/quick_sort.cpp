#include <iostream>
#include <vector>
#include <utility>
using namespace std;

/* 快速排序类 */
class QuickSort{
private:
    /* 哨兵划分 */
    static int partition(vector<int> &nums, int left, int right){
        // 以 nums[left] 为基准数
        int i=left, j=right;
        while(i<j){
            while(i<j && nums[j] >= nums[left]){
                j--;   // 从右向左找首个小于基准数的元素
            }
            while(i<j && nums[i] <= nums[left]){
                i++;  // 从左向右找首个大于基准数的元素
            }
            /*在快排的经典双指针交换法中，有一个铁律：
            如果选最左边的元素作为基准数（Pivot），必须让右指针j
            先动；反之，如果选最右边作为基准数，必须让左指针 i 先动。
            */
            swap(nums[i],nums[j]);
        }
        swap(nums[i],nums[left]);  // 将基准数交换至两子数组的分界线
        return i;
    }
    
public:
    static void quickSort(vector<int> &nums,int left,int right){
        // 子数组长度为 1 时终止递归
        if(left>=right) return;
        int pivot = partition(nums,left,right);
        // 递归左子数组、右子数组
        quickSort(nums,left,pivot-1);
        quickSort(nums,pivot+1,right);
    }
};

/* 快速排序类（中位基准数优化） */
class QuickSortMedian {
private:
    /* 选取三个候选元素的中位数 */
    static int medianThree(const vector<int> &nums, int left, int med, int right){
        int l=nums[left], m=nums[med], r=nums[right];
        if(l<=m && r>=m || l>=m && r<=m) return med;
        if(m<=l && l<=r || r<=l && l<=m) return left;
        return right;
    }
    
    static int partition(vector<int> &nums, int left, int right){
        // 选取三个候选元素的中位数
        int med = medianThree(nums,left,(left+right)/2,right);
        // 将中位数交换至数组最左端
        swap(nums[left],nums[med]);
        int i=left,j=right;
        while(i<j){
            while(i<j && nums[j] >= nums[left]){
                j--;
            }
            while(i<j && nums[i] <= nums[left]){
                i++;
            }
            swap(nums[i],nums[j]);
        }
        swap(nums[i],nums[left]);
        return i;
    }
    
public:
    static void quickSort(vector<int> &nums,int left,int right){
        if(left>=right) return;
        int pivot = partition(nums,left,right);
        quickSort(nums,left,pivot-1);
        quickSort(nums,pivot+1,right);
    }
};

/* 快速排序类（递归深度优化） */
class QuickSortTailCall {
private:
    static int partition(vector<int> &nums,int left,int right){
        int i=left,j=right;
        while(i<j){
            while(i<j && nums[j] >= nums[left]){
                j--;
            }
            while(i<j && nums[i] <= nums[left]){
                i++;
            }
            swap(nums[i],nums[j]);
        }
        swap(nums[left],nums[i]);
        return i;
    }
public:
    static void quickSort(vector<int> &nums,int left,int right){
        while(left<right){
            int pivot = partition(nums,left,right);
            if(pivot - left < right - pivot){
                quickSort(nums,left,pivot-1);
                left=pivot+1;
            }else{
                quickSort(nums,pivot+1,right);
                right=pivot-1;
            }
        }
    }
};

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
    cout << "=== 快速排序 (Quick Sort) 三大变体测试 ===" << endl;

    // 测试 1：基础快排
    vector<int> nums1 = {2, 4, 1, 0, 3, 5};
    cout << "\n>>> 测试 1: 基础快速排序" << endl;
    printVector("排序前: ", nums1);
    QuickSort::quickSort(nums1, 0, nums1.size() - 1);
    printVector("排序后: ", nums1);

    // 测试 2：中位基准数优化
    vector<int> nums2 = {8, 1, 4, 9, 0, 3, 5, 2, 7, 6};
    cout << "\n>>> 测试 2: 中位基准数优化快排" << endl;
    printVector("排序前: ", nums2);
    QuickSortMedian::quickSort(nums2, 0, nums2.size() - 1);
    printVector("排序后: ", nums2);

    // 测试 3：尾递归消除优化
    vector<int> nums3 = {15, 22, 13, 9, 22, 1, 8};
    cout << "\n>>> 测试 3: 尾递归消除优化快排" << endl;
    printVector("排序前: ", nums3);
    QuickSortTailCall::quickSort(nums3, 0, nums3.size() - 1);
    printVector("排序后: ", nums3);

    return 0;
}
