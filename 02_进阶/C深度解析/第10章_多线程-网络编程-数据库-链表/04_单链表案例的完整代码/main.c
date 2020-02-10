#include <stdio.h>
#include "sList.h"

//文件路径名
//#define FILE_PATH "C:\\Users\\Administrator\\Desktop\\StuFile.txt"  //windows
#define FILE_PATH "/home/zxf/Desktop/sList/StuFile.txt"    						//Linux

#define SHOW                1
#define FIND                2
#define READ_KEYBORD        3
#define ALTER               4
#define SAVE                5
#define DELETE              6
#define EMPTY               7
#define EXIT                8

/* 功能：交互函数
 * 参数：无
 * 返回值：选择
 */
int interactive(void)
{
    printf("1. 打印显示所有信息\n");
    printf("2. 按照学号查找，并打印学生信息\n");
    printf("3. 从键盘输入一条学生信息，然后插入链表\n");
    printf("4. 修改学生信息\n");
    printf("5. 保存链表到文件中\n");
    printf("6. 删除某个学生的信息\n");
    printf("7. 清空链表\n");
    printf("8. 退出程序，并销毁链表\n");

    int select = 0;
    scanf("%d", &select);

    return select; //返回选择
}

int main(void)
{
    SNode *hp = NULL;

    /* 创建空链表 */
    createList(&hp);

    /* 读取文件数据 */
    ReadDataFromFileToList(hp, FILE_PATH);

    /* 操作链表 */
    while(1)
    {
        //interactive为交互函数
        switch(interactive())
        {
            case SHOW:  //显示所有链表信息
                ShowList(hp);
                break;
            case FIND:  //按照学号查找
                FindStuByNumber(hp);
                break;
            case READ_KEYBORD:  //从键盘输入信息
                ReadDataFromKeybordToList(hp);
                break;
            case ALTER: //修改信息
                AlterNode(hp);
                break;
            case SAVE: //保存到文件中
                SaveListToFile(hp, FILE_PATH);
                break;
            case DELETE: //删除某个学生
                DeleteStu(hp);
                break;
            case EMPTY: //清空链表
                EmptyList(hp);
                break;
            case EXIT: //退出程序，并销毁链表
                DestroyList(hp); //销毁链表
                return 0;  //main函数退出，整个程序结束
                break;
            default: 
                printf("无此选项\n");
        }
    }

    return 0;
}
