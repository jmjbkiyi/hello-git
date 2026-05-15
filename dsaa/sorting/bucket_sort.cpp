//考虑一个长度为n的数组，其元素是范围[0,1)内的浮点数。
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void bucketSort(vector<float> &nums){
    // 初始化 k = n/2 个桶，预期向每个桶分配 2 个元素
    int k = nums.size() / 2 ;
    vector<vector<float>> buckets(k);
    // 1. 将数组元素分配到各个桶中
    for(float num : nums){
        // 输入数据范围为 [0, 1)，使用 num * k 映射到索引范围 [0, k-1]
        int i = num * k;
        buckets[i].push_back(num);
    }
    // 2. 对各个桶执行排序
    for(auto &bucket : buckets){
        sort(bucket.begin(),bucket.end());
    }
    // 3. 遍历桶合并结果
    int i = 0;
    for(auto &bucket : buckets){
        for(auto num : bucket){
            nums[i++] = num ;
        }
    }
}

/* --- Driver Code --- */
// 辅助打印函数
void printVector(const string& msg, const vector<float>& nums) {
    cout << msg << "[";
    for (int i = 0; i < nums.size(); i++) {
        cout << nums[i] << (i == nums.size() - 1 ? "" : ", ");
    }
    cout << "]" << endl;
}

int main() {
    cout << "=== 桶排序 (Bucket Sort) 测试 ===" << endl;

    // 测试用例：范围在 [0, 1) 内的浮点数
    vector<float> nums = {0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    
    printVector("排序前: ", nums);
    
    // 调用修改好类型的 bucketSort
    bucketSort(nums);
    
    printVector("排序后: ", nums);

    return 0;
}
