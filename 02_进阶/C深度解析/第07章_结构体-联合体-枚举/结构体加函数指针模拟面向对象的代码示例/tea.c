#include <stdio.h>
#include "public.h"
#include "tea.h"

static struct Register reg = {0};

void Tea_initFun(int n, Tea buf[])
{
    reg.n = n;
    reg.buf = (void *)buf;
    reg.print = Tea_print;
    reg.alter = Tea_alter;

    registerFun(&reg);
}

static void Tea_alter(int n, void *buf)
{
    int i = 0;
    int teaNum;
    Tea *tea = (Tea *)buf;

    printf("输入教师编号: \n");
    scanf("%d", &teaNum);

    for(i=0; i<n; i++)
    {
        if(tea[i].teaNum == teaNum)
        {
            printf("%s %d %d\n", tea[i].name, tea[i].teaNum, tea[i].grade);
            printf("输入新信息\n");
            scanf("%s %d %d", tea[i].name, &tea[i].teaNum, &tea[i].grade);
            break;
        }
    }
}

static void Tea_print(int n, void *buf)
{
    int i = 0;
    Tea *tea = (Tea *)buf;

    for(i=0; i<n; i++)
    {
            printf("%s %d %d级\n", tea[i].name, tea[i].teaNum, tea[i].grade);
    }
}
