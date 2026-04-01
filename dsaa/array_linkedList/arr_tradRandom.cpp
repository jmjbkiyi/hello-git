#include <iostream>
#include <cstdlib>
#include <ctime>

int randomAccess(int *nums, int size) {

    // 在区间 [0, size) 中随机抽取一个数字

    int randomIndex = rand() % size;

    // 获取并返回随机元素

    int randomNum = nums[randomIndex];

    return randomNum;

}

int main(){
    // 关键：用当前系统时间初始化随机数种子
    // time(0) 返回从 1970 年到现在的秒数
    srand(static_cast<unsigned int>(time(0)));

    int nums[] = {10,20,30,40,50};
    int val = randomAccess(nums,5);

    std::cout << "抽到的数字是：" << val << std::endl;

    return 0;
}