/***********************************************************
 * @Description : 动态数组的模板类
 * @author      : 梁山广(Laing Shan Guang)
 * @date        : 2020/2/6 09:57
 * @email       : liangshanguang2@gmail.com
 ***********************************************************/
#include <cstdio>

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


int main() {
    MyArray<int> list;
    list.add(1);
    list.add(2);
    printf("%d\n", list.getSize());
    list.add(3);
    printf("%d\n", list.getSize());
    list.add(4);
    printf("%d\n", list.getSize());
    for (int i = 0; i < list.getSize(); ++i) {
        printf("%d\n", list.get(i));
    }
    return 0;
}