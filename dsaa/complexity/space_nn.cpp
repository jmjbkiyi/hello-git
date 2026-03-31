#include <iostream>
#include <vector>
using namespace std;

void quadraticRecur(int n){
    if(n <= 0){
        return;
    }
    vector<int> nums(n);
    cout << "递归n = " << n << " 中的 nums 的长度是 " << nums.size() << endl;
    quadraticRecur(n-1);
}

int main(){
    int n = 5;
    quadraticRecur(n);
    return 0;
}