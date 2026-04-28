#include <iostream>
#include <queue>
#include <vector>
#include <functional>  //greater 和 less 都在functional里

using namespace std;

// 辅助打印函数（注意：这里必须是值传递 priority_queue<int>，不能加引用 &）
// 这样我们在函数体内部 pop 掉的只是原堆的一个“替身/拷贝”，原堆安然无恙
/*缺点十分明显，只能打印大顶堆*/
// void printHeap(priority_queue<int> copyHeap) {
//     cout << "堆的内容（自堆顶至堆底）：" ;
//     while(!copyHeap.empty()) {
//          cout << copyHeap.top() << " " ;
//          copyHeap.pop();
//     }
//     cout << endl;
// }

// 🌟 终极万能打印函数（利用 C++ 模板）
// template <typename T> 告诉编译器：T 是一个未知的占位符类型
// T copyHeap依然是按值传递（拷贝），不会破坏原堆
template <typename T>
void printHeap(T copyHeap) {
    cout << "堆的内容: ";
    while (!copyHeap.empty()) {
        cout << copyHeap.top() << " "; 
        copyHeap.pop();                
    }
    cout << endl;
}

int main(){
    //小顶堆，三个参数必须全写全
    // priority_queue<int, vector<int>, greater<int>> minHeap;
    //大顶堆，可以直接写，默认是大顶堆；也可以写全priority_queue<int,vector<int>,less<int>> maxMap
    priority_queue<int> maxHeap;

    /* 元素入堆 */
    maxHeap.push(1);
    maxHeap.push(3);
    maxHeap.push(2);
    maxHeap.push(5);
    maxHeap.push(4);

    // 调用安全的打印函数
    printHeap(maxHeap);

    /* 获取堆顶元素 */
    int peek = maxHeap.top(); // 5
    cout << "堆顶元素为：" << peek << endl;

    
    /* 获取堆大小 */
    int size = maxHeap.size();
    cout << "堆的大小为：" << size << endl;

    /* 堆顶元素出堆 */
    // 出堆元素会形成一个从大到小的序列
    // 
    cout << "\n开始手动出堆操作..." << endl;
    while(!maxHeap.empty()) {
        cout << "弹出: " << maxHeap.top() << endl;
        maxHeap.pop();
    }

    /* 判断堆是否为空 */
    bool isEmpty = maxHeap.empty();

    /*迭代器建堆/批量建堆，适用于一开始就拿到一批完整数据*/
    //输入列表并建堆
    // 时间复杂度为 O(n) ，而非 O(nlogn)
    vector<int> input{1,3,4,5,2};
    priority_queue<int, vector<int>, greater<int>> minHeap(input.begin(), input.end());

    // cout << "小顶堆输出：" ;
    // while(!minHeap.empty()) {
    //     cout << minHeap.top() << " " ;
    //     minHeap.pop();
    // }
    // cout << endl;

    printHeap(minHeap);

    return 0;
}