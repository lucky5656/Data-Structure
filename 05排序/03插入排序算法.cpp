#include<iostream>
using namespace std;

template<class T>
void InsertionSort(T *a, int n)
{
	int in, out;  //in排好顺序的；out未排好顺序的
	for (out = 1; out < n;out++)  //out = 0已经默认为排好顺序的
	{
		T temp = a[out];  //将待插入元素复制为哨兵
		in = out;
		while (in > 0 && a[in - 1] >= temp)  //从后往前查找待插入的位置
		{
			a[in] = a[in - 1];  //往后挪位置
			in--;
		}
		a[in] = temp;  //复制待插入元素到插入位置
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

	InsertionSort(a, 10);

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

	InsertionSort(b, 10);

	cout << "排序后：" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << b[i] << "  ";
	}
	cout << endl;

	system("pause");

	return 0;
}