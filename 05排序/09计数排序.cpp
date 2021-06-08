#include<iostream>
using namespace std;

void CountingSort(int *arr, int size)
{
	int minValue = arr[0];  //通过maxValue和minValue计算出临时数组所需要开辟的空间大小
	int maxValue = arr[0];
	int* tmp = 0;
	int count = 0;
	for (int i = 0; i < size; i++)  //找出待排序的数组中最大和最小的元素
	{
		if (arr[i] < minValue) 
			minValue = arr[i];
		if (arr[i] > maxValue)
			maxValue = arr[i];
	}
	int range = maxValue - minValue + 1;  //计算数据的分散空间
	tmp = (int*)malloc(sizeof(arr[0])*size);  //申请辅助空间
	if (tmp == NULL)
		return;
	memset(tmp, 0, sizeof(int)*range);  //初始化

	for (int i = 0; i < size; i++)  //统计每个元素出现的次数
		tmp[arr[i] - minValue]++;  //在存储上要在原始数组数值上减去minValue才不会出现越界问题

	for (int i = 0; i < range; i++)  //通过统计tmp[];回收元素
	{
		while (tmp[i]--)
			arr[count++] = i + minValue;  //要将i的值加上minValue才能还原到原始数据
	}
	free(tmp);
}

int main()
{
	int a[] = { 2,3,8,7,1,7,3,9,8,2,1,4,2,4,6,9 };
	int len = (int) sizeof(a) / sizeof(*a);

	cout << "排序前：" << endl;
	for (int i = 0; i < len; i++)
	{
		cout << a[i] << "  ";
	}
	cout << endl;

	CountingSort(a, len);

	cout << "排序后：" << endl;
	for (int i = 0; i < len; i++)
	{
		cout << a[i] << "  ";
	}
	cout << endl;

	system("pause");
	return 0;
}