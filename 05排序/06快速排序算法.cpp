#include<iostream>
using namespace std;

template<class T>
void QuickSort(T *a, const int left, const int right)
{
	if (left < right)
	{
		//选枢轴
		int i = left;
		int j = right + 1;
		T pivot = a[left];  //pivot为枢轴，从数组左边开始

		//进行划分
		do {
			do i++; while (a[i] < pivot);  //找到比枢轴大的
			do j--; while (a[j] > pivot);  //找到比枢轴小的
			if (i < j)
			{
				swap(a[i], a[j]);  //小的放左边，大的放右边
			}
		} while (i < j);
		swap(a[left], a[j]);

		//递归
		QuickSort(a, left, j - 1);

		QuickSort(a, j + 1, right);
	}
}

int main()
{
	int a[] = { 4,2,8,0,5,7,1,3,6,9 };  
	
	cout << "排序前：" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << a[i] << "  ";
	}
	cout << endl;

	QuickSort(a, 0, 9);

	cout << "排序后：" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << a[i] << "  ";
	}
	cout << endl;

	double b[] = { 4.1,2.2,8.3,0.4,5.5,7.6,1.7,3.8,6.9,9.0 };

	cout << "排序前：" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << b[i] << "  ";
	}
	cout << endl;

	QuickSort(b, 0, 9);

	cout << "排序后：" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << b[i] << "  ";
	}
	cout << endl;

	system("pause");

	return 0;
}