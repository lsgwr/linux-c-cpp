/***********************************************************
 * @Description : 深拷贝与浅拷贝
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/10/7 21:50
 * @email       : liangshanguang2@gmail.com
***********************************************************/
#include "String.h"

// String 的普通构造函数
String::String(const char *str) {
    if (str == NULL) {
        m_data = new char[1];
        if (m_data != NULL) {
            *m_data = '\0';
        } else {
            exit(-1);
        }
    } else {
        int len = strlen(str);
        m_data = new char[len + 1];
        if (m_data != NULL) {
            strcpy(m_data, str);
        } else {
            exit(-1);
        }
    }
}

// 拷贝构造函数
String::String(const String &other) {
    int len = strlen(other.m_data);
    m_data = new char[len + 1];
    if (m_data != NULL) {
        strcpy(m_data, other.m_data);
    } else {
        exit(-1);
    }
}

// 移动构造函数
String::String(String &&other) {
    if (other.m_data != NULL) {
        // 资源让渡
        m_data = other.m_data;
        other.m_data = NULL;
    }
}


// 赋值函数
String &String::operator=(const String &other) {
    if (this == &other) {
        return *this;
    }
    // 释放原有的内容
    delete[] m_data;
    // 重新分配资源并赋值
    int len = strlen(other.m_data);
    m_data = new char[len + 1];
    if (m_data != NULL) {
        strcpy(m_data, other.m_data);
    } else {
        exit(-1);
    }

    return *this;
}

// 移动赋值运算符
String &String::operator=(String &&rhs) noexcept {
    if (this != &rhs) {
        delete[] m_data;
        m_data = rhs.m_data;
        rhs.m_data = NULL;
    }
    return *this;
}

// String 的析构函数
String::~String(void) {
    if (m_data != NULL) {
        delete[] m_data;
    }
}

ostream &operator<<(ostream &os, const String &c) {
    os << c.m_data;
    return os;
}