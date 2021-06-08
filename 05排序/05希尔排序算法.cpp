#include<iostream>
using namespace std;

template <class T>
void InsertSort(T *a, int n, int i, int gap)
{
	int j;

	for (j = i + gap; j < n; j += gap)
	{
		// 如果a[j] < a[j-gap]，则寻找a[j]位置，并将后面数据的位置都后移。
		if (a[j] < a[j - gap])
		{
			T temp = a[j];
			int k = j - gap;
			while (k >= 0 && a[k] > temp)
			{
				a[k + gap] = a[k];
				k -= gap;
			}
			a[k + gap] = temp;
		}
	}
}

template <class T>
void ShellSort(T *a, int n)
{
	int i, gap;

	// gap为步长，每次减为原来的一半
	for (gap = n / 2; gap > 0; gap /= 2)
	{
		// 共gap个组，对每一组都执行直接插入排序
		for (i = 0; i < gap; i++)
		{
			InsertSort(a, n, i, gap);
		}
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

	ShellSort(a, 10);

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

	ShellSort(b, 10);

	cout << "排序后：" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << b[i] << "  ";
	}
	cout << endl;

	system("pause");

	return 0;
}