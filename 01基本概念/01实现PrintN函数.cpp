#include<iostream>
using namespace std;

void PrintN_Iteration(int n)  //循环实现
{
	for (int i = 1; i <= n; i++)
	{
		cout << i << endl;
	}
}

void PrintN_Recursion(int n)  //递归实现
{
	if(n)
	{
		PrintN_Recursion(n - 1);
		cout << n << endl;
	}
}

int main()
{
	PrintN_Iteration(10000);
	//PrintN_Recursion(10000);

	system("pause");

	return 0;
}