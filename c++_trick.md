# C++ 核心语法与避坑速查手册 (带代码示例)

## 1. 内存与指针引用 (Memory & References)
* 【& 符号的双面性】
  - 类型后 (int& a)：引用（起别名）。操作引用即操作原件。
  - 变量前 (&a)：取地址。获取指针。
* 【return *this】
  - 用于支持链式调用（如 a = b = c）。
  - 代码示例：
    ```cpp
    Complex& operator+=(const Complex& c) {
        real += c.real;
        return *this; // 返回解引用的本尊
    }
    ```
* 【深拷贝 vs 浅拷贝】
  - 只要类里有 new 出来的指针，必须手动重载 operator=，否则会引发 Double Free。
  - 流程：防自反 -> 释放旧内存 -> 申请新内存 -> 拷数据。

## 2. 运算符重载 (Operator Overloading)
* 【成员函数 vs 友元函数 (friend)】
  - 成员函数：运算符左侧是“自己”时用（如 +=, ==, ++）。
  - 友元函数：运算符左侧是“别人”（如 cout）时必须用 friend。
  - 代码示例 (流输出重载)：
    ```cpp
    class Matrix {
        friend ostream& operator<<(ostream& out, const Matrix& m);
    };
    ostream& operator<<(ostream& out, const Matrix& m) {
        out << m.data; // 拥有通行证，直接访问私有成员
        return out;    // 必须返回引用以支持 cout << a << b;
    }
    ```
* 【const 护体】
  - 不修改对象本身的重载函数，必须在末尾加 const。
  - `bool operator==(const Matrix& m) const { ... }`

## 3. 面向对象与动态多态 (OOP & Polymorphism)
* 【封装的艺术】
  - 类内方法互调：类内部循环尽量用 `i < size()`，而不是直掏底层的 `i < tree.size()`。
* 【多态的触发三要素】
  - 1. 父类有 virtual 函数；2. 子类重写；3. 父类指针/引用指向子类对象。
* 【底层机制：查表法】
  - 只要加了 virtual，对象体内就会塞入一个 8 字节的虚指针 (vptr)，运行时去虚函数表 (vtable) 里查真实地址。
* 【override 防手残】
  - 强制编译器检查子类重写是否拼错名字或对错参数。
  - 代码示例：
    ```cpp
    class Son : public Father {
    public:
        void spendMoney() override { ... } // 必须写在最后面
    };
    ```
* 【析构函数的铁律】
  - 只要这个类准备当父类，它的析构函数必须加 virtual，防止 delete 父类指针时子类内存泄漏。

## 4. 现代 C++ 护航关键字 (Modern Keywords)
* 【explicit（禁毒令）】
  - 防止编译器偷偷拿单参数去做隐式类型转换。
  - 代码示例：
    ```cpp
    explicit StudentID(int n) { id = n; }
    // StudentID s = 1001; // 报错！被 explicit 拦截
    ```
* 【noexcept（免死金牌）】
  - 发誓该函数绝不报错。特别是在移动构造函数上，加上它才能让 vector 搬家时从慢速拷贝变成极速移动。
  - `void swap(T& a, T& b) noexcept { ... }`
* 【static_cast（静态转换）】
  - 用于理直气壮的转换（基础类型互转、安全的向上转型）。
  - `int num = static_cast<int>(3.14);`
* 【dynamic_cast（动态转换）】
  - 用于危险的向下转型（父类转子类）。自带安检，不是亲儿子就返回 nullptr。

## 5. 移动语义与终极交换 (Move & Swap)
* 【std::move（废品贴纸）】
  - 它不移动数据！它只是把对象转为右值，告诉编译器：“我不要了，谁来抢走我的底层指针都可以。”
* 【std::swap 的 O(1) 魔法】
  - 不发生海量数据的复印，仅倒腾三个指针。
  - `swap(vec1, vec2); // 100万个数据瞬间对调`
* 【神技：Swap Trick 彻底清空内存】
  - vector 的 `clear()` 只让 size=0，但 capacity（物理内存）一点不还。
  - 代码示例 (物理清空)：
    ```cpp
    vector<int> vec = {1, 2, 3...}; // 占用巨大内存
    vector<int>().swap(vec);        // 用匿名空壳套走旧内存并随之销毁
    // 此时 vec 彻底变为 0 size, 0 capacity
    ```

## 6. STL 容器与数据结构 (STL & Data Structures)
* 【queue (普通队列)】
  - FIFO（先进先出）。
  - `que.push(x);` | `que.front();` | `que.pop(); // 注意 pop 不返回元素`
* 【priority_queue (优先队列 / 堆)】
  - 默认是大顶堆。
  - 代码示例 (大顶堆 vs 小顶堆)：
    ```cpp
    priority_queue<int> maxHeap; // 默认大顶堆
    priority_queue<int, vector<int>, greater<int>> minHeap; // 必须写全才是小顶堆
    ```
* 【神技：批量建堆 (Range Initialization)】
  - 时间复杂度 O(N)，远快于 for 循环 push 的 O(N log N)。
  - 代码示例：
    ```cpp
    vector<int> arr = {3, 1, 4, 1, 5};
    priority_queue<int, vector<int>, greater<int>> minHeap(arr.begin(), arr.end()); // 瞬间建好小顶堆
    ```
* 【二叉树遍历 (DFS)】
  - 盯住“根节点”的位置：
    - 前序 (Pre-order): 根 -> 左 -> 右
    - 中序 (In-order): 左 -> 根 -> 右
    - 后序 (Post-order): 左 -> 右 -> 根（适合用来做 delete 内存释放）

## 7. 典型报错诊断 (Debugging)
* 【Illegal instruction (core dumped)】
  - 排查 1：函数有返回值，但你忘了写 `return`（最常见）。
  - 排查 2：访问了 `nullptr` 或者已释放的内存。
* 【redeclaration of 'xxx'】
  - 排查：变量名重名了（同一个大括号里声明了两次）。删掉旧的，或者用 `=` 直接覆盖赋值。