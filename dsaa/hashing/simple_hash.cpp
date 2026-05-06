#include <iostream>
using namespace std;

/* 加法哈希 */
int addHash(string key){
    long long hash = 0;
    const int MODULUS = 1000000007;
    for(unsigned char c : key) {
        hash = (hash + (int)c) % MODULUS;
    }
    return (int)hash;
}
/* 乘法哈希 */
int mulHash(string key) {
    long long hash = 0;
    const int MODULUS = 1000000007;
    for (unsigned char c : key) {
        hash = (31 * hash + (int)c) % MODULUS;
    }
    return (int)hash;
}

/* 异或哈希 */
int xorHash(string key) {
    int hash = 0;
    const int MODULUS = 1000000007;
    for (unsigned char c : key) {
        hash ^= (int)c;
    }
    return hash & MODULUS;   // 并不是取模，而是按位与操作，只是起到截断位数的限制作用
}

/* 旋转哈希 */
int rotHash(string key) {
    long long hash = 0;
    const int MODULUS = 1000000007;
    for (unsigned char c : key) {
        hash = ((hash << 4) ^ (hash >> 28) ^ (int)c) % MODULUS;
    }
    return (int)hash;
}
/* * 1. 加法哈希 (Additive Hash)
 * 原理：将字符串中所有字符的 ASCII 码直接相加。
 * 缺点：完全无视字符顺序。"abc" 和 "cba" 的哈希值绝对一样，极易产生哈希冲突。
 * 适用场景：基本无，仅作为教学反面教材。
int addHash(string key){
    long long hash = 0;
    const int MODULUS = 1000000007;
    for(unsigned char c : key) {
        hash = (hash + (int)c) % MODULUS;
    }
    return (int)hash;
}

* * 2. 乘法哈希 (Multiplicative Hash)
 * 原理：引入乘法权重（常数 31）。越靠前的字符被乘的次数越多，权重越大。
 * 优点：完美区分了字符顺序（"abc" != "cba"），分布极其均匀。31 是奇素数，
 * 底层可以通过位移优化 (31 * i == (i << 5) - i)，性能极高。
 * 适用场景：工业界绝对主力。Java 的 String.hashCode() 底层就是这个逻辑。
int mulHash(string key) {
    long long hash = 0;
    const int MODULUS = 1000000007;
    for (unsigned char c : key) {
        hash = (31 * hash + (int)c) % MODULUS;
    }
    return (int)hash;
}

* * 3. 异或哈希 (XOR Hash)
 * 原理：利用按位异或 (^) 极其快速的特性合并字符。
 * 缺点：异或运算存在“抵消效应”(a ^ a = 0)。如果字符串中有偶数个相同字符
 * （如 "aabb"），它们对哈希值的贡献会瞬间归零，导致严重冲突。
 * 适用场景：极少单独使用，通常作为复杂哈希算法（如 MurmurHash）的一个中间步骤。
int xorHash(string key) {
    int hash = 0;
    const int MODULUS = 1000000007;
    for (unsigned char c : key) {
        hash ^= (int)c;
    }
    // 注意：这里用的是按位与 (&)，起到截断位数的作用，保证结果在范围内
    return hash & MODULUS; 
}

* * 4. 旋转哈希 (Rotative Hash)
 * 原理：通过左移 (<< 4) 和右移 (>> 28) 操作，把二进制位像齿轮一样旋转打散，再异或新字符。
 * 优点：位运算极其廉价，且能将每一个字符的信息充分、均匀地混合到整型变量的 32 个比特位中。
 * 适用场景：对性能要求极其苛刻的 C/C++ 底层组件或轻量级数据处理。
int rotHash(string key) {
    long long hash = 0;
    const int MODULUS = 1000000007;
    for (unsigned char c : key) {
        // (hash >> 28) 是为了把左移溢出的高位重新补到低位，形成“循环旋转”
        hash = ((hash << 4) ^ (hash >> 28) ^ (int)c) % MODULUS;
    }
    return (int)hash;
}
*/

/* Driver Code */
int main() {
    string key = "Hello 算法";

    int hash = addHash(key);
    cout << "加法哈希值为 " << hash << endl;

    hash = mulHash(key);
    cout << "乘法哈希值为 " << hash << endl;

    hash = xorHash(key);
    cout << "异或哈希值为 " << hash << endl;

    hash = rotHash(key);
    cout << "旋转哈希值为 " << hash << endl;

    return 0;
}
