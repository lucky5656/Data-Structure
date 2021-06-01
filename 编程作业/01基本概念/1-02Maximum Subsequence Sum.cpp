#include<iostream>
using namespace std;

void MaxSubseqSum(int a[], int n)
{
	int ThisSum = 0;
	int MaxSum = -1;
	int Head = 0, Tail = 0, TempHead = 0; // 最大子列的头和尾的下标 
	for (int i = 0; i < n; i++) 
	{
		ThisSum += a[i]; // 向右累加
		if (ThisSum < 0)  //如果当前子列小于0 
		{
		    ThisSum = 0; //则不可能使后面的部分增大，抛弃之 
	 	    TempHead = i + 1; //注意这时不能改变真正的头，只有发现更大的和更新序列时才会改变头和尾 
		}
		else if (ThisSum > MaxSum)  //如果刚得到的这个子列和更大，则更新结果
		{
			MaxSum = ThisSum; // 发现更大的和则更新当前结果
			Tail = i;
			Head = TempHead;
		}
	}
	if (MaxSum < 0) //全是负数，输出0和原序列首尾数 
		cout << 0 << " " << a[0] << " " << a[n - 1] << endl;
	else
		cout << MaxSum << " " << a[Head] << " " << a[Tail] << endl;
}

int main()
{
	int n;
	int a[100000 + 5];
	cin >> n; 
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	MaxSubseqSum(a, n);

	system("pause");

	return 0;
}