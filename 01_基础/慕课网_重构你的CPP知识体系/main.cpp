#include <algorithm>
#include <iostream>

using namespace std;

bool MySort(int a, int b) {
    return a < b;
}

void Display(int a) {
    cout << a << " ";
}

template<class T>
inline bool MySortT(T const &a, T const &b) {
    return a < b;
}

template<class T>
inline void DisplayT(T const &a) {
    cout << a << " ";
}

struct SortF {
    bool operator()(int a, int b) {
        return a < b;
    }
};

struct DisplayF {
    void operator()(int a) {
        cout << a << " ";
    }
};

// C++仿函数模板
template<class T>
struct SortTF {
    inline bool operator()(T const &a, T const &b) const {
        return a < b;
    }
};

template<class T>
struct DisplayTF {
    inline void operator()(T const &a) const {
        cout << a << " ";
    }
};


int main() {
    // C++方式
    int arr[] = {4, 3, 2, 1, 7};
    sort(arr, arr + 5, MySort);
    for_each(arr, arr + 5, Display); // 1 2 3 4 7
    cout << endl;

    // C++泛型
    int arr2[] = {4, 3, 2, 1, 7};
    sort(arr2, arr2 + 5, MySortT<int>);
    for_each(arr2, arr2 + 5, DisplayT<int>); // 1 2 3 4 7
    cout << endl;

    // C++仿函数
    int arr3[] = {4, 3, 2, 1, 7};
    sort(arr3, arr3 + 5, SortTF<int>());
    for_each(arr3, arr3 + 5, DisplayTF<int>()); // 1 2 3 4 7
    cout << endl;

    // C++仿函数模板
    int arr4[] = {4, 3, 2, 1, 7};
    sort(arr4, arr4 + 5, SortF());
    for_each(arr4, arr4 + 5, DisplayF()); // 1 2 3 4 7
    cout << endl;

    return 0;
}