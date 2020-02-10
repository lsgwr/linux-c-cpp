#include <stdio.h>
#include "sList.h"

/* 功能：创建一个空链表
 * 参数：
 *      hpp：头指针变量的指针（地址）
 * 返回值：无
 */
void createList(SNode **hpp)
{
    //创建一个空间点作为头节点，由于空节点没有数据，所以参数传NULL和0
    *hpp = Sig_CreateNode(NULL, 0);

    //保险起见，给头节点next再赋一次NULL
    (*hpp)->next = NULL;
}

/* 功能：读取文件中的学生信息，然后保存到单链表中
 *       如果文件中没有数据，链表就是一个空链表，我们可以选择从键盘输入学生数据
 * 参数：
 *      hp：头指针变量
 * 返回值：无
 */
void ReadDataFromFileToList(SNode *hp, char *fileName)
{
    /* 打开存放学生信息的文件 */
    FILE *fp = fopen(fileName, "r+"); 
    if(NULL == fp) print_error("fopen");

    /* 循环读取文件内容，每读出一条，就存入创建的节点中
     * feof函数检测读到文件末尾时，就退出循环
    */
    Stu stu = {}; //暂存读出的数据
    while(1)
    {
        /* 格式化读文件，每次只读出一条，name是数组，就不要再&取地址了 */
        fscanf(fp, "%s %d %c", stu.name, &stu.number, &stu.gender);

        /* feof返回非零时，就表示读到末尾了，然后退出循环 */
        if(feof(fp) != 0) break;

        /* 创建节点，将数据保存到节点中data所代表的数据空间 */
        SNode *nodep = Sig_CreateNode((void *)&stu, sizeof(stu));

        /* 将节点插入链表，我们这里选择都在链表头部插入 */
        Sig_HeadInertNode(hp, nodep);
    }

    fclose(fp);
}

/* 功能：遍历每一个节点，并打印出每个节点的学生数据
 * 参数：
 *   hp：头指针
 * 返回值：无
 */
void ShowList(SNode *hp)
{
    SNode *p = hp->next;
    Stu *datap = NULL;

    if(NULL == p) printf("链表为空\n");
    else
    {
        /* 遍历链表，找到每个节点，打印学生信息 */
        while(1)
        {
            if(NULL == p) break;   //判断是否到了末尾
            datap = (Stu *)p->data; //将void *强制转为Stu *
            printf("%s %d %c\n", datap->name, datap->number, datap->gender);//打印节点中的学生信息

            p = p->next; //指向下一个节点
        }
    }
}

/* 功能：遍历链表，通过学号查找学生信息
 * 参数：
 *   hp：头指针
 *   number：要查找的学号
 * 返回值：返回找到节点的上一个节点的指针
 *   之所以返回上一个节点，是因为想方便后续的删除和插入操作
 */
SNode *FindStuByNumber(SNode *hp)
{
    SNode *p = hp; //指向头节点
    Stu *datap = NULL;
    int number = 0;

    if(NULL == p) printf("链表为空\n");
    else
    {
        printf("输入学号\n");
        scanf("%d", &number);
        /* 遍历链表，找到每个节点，通过比对学号找到某学生信息 */
        while(1)
        {
            if(NULL == p->next) break;    //判断是否到了末尾

            datap = (Stu *)p->next->data; //暂存节点中数据指针
            if(datap->number == number)
            {
                printf("%s %d %c\n", datap->name, datap->number, datap->gender);//打印节点中的学生信息
                break;
            }
            p = p->next; //指向下一个节点
        }
    }

    return p;  //返回被早到节点的上一个节点
}

/* 功能：从键盘输入一条学生信息然后插入链表的头，
 *      当然你也可以插入链表中的任何位置，我们这里简单一点，直接插入到链表头
 * 参数：
 *   hp：头指针
 * 返回值：无
 */
void ReadDataFromKeybordToList(SNode *hp)
{
    int select = 0;
    Stu stu = {};
    SNode *nodep = NULL;
    SNode *temp = NULL;

    printf("%s %d %c\n", stu.name, stu.number, stu.gender);
    printf("请输入学生信息，输入格式为：名字 学号 性别（M/F）\n");
    scanf("%s %d %c", stu.name, &stu.number, &stu.gender);

    /* 创建节点，将数据保存到节点中data所代表的数据空间 */
    nodep = Sig_CreateNode((void *)&stu, sizeof(stu));

    printf("1. 插入链表头部\n");
    printf("2. 插入链尾部\n");
    printf("3. 插入指定位置\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            Sig_HeadInertNode(hp, nodep);
            break;
        case 2:
            Sig_TailInertNode(hp, nodep);
            break;
        case 3:
            ShowList(hp);  //显示整个链表，方便寻找插入位置
            temp = FindStuByNumber(hp); //返回要插入位置的上一个节点的指针
            Sig_InsertNode(temp, nodep);//调用同样插入函数，将nodep插入到temp所指节点的后面
            break;
        default:
            printf("无此选项\n");
    }
}

/* 功能：通过学号找到学生信息，然后修改
 * 参数：
 *   hp：头指针
 *   number：要查找的学号
 * 返回值：无
 */
void AlterNode(SNode *hp)
{
    SNode *tmp = NULL;
    Stu *datap = NULL;

    /* 调用FindStuByNumber函数，
     * 按照学号查找，找到后返回节点指针 */
    tmp = FindStuByNumber(hp);

    if(tmp->next == NULL) printf("没有找到\n");
    else
    {
        //暂存节点中数据空间的指针，以方便操作，不过需要将void *强制转为Stu
        datap = (Stu *)tmp->next->data;
        printf("输入新信息，格式：名字 学号 性别\n");
        scanf("%s %d %c", datap->name, &datap->number, &datap->gender);
    }
}

/* 功能：将链表中的数据保存到文件中
 * 参数：
 *   hp：头指针
 * 返回值：无
 */
void SaveListToFile(SNode *hp, char *fileName)
{
    SNode *p = hp->next;
    Stu *datap = NULL;

    /* 以w方式打开（只写），并将文件内容清空，清空后
     * 再重新将被修改后的链表中的数据写入文件中 */
    FILE *fp = fopen(fileName, "w"); 
    if(NULL == fp) print_error("fopen");

    /* 遍历链表，找到每个节点，通过比对学号找到某学生信息 */
    while(1)
    {
        if(NULL == p) break;    //判断是否到了末尾
        datap = (Stu *)p->data; //将void *强制转为Stu *
        fprintf(fp, "%s %d %c\n", datap->name, datap->number, datap->gender);//打印节点中的学生信息

        p = p->next; //指向下一个节点
    }
    //关闭文件，并将数据从库缓存刷新到文件中
    fclose(fp);
}

/* 功能：删除某个学生信息
 * 参数：
 *   hp：头指针
 * 返回值：无
 */
void DeleteStu(SNode *hp)
{
    //通过学号找到节点
    SNode *p = FindStuByNumber(hp);

    //删除节点
    Sig_DeleteNode(p);
}

/* 功能：删除所有的数据节点，只保留头节点
 * 参数：
 *   hp：头指针
 * 返回值：无
 */
void EmptyList(SNode *hp)
{
    while(1)
    {
        if(hp->next == NULL) break;
        Sig_DeleteNode(hp);
    }
    printf("链表已被清空\n");
}

/* 功能：将数据节点和头节点都删除，整个链表就被销毁了
 * 参数：
 *   hp：头指针
 * 返回值：无
 */
void DestroyList(SNode *hp)
{
    //删除所有数据节点
    EmptyList(hp);

    //删除头节点
    free(hp);
    hp = NULL;
    printf("链表已被销毁");
}
