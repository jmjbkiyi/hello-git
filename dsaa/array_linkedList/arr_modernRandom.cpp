#include <iostream>
#include <random>

int modernRandom(int size){
    // 1. 硬件随机数生成器（种子）
    std::random_device rd; 
    // 2. 梅森旋转算法（强大的随机引擎）
    std::mt19937 gen(rd()); 
    // 3. 分布器：限定在 [0, size-1] 范围内的均匀分布
    std::uniform_int_distribution<> dis(0, size - 1);
    
    return dis(gen);
}

int main(){
    int nums[] = {10,20,30,40,50};
    int val = modernRandom(5);

    std::cout << "抽到的数字为：" << nums[val] << std::endl;

    return 0;
}