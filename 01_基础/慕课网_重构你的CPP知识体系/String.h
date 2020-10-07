/***********************************************************
 * @Description : 
 * @author      : 梁山广(Liang Shan Guang)
 * @date        : 2020/10/7 21:50
 * @email       : liangshanguang2@gmail.com
***********************************************************/
//
// Created by pc on 2020/10/7.
//

#ifndef _CPP_STRING_H
#define _CPP_STRING_H

#include <iostream>
#include <cstring>

using namespace std;

class String
{
public:
    String(const char *str = NULL);                    // 普通构造函数
    String(const String &other);                       // 拷贝构造函数
    String(String&& other);                            // 移动构造函数
    ~String(void);                                     // 析构函数
    String& operator= (const String& other);           // 赋值函数
    String& operator=(String&& rhs)noexcept;		   // 移动赋值运算符

    friend ostream& operator<<(ostream& os, const String &c); // cout输出

private:
    char *m_data; // 用于保存字符串
};
#endif //_CPP_STRING_H
