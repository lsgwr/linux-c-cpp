//
// Created by 梁山广 on 2018/1/13.
//

#ifndef LINUXCSTUDY_LIST_H
#define LINUXCSTUDY_LIST_H

extern int insert(int val);

extern void print();

extern void destroy();

/**
 * 可变参数函数，其中第一个参数的类型是固定的，在定义的时候必须已经定义好,传入的为NULL的话那么久自动忽略掉
 */
extern int print_args(int begin, ...);

#endif //LINUXCSTUDY_LIST_H
