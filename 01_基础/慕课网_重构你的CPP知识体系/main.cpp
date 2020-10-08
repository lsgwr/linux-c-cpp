#include <iostream> // std::cout
#include <vector> // std::vector
#include <algorithm> // std::sort
#include <functional> // std::binary_function
#include <iterator>
#include <numeric>
#include <string>
#include <unordered_map>

//函数指针类别：返回S 无输入  通过指针调用
template<class S, class T>
class mem_fun_t : public std::unary_function<T *, S> {
public:
    explicit mem_fun_t(S (T::*pf)()) : f(pf) {}//初始化
    S operator()(T *p) const { return (p->*f)(); }//调用，p里面对应的函数
private:
    S (T::*f)();//这是一个变量，这个函数指针变量
};

//辅助函数，直接通过模板萃取相应的型别，然后声明相应的对象
template<class S, class T>
inline mem_fun_t<S, T> mem_fun(S (T::*f)()) {
    return mem_fun_t<S, T>(f);//返回仿函数临时对象，真的很牛逼哦抽象出来了
}

// 小例子
// size_type length() const { return _M_string_length; }
//
// mem_fun(&string::length);//传入函数指针，::优先级大于&
//s 是 size_type  T是string  f是length，通过模板萃取出这些型别，即可产生相应的对象。

//有一个参数，通过指针调用
template<class S, class T, class A>
class mem_fun1_t : public std::binary_function<T *, A, S> {
public:
    explicit mem_fun1_t(S (T::*pf)(A)) : f(pf) {}

    S operator()(T *p, A x) const { return (p->*f)(x); }

private:
    S (T::*f)(A);
};

template<class S, class T, class A>
class const_mem_fun1_t : public std::binary_function<const T *, A, S> {
public:
    explicit const_mem_fun1_t(S (T::*pf)(A) const) : f(pf) {}

    S operator()(const T *p, A x) const { return (p->*f)(x); }

private:
    S (T::*f)(A) const;
};

int main() {
    std::vector<std::string *> numbers;

    // populate vector of pointers:
    numbers.push_back(new std::string("one"));
    numbers.push_back(new std::string("two"));
    numbers.push_back(new std::string("three"));
    numbers.push_back(new std::string("four"));
    numbers.push_back(new std::string("five"));

    std::vector<int> lengths(numbers.size());//预先分配内存空间

    transform(numbers.begin(), numbers.end(), lengths.begin(), mem_fun(&std::string::length));

    for (int i = 0; i < 5; i++) {
        std::cout << *numbers[i] << " has " << lengths[i] << " letters.\n";
    }

    // deallocate strings:
    for (auto &number : numbers) delete number;

    return 0;
}