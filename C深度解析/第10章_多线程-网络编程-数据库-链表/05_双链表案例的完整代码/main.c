#include <stdio.h>
#include "dList.h"

//文件路径名
#define FILE_PATH "C:\\Users\\Administrator\\Desktop\\StuFile.txt"

#define SHOW                1
#define FIND                2
#define READ_KEYBORD        3
#define ALTER               4
#define SAVE                5
#define DELETE              6
#define EMPTY               7
#define SORT                8
#define EXIT                9

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
    printf("8. 按学号进行从小到大排序\n");
    printf("9. 退出程序，退出前先销毁链表\n");

    int select = 0;
    scanf("%d", &select);

    return select; //返回选择
}

int main(void)
{
    DNode *hp = NULL;

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
            case SORT: //清空链表
                BubbleSort(hp);
                break;
            case EXIT: //销毁链表
                DestroyList(hp);
                printf("退出程序\n");
                return 0;
                break;
            default: 
                printf("无此选项\n");
        }
    }

    return 0;
}
