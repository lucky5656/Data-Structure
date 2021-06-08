#include<iostream>
using namespace std;

int maxbit(int arr[], int len)  //求数组的最大位数
{
	int maxData = arr[0];              // 最大数
	// 先求出最大数，再求其位数
	for (int i = 1; i < len; i++)
	{
		if (maxData < arr[i])
			maxData = arr[i];
	}
	int d = 1;
	int p = 10;
	while (maxData >= p)
	{
		maxData /= 10;
		++d;
	}
	return d;
}

void RadixSort(int arr[], int len)  //基数排序
{
	int d = maxbit(arr, len);  //数组中最大值的位数
	int *tmp = new int[len];
	int *count = new int[10]; //计数器
	int radix = 1;
	for (int i = 1; i <= d; i++) //进行d次排序
	{
		for (int j = 0; j < 10; j++)
			count[j] = 0; //每次分配前清空计数器
		for (int j = 0; j < len; j++)
		{
			int k = (arr[j] / radix) % 10; //统计每个桶中的记录数
			count[k]++;
		}
		for (int j = 1; j < 10; j++)
			count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
		for (int j = len - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
		{
			int k = (arr[j] / radix) % 10;
			tmp[count[k] - 1] = arr[j];
			count[k]--;
		}
		for (int j = 0; j < len; j++) //将临时数组的内容复制到arr中
			arr[j] = tmp[j];
		radix = radix * 10;
	}
	delete[]tmp;
	delete[]count;
}

int main()
{
	int a[] = { 144,203,6,905,47,215,836,26,527,602,848 };
	int len = sizeof(a) / sizeof(a[0]);

	cout << "排序前：" << endl;
	for (int i = 0; i < len; i++)
	{
		cout << a[i] << "  ";
	}
	cout << endl;

	RadixSort(a, len);

	cout << "排序后：" << endl;
	for (int i = 0; i < len; i++)
	{
		cout << a[i] << "  ";
	}
	cout << endl;

	system("pause");
	return 0;
}