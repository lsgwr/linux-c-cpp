/* 直接插入排序函数 */
void insert_sort(int * array, int length)
{
	int i,j;
	
	for(i = 1; i < length; i++){ /* 控制循环的次数 */
		int temp;
		
		j = i;
		temp = array[j]; /* 临时值的赋值 */
		
		while(j > 0){
			if(temp < array[j - 1]){ /* 移动后面的所有数组元素 */
				array[j] = array[j - 1];
				j--;
			}else 
				break;		/* 跳出循环 */
		}	
		array[j] = temp;	/* 临时值保存在适当的位置上 */
	} 	
}

/* 二分查找函数 */
int binary_search(int * array, int item, int length)
{
	int high, low, mid;
	
	high = length - 1;		/* 高端 */
	low = 0;				/* 低端 */
	mid = (high + low)/2;	/* 中间位置 */
	
	while(low <= high){ /* 当高端大于低端时开始循环 */
		if(array[mid] > item){ /* 是否大于中点的元素 */
			high = mid;
			mid = (high + low)/2;	
		}else if(array[mid] < item){ /* 是否小于中点的元素 */
			low = mid;
			mid = (high + low)/2;
		}else
			return mid;	/* 等于中点元素，则返回该元素 */
	}
	return -1;			/* 否则没有找到该元素 */
}

/* 冒泡排序函数 */
void bubble_sort(int * array, int length)
{
	int i, j;
	int exchange;
	int temp;
	
	i = 0;
	exchange = 1;					/* 是否交换的标志位 */
	
	while(i < length && exchange){	/* 当上一趟循环没有交换元素时，停止循环 */
		j = length - 1;
		exchange = 0;				/* 清空交换元素标志 */

		while(j >= i){
			if(array[j] < array[j - 1]){ /* 如果两个元素逆序，则交换两个元素 */
				temp = array[j];
				array[j] = array[j - 1];
				array[j - 1] = temp;
				exchange = 1;		/* 设置交换元素标志位 */
			}	
			j--;
		}
		i++; 						/* 总的循环次数累加 */
	} 	
}

