#include <stdio.h>
#include "dList.h"

/* 功能：创建一个空链表
 * 参数：
 *      hpp：头指针变量的指针（地址）
 * 返回值：无
 */
void createList(DNode **hpp)
{
    //创建一个空间点作为头节点，由于空节点没有数据，所以参数传NULL和0
    *hpp = Dou_CreateNode(NULL, 0);

    //保险起见，给头节点next、prev放自己的地址
    //如此就做成了双向循环链表
    (*hpp)->next = (*hpp)->prev = *hpp;
}

/* 功能：读取文件中的学生信息，然后保存到单链表中
 *       如果文件中没有数据，链表就是一个空链表，我们可以选择从键盘输入学生数据
 * 参数：
 *      hp：头指针变量
 * 返回值：无
 */
void ReadDataFromFileToList(DNode *hp, const char *fileName)
{
    /* 打开存放学生信息的文件 */
    FILE *fp = fopen(fileName, "r+"); //FILE_PATH定义在了sList.h中
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
        DNode *nodep = Dou_CreateNode((void *)&stu, sizeof(stu));

        /* 将节点插入链表，我们这里选择都在链表头部插入 */
        Dou_TailInertNode(hp, nodep);
    }

    fclose(fp);
}


/* 功能：遍历每一个节点，并打印出每个节点的学生数据
 * 参数：
 *   hp：头指针
 * 返回值：无
 */
void ShowList(const DNode *hp)
{
    DNode *p = hp->next;
    Stu *datap = NULL;

    if(hp == p) printf("链表为空\n");
    else
    {
        /* 遍历链表，找到每个节点，打印学生信息 */
        while(1)
        {
            if(hp == p) break; //如果p指向了头节点，表示遍历结束了
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
 * 返回值：无
 */
DNode *FindStuByNumber(const DNode *hp)
{
    DNode *p = hp->next;
    Stu *datap = NULL;
    int number = 0;

    if(hp == p) printf("链表为空\n");
    else
    {
        printf("输入学号\n");
        scanf("%d", &number);
        /* 遍历链表，找到每个节点，通过比对学号找到某学生信息 */
        while(1)
        {
            if(hp == p) break;    //判断是否到了末尾

            datap = (Stu *)p->data; //暂存节点中数据指针
            if(datap->number == number)
            {
                printf("%s %d %c\n", datap->name, datap->number, datap->gender);//打印节点中的学生信息
                break;
            }
            p = p->next; //指向下一个节点
        }
    }

    return p;
}

/* 功能：从键盘输入一条学生信息然后插入链表的头，
 *      当然你也可以插入链表中的任何位置，我们这里简单一点，直接插入到链表头
 * 参数：
 *   hp：头指针
 * 返回值：无
 */
void ReadDataFromKeybordToList(DNode *hp)
{
    int select = 0;
    Stu stu = {};
    DNode *nodep = NULL;
    DNode *temp = NULL;

    printf("%s %d %c\n", stu.name, stu.number, stu.gender);
    printf("请输入学生信息，输入格式为：名字 学号 性别（M/F）\n");
    scanf("%s %d %c", stu.name, &stu.number, &stu.gender);

    /* 创建节点，将数据保存到节点中data所代表的数据空间 */
    nodep = Dou_CreateNode((void *)&stu, sizeof(stu));

    printf("1. 插入链表头部\n");
    printf("2. 插入链尾部\n");
    printf("3. 插入指定位置\n");
    scanf("%d", &select);
    switch(select)
    {
        case 1:
            Dou_HeadInertNode(hp, nodep);
            break;
        case 2:
            Dou_TailInertNode(hp, nodep);
            break;
        case 3:
            ShowList(hp);  //显示所有学生信息，方便查看
            temp = FindStuByNumber(hp);  //查找要插入的位置
            printf("1. 插入到前面\n");
            printf("2. 插入到后面\n");
            scanf("%d", &select);
            if(select == 1)      Dou_InsertNodeBefore(temp, nodep);
            else if(select == 2) Dou_InsertNodeAfter(temp, nodep);
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
void AlterNode(const DNode *hp)
{
    DNode *tmp = NULL;
    Stu *datap = NULL;

    /* 调用FindStuByNumber函数，
     * 按照学号查找，找到后返回节点指针 */
    tmp = FindStuByNumber(hp);

    if(tmp == hp) printf("没有找到\n");
    else
    {
        //暂存节点中数据空间的指针，以方便操作，不过需要将void *强制转为Stu
        datap = (Stu *)tmp->data;
        printf("输入新信息，格式：名字 学号 性别\n");
        scanf("%s %d %c", datap->name, &datap->number, &datap->gender);
    }
}

/* 功能：将链表中的数据保存到文件中
 * 参数：
 *   hp：头指针
 * 返回值：无
 */
void SaveListToFile(const DNode *hp, const char *fileName)
{
    DNode *p = hp->next;
    Stu *datap = NULL;

    /* 以w方式打开（只写），并将文件内容清空，清空后
     * 再重新将被修改后的链表中的数据写入文件中 */
    FILE *fp = fopen(fileName, "w");
    if(NULL == fp) print_error("fopen");

    /* 遍历链表，找到每个节点，通过比对学号找到某学生信息 */
    while(1)
    {
        if(hp == p) break;    //判断是否到了末尾
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
 * 返回值：无51
 */
void DeleteStu(const DNode *hp)
{
    //通过学号找到节点
    DNode *p = FindStuByNumber(hp);

    //删除节点
    Dou_DeleteNode(p);
}

/* 功能：删除所有的数据节点，只保留头节点
 * 参数：
 *   hp：头指针
 * 返回值：无
 */
void EmptyList(const DNode *hp)
{
    DNode *p = NULL;

    //先删除
    while(1)
    {
         p = hp->next;  //指向第一个数据
         if(p == hp) break;
         Dou_DeleteNode(p);
    }
    printf("链表已被清空\n");
}

/* 功能：将数据节点和头节点都删除，整个链表就被销毁了
 * 参数：
 *   hp：头指针
 * 返回值：无
 */
void DestroyList(const DNode *hp)
{
    //删除所有数据节点
    EmptyList(hp);

    //删除头节点
    free(hp);
    hp = NULL;
    printf("链表已被删除\n");
}


/* 功能：按学号的从小到大排序
 * 参数：hp：头指针
 * 返回值：无
 */
void BubbleSort(const DNode *hp)
{
    DNode *p     = NULL; //指向第一个节点
    DNode *lastp = hp->prev; //指向最后一个节点
    Stu *datap = NULL;
    Stu *nextNodeDatap = NULL;
    Stu *temp = NULL;

    while(1)
    {
        if(lastp->prev == hp) break;
        p = hp->next; //指向第一个节点

        while(1)
        {
            if(p == lastp) break;
            datap = (Stu *)(p->data);
            nextNodeDatap = (Stu *)(p->next->data);
            if((datap->number) >= (nextNodeDatap->number))
            {
                    temp = p->next->data;
                    p->next->data = p->data;
                    p->data = temp;
            }
            p = p->next;
        }
        lastp = lastp->prev;
    }
    printf("冒泡排序结束\n");
}
