#include "common.h"
/* 创建一个图书结构，并将其插入到指定的位置
* pos : 保存新创建的结构体的数组的指针，注意这是一个指向Book指针类型的指针
* id : 新结构体的id
* name : 新结构体的name
* 如果成功创建一个新结构并将其设置到指定位置，则返回0，失败则返回-1
*/
int insert_struct(Book *pos, int id, char *name)
{
	Book p;

	p = (Book)malloc(sizeof(struct book)); /* 分配一个空间 */
	if(p == NULL){
		perror("fail to malloc");
		return -1;
	}

	p->id = id;
	strcpy(p->name, name); /* 对结构体变量进行赋值 */

	*pos = p; /* 将结构体变量赋值到数组中 */
	
	return 0;
}

/* 为了统一模式，添加一个插入整型元素的函数，这个函数也可以不要 */
int insert_int(int **pos, int val)
{
	int *p;
	
	p = (int *)malloc(sizeof(int)); /* 分配一个整型数据 */

	*p = val; /* 将整型数据的值赋值到新分配的空间中 */
	*pos = p; /* 将整型数据设置到数组中 */
	
	return 0;
}
