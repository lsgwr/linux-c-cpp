#ifndef H_SLIST_H
#define H_SLIST_H
#include "dList_base_op.h"

/* 学生结构体(存放数据的结构体) */
typedef struct Student
{
    char name[40];
    int  number;
    char gender;
}Stu;

/* 功能函数的声明 */
extern void createList(DNode **hpp);
extern void ReadDataFromFileToList(DNode *hp, const char *fileName);
extern void ShowList(const DNode *hp);
extern DNode *FindStuByNumber(const DNode *hp);
extern void ReadDataFromKeybordToList(DNode *hp);
extern void AlterNode(const DNode *hp);
extern void SaveListToFile(const DNode *hp, const char *fileName);
extern void DeleteStu(const DNode *hp);
extern void EmptyList(const DNode *hp);
extern void DestroyList(const DNode *hp);

#endif
