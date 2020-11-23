/***********************************************************
 * @Description : 顺序表
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/11/23 23:06
 * @email       : liangshanguang2@gmail.com
***********************************************************/

#ifndef FUNCALGOCPP_SEQLIST_H
#define FUNCALGOCPP_SEQLIST_H

#include <iostream>

using namespace std;

const int defaultSize = 10; // 设置默认顺序表大小

template<typename T>
class SeqList {
private:
    T *arr;
    int maxSize;
    int len;

public:
    SeqList(int size = defaultSize) {
        if (size > 0) { // size合法才分配内存
            maxSize = size;
            arr = new T[maxSize];
        }
    }

    ~SeqList() {
        delete[] arr;
    }


    int getLen() const; // 获取顺序表的长度
    bool insert(T e); // 向表尾插入元素
    bool del(int loc); // 删除指定位置的元素
    T get(int loc); // 获取指定位置的元素
    bool update(int loc, T eNew); // 更新指定位置的元素
};

template<typename T>
bool SeqList<T>::insert(T e) {
    int cur = len; // 记录新元素的插入位置
    if (len >= maxSize) { // 检查顺序表是否已经满了
        return false; // 顺序表已经满了，返回false，即插入不成功
    } else {
        arr[cur] = e; // 将新元素插入到顺序表表尾
        len++; // 顺序表有效长度+1
        return true;
    }
}

template<typename T>
bool SeqList<T>::del(int loc) {
    if (loc >= len || loc < 0) { // 验证位置索引参数是否有效
        return false;
    } else {
        for (int i = loc; i < len; i++) {
            arr[i] = arr[i + 1]; // 将指定位置之后的元素依次往前覆盖一个位置
        }
        len--;
        return true;
    }
}

template<typename T>
T SeqList<T>::get(int loc) {
    if (loc < 0 || loc > len) {
        cout << "参数无效" << endl;
        return 0;
    } else {
        return arr[loc];
    }
}

template<typename T>
bool SeqList<T>::update(int loc, T eNew) {
    if (loc <0 || loc >= len) {
        return false;
    } else {
        arr[loc] = eNew;
        return true;
    }
}

template<typename T>
int SeqList<T>::getLen() const {
    return len;
}

#endif //FUNCALGOCPP_SEQLIST_H
