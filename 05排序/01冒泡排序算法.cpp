#include<iostream>
using namespace std;

void BubbleSort(int list[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		bool flag = true;  //表示本轮冒泡是否发生交换的标志
		for (int j = 0; j < n - i - 1; j++)
		{
			if (list[j] > list[j + 1])
			{
				flag = false;
				std::swap(list[j], list[j + 1]);
			}
		}
		if(flag)  //一轮对比下来是否发生位置交换
		{
			break;
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

	BubbleSort(a, 10);

	cout << "排序后：" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << a[i] << "  ";
	}
	cout << endl;

	system("pause");

	return 0;
}