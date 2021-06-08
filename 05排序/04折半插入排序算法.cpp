#include<iostream>
using namespace std;

template<class T>
void BinaryInsertionSort(T *a, int n)
{
	int i, j, low, high, mid;
	for (i = 2; i < n; i++)  //依次将a[2]~a[n]插入到前面已经排好序的列表
	{
		a[0] = a[i];  //将a[i]暂存到a[0]
		low = 1;
		high = i - 1;
		while (low <= high)
		{
			mid = low + (high - low) / 2;  //取中间位置(利用low + (high - low) / 2求mid是为了防止整数溢出问题)
			if (a[mid] > a[0])  //查找左子表
			{
				high = mid - 1;
			}
			else  //查找右子表
			{
				low = mid + 1;
			}
		}
		for (j = i - 1; j >= high + 1; --j)  //i - 1指待插入元素的前一个元素，即有序列表中所有大于待插入元素的最后一个元素；high + 1指有序列表中所有大于待插入元素的第一个元素
		{
			a[j + 1] = a[j];  //统一后移元素
		}
		a[high + 1] = a[0];  //插入操作
	}
}

int main()
{
	int a[] = { 0,4,2,8,0,5,7,1,3,6,9 };

	cout << "排序前：" << endl;
	for (int i = 1; i < 11; i++)
	{
		cout << a[i] << "  ";
	}
	cout << endl;

	BinaryInsertionSort(a, 11);

	cout << "排序后：" << endl;
	for (int i = 1; i < 11; i++)
	{
		cout << a[i] << "  ";
	}
	cout << endl;

	double b[] = { 0,4.1,2.2,8.3,0.4,5.5,7.6,1.7,3.8,6.9,9.0 };

	cout << "排序前：" << endl;
	for (int i = 1; i < 11; i++)
	{
		cout << b[i] << "  ";
	}
	cout << endl;

	BinaryInsertionSort(b, 11);

	cout << "排序后：" << endl;
	for (int i = 1; i < 11; i++)
	{
		cout << b[i] << "  ";
	}
	cout << endl;

	system("pause");

	return 0;
}