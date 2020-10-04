# 第05章 指针与引用

## 5-2 左值与右值

### 左值与右值的概念
![左值与右值的概念](images/左值与右值的概念.jpg)

### 表达式必须是一个可修改的左值
![表达式必须是一个可修改的左值](images/表达式必须是一个可修改的左值.jpg)

## 5-6 野指针

### NULL指针
![NULL指针](images/NULL指针.jpg)

### 野指针分类
> 野指针：指向垃圾内存的指针

三种情况：
+ 1.指针变量没有进行初始化
  > ![未初始化的指针](images/未初始化的指针.jpg)
+ 2.已经释放不用的指针（地址空间内容已经释放）没有置为NULL
+ 3.指针操作超越了变量的作用范围

![野指针](images/野指针.jpg)

## 5-10 不同变量在内存中的位置
![表达式必须是一个可修改的左值](images/不同变量在内存中的位置.jpg)

+ 栈(Stack)中的变量是从高地址向低地址存储；堆(Heap)中的变量是从低地址向高地址存储

> C++内存模型如下：

![CPP内存模型](images/CPP内存模型.jpg)

## 5-12 C++的动态分配与回收
### 堆在不同语言中的使用
![堆在不同语言中的使用](images/堆在不同语言中的使用.jpg)

### 动态分配的原则
![分配和回收动态内存的原则](images/分配和回收动态内存的原则.jpg)

## 5-13 RAII资源管理方案
![RAII资源管理方案](images/RAII资源管理方案.jpg)

## 5-14 几种变量存储区的对比
### 栈和堆的对比
![栈和堆的对比](images/栈和堆的对比.jpg)

### 全局静态存储区和常量区的对比
![](images/全局静态存储区和常量区的对比.png)

## 5-15 内存泄露问题
![内存泄露问题](images/内存泄露问题.jpg)

## 5-16 智能指针
### 安全使用指针的两种方案
![安全使用指针的两种方案](images/安全使用指针的两种方案.png)

### 常用的智能指针
> shared_ptr和weak_ptr经常结合在一起用，用地最多
![常见的智能指针](images/常见的智能指针.png)

### auto_ptr的使用和问题
![auto_ptr的使用和问题](images/auto_ptr的使用和问题.png)

```cpp
#include <string>
#include <iostream>
#include <memory>

using namespace std;

int main() {
    {// 确定auto_ptr失效的范围
        // 对int使用
        auto_ptr<int> pI(new int(10));
        cout << *pI << endl;                // 10 

        // auto_ptr	C++ 17中移除	拥有严格对象所有权语义的智能指针
        // auto_ptr原理：在拷贝 / 赋值过程中，直接剥夺原对象对内存的控制权，转交给新对象，
        // 然后再将原对象指针置为nullptr（早期：NULL）。这种做法也叫管理权转移。
        // 他的缺点不言而喻，当我们再次去访问原对象时，程序就会报错，所以auto_ptr可以说实现的不好，
        // 很多企业在其库内也是要求不准使用auto_ptr。
        auto_ptr<string> languages[5] = {
                auto_ptr<string>(new string("C")),
                auto_ptr<string>(new string("Java")),
                auto_ptr<string>(new string("C++")),
                auto_ptr<string>(new string("Python")),
                auto_ptr<string>(new string("Rust"))
        };
        cout << "There are some computer languages here first time: \n";
        for (int i = 0; i < 5; ++i) {
            cout << *languages[i] << endl;
        }
        auto_ptr<string> pC;
        pC = languages[2]; // languges[2] loses ownership. 将所有权从languges[2]转让给pC，
        //此时languges[2]不再引用该字符串从而变成空指针
        cout << "There are some computer languages here second time: \n";
        for (int i = 0; i < 2; ++i) {
            cout << *languages[i] << endl;
        }
        cout << "The winner is " << *pC << endl;
        //cout << "There are some computer languages here third time: \n";
        //for (int i = 0; i < 5; ++i)
        //{
        //	cout << *languages[i] << endl;
        //}
    }
    return 0;
}
```
