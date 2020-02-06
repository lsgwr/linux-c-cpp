/***********************************************************
 * @Description : P17_为数组和链表编制共同的显示函数
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 16:22
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <iostream>

using namespace std;

template<class T>
class MyArray {
private:
    /**
     * 数组总长度
     */
    int m_nTotalSize;
    /**
     *  数组有效长度
     */
    int m_nValidSize;
    /**
     *  数据
     */
    T *m_pData;

public:
    /**
     * 构造函数
     * @param nSize 数组的长度，这里默认为3
     */
    MyArray(int nSize = 3) {
        // m_pData是初始长度为nSize的T类型的数组，后面会对这个数组进行动态扩缩容
        m_pData = new T[nSize];
        m_nTotalSize = nSize;
        m_nValidSize = 0;
    }

    /**
     * 向m_pData中添加数据
     * @param val
     */
    void add(T val) {
        if (m_nValidSize >= m_nTotalSize) {
            // 有效长度大于等于数据的总长度了，则需要进行扩容
            // 1.原始数据备份
            T *tmpData = new T[m_nTotalSize];
            for (int i = 0; i < m_nTotalSize; ++i) {
                tmpData[i] = m_pData[i];
            }
            delete[]m_pData;
            // 2.空间扩容至原来的2倍
            m_nTotalSize *= 2;
            m_pData = new T[m_nTotalSize];
            for (int i = 0; i < m_nValidSize; ++i) {
                m_pData[i] = tmpData[i];
            }
            delete[]tmpData;
        }
        // 把新来的值赋给数组，有效长度+1
        m_pData[m_nValidSize++] = val;
    }

    /**
     * 获取数组的有效长度
     * @return 数据有效长度
     */
    int getSize() {
        return m_nValidSize;
    }

    /**
     * 获取指定位置的元素
     * @param index 在数组中的下标
     * @return 下标对应的元素
     */
    int get(int index) {
        return m_pData[index];
    }

    T *begin() {
        return m_pData;
    }

    T *end() {
        return m_pData + m_nValidSize;
    }

    /**
     * 虚函数，用于类的声明周期结束时释放资源
     */
    virtual ~MyArray() {
        if (m_pData != NULL) {
            delete[]m_pData;
            m_pData = NULL;
        }
    }
};


template<class T>
struct Node {
    T val;
    Node *next;
};

template<class T>
class MyLink {
    Node<T> *head;
    Node<T> *tail;
    Node<T> *prev;

public:
    MyLink() {
        head = tail = prev = NULL;
    }

    void add(T &val) {
        Node<T> *pNode = new Node<T>();
        pNode->val = val;
        pNode->next = NULL;
        if (head == NULL) {
            head = pNode;
            prev = pNode;
        } else {
            prev->next = pNode;
            prev = pNode;
        }
        tail = pNode->next;
    }

    Node<T> *begin() {
        return head;
    }

    Node<T> *end() {
        return tail;
    }

    virtual ~MyLink() {
        if (head != NULL) {
            Node<T> *cur = head;
            Node<T> *next = NULL;
            while (cur != tail) {
                next = cur->next;
                delete cur;
                cur = next;
            }
        }
    }
};

// 重载全局输出函数
template<class T>
ostream &operator<<(ostream &os, Node<T> &s) {
    os << s.val;
    return os;
}

template<class Init>
void display(Init start, Init end) {
    for (Init cur = start; cur != end; cur++) {
        cout << "\t" << *cur;
    }
    cout << endl;
}

template<class Init>
class ArrayIterator {
    Init *init;

public:
    ArrayIterator(Init *init) : init(init) {}

    bool operator!=(ArrayIterator &it) {
        return this->init != it.init;
    }

    void operator++(int) {
        init++;
    }

    Init operator*() {
        return *init;
    }

};

template<class Init>
class LinkIterator {
    Init *init;

public:
    LinkIterator(Init *init) {
        this->init = init;
    }

    bool operator!=(LinkIterator &it) {
        return this->init != it.init;
    }

    void operator++(int) {
        init = init->next;
    }

    Init operator*() {
        return *init;
    }

};


int main() {
    // 1.数组迭代器测试
    MyArray<int> arr;
    for (int i = 0; i < 5; ++i) {
        arr.add(i + 1);
    }
    ArrayIterator<int> start(arr.begin());
    ArrayIterator<int> end(arr.end());
    cout << "数组元素为：";
    display(start, end);

    // 2.链表迭代器测试
    int m = 0;
    MyLink<int> linkedList;
    for (int i = 0; i < 5; ++i) {
        m = i + 1;
        linkedList.add(m);
    }
    LinkIterator<Node<int>> start2(linkedList.begin());
    LinkIterator<Node<int>> end2(linkedList.end());
//    display(start2, end2);
    return 0;
}