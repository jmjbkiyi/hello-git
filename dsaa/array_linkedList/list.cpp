#include <iostream>
#include <vector>
#include <algorithm> // sort() 的家
using namespace std;

void printVector(const vector<int>& nums){
    for(int num:nums){
        cout << num << endl;
    }
}

int main() {
    /* 初始化列表 */
    vector<int> nums = {1, 3, 2, 5, 4};
    cout << "列表 nums = ";
    printVector(nums);

    /* 访问元素 */
    int num = nums[1];
    cout << "访问索引 1 处的元素，得到 num = " << num << endl;

    /* 更新元素clear() */
    nums[1] = 0;
    cout << "将索引 1 处的元素更新为 0 ，得到 nums = ";
    printVector(nums);

    /* 清空列表 */
    nums.clear();
    cout << "清空列表后 nums = ";
    printVector(nums);

    /* 在尾部添加元素push_back()*/
    nums.push_back(1);
    nums.push_back(3);
    nums.push_back(2);
    nums.push_back(5);
    nums.push_back(4);
    cout << "添加元素后 nums = ";
    printVector(nums);

    /* 在中间插入元素insert() */
    nums.insert(nums.begin() + 3, 6);
    cout << "在索引 3 处插入数字 6 ，得到 nums = ";
    printVector(nums);

    /* 删除元素erase() */
    nums.erase(nums.begin() + 3);
    cout << "删除索引 3 处的元素，得到 nums = ";
    printVector(nums);

    /* 通过索引遍历列表 */
    int count = 0;
    for (int i = 0; i < nums.size(); i++) {
        count += nums[i];
    }
    /* 直接遍历列表元素 */
    count = 0;
    for (int x : nums) {
        count += x;
    }

    /* 拼接两个列表insert() */
    vector<int> nums1 = {6, 8, 7, 10, 9};
    nums.insert(nums.end(), nums1.begin(), nums1.end());
    cout << "将列表 nums1 拼接到 nums 之后，得到 nums = ";
    printVector(nums);

    /* 排序列表 */
    // 核心语法：传入起始和结束迭代器 (左闭右开)
    sort(nums.begin(), nums.end());
    cout << "排序列表后 nums = ";
    printVector(nums);

    return 0;
}