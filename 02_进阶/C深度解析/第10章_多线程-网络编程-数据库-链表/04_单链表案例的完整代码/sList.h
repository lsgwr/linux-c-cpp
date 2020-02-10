#ifndef H_SLIST_H
#define H_SLIST_H
#include "sList_base_op.h"

/* 学生结构体(存放数据的结构体) */
typedef struct Student
{
    char name[40];
    int  number;
    char gender;
}Stu;

/* 功能函数的声明 */
extern void createList(SNode **hpp);
extern void ReadDataFromFileToList(SNode *hp, char *fileName);
extern void ShowList(SNode *hp);
extern SNode *FindStuByNumber(SNode *hp);
extern void ReadDataFromKeybordToList(SNode *hp);
extern void AlterNode(SNode *hp);
extern void SaveListToFile(SNode *hp, char *fileName);
extern void DeleteStu(SNode *hp);
extern void EmptyList(SNode *hp);
extern void DestroyList(SNode *hp);

#endif
