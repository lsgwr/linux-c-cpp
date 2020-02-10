#include <stdio.h>
#include "public.h"
#include "stu.h"

//用于封装操作学生的基本信息
static struct Register reg = {}; //初始化为0

/* 功能:初始化操作,向"公共代码"注册操作学生的信息
 *      注册的信息为"学生结构体素组" 和 "操作学生数据的函数"
 * 参数:
 *   n: 学生结构体数组的元素个数
 *   buf: 数组首元素指针
 */
void Stu_initFun(int n, Stu buf[])
{
    /* 使用struct Register结构体封装操作学生的信息 */
    reg.n = n;                      //学生结构体数组的大小
    reg.buf = (void *)buf;          //学生数组的首元素指针,公共代码不区分具体的类型 
    reg.print = Stu_print;          //打印学生数据的函数指针,让公共代码回调 
    reg.alter = Stu_alter;          //修改学生数据的函数指针,让公共代码回调

    /* 向公共代码注册,所谓注册就
     * 是将封装的结构体传递公共代码,
     * 让公共代码通过这些信息来操作学生数据 */
    registerFun(&reg);
}


/* 功能: 通过学号找打某个学生,然后修改学生数据
 *       这个函数由"公共代码"回调,公共代码会讲数组的n和buf传递回来 
 * 
 * 参数: 
 *  n:数组元素个数
 *  buf: 数组的首元素指针
 *       公共代码只记录存储的地址,不区分具体的类型,所以为void *
*/
static void Stu_alter(int n, void *buf)
{
    int i = 0;
    int stuNum;
    Stu *stu = (Stu *)buf;                  //强制转为具体Stu *, 如此才能进行具体的操作

    printf("输入学号: ");
    scanf("%d", &stuNum);

    for(i=0; i<n; i++)
    {
        if(stu[i].stuNum == stuNum)     //进行学号比对
        {
            printf("%s %d %f\n", stu[i].name, stu[i].stuNum, stu[i].score);

            printf("输入新信息\n");
            scanf("%s %d %f", stu[i].name, &stu[i].stuNum, &stu[i].score);
            break;
        }
    }

    if(i == n) printf("无此学生\n");

}

/* 功能: 显示所有学生的信息, 由"公共代码"回调
 * 参数: 同Stu_alter
*/
static void Stu_print(int n, void *buf)
{
    int i = 0;
    Stu *stu = (Stu *)buf;

    for(i=0; i<n; i++)
    {
        printf("%s %d %f分\n", stu[i].name, stu[i].stuNum, stu[i].score);
    }
}
