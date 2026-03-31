#include <iostream>
using namespace std;

int tailRecur(int n,int res){
    if(n == 1){
        cout << "本层n = " << n << ", res = " << res << endl;
        return res;
    }
    cout << "本层n = " << n << ", res = " << res << endl;
    return tailRecur(n-1,res+n);
}

int main(){
    int n=9,res=0;
    int sum = tailRecur(n,res);
    cout << "sum = " << sum << endl;
    return 0;
}