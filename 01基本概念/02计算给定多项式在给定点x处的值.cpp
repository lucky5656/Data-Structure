#include<iostream>
using namespace std;
#include<ctime>

double f1(double a[], int n, double x)
{
	double p = a[0];
	for (int i = 1; i <= n; i++)
	{
		p += (a[i] * pow(x, i));  //f(x)=a[0]+a[1]*x+...+a[n−1]*x^(n−1)+a[n]*x^(n)
	}
	return p;
}

double f2(double a[], int n, double x)
{
	double p = a[n];
	for (int i = n; i > 0; i--)
	{
		p = a[i - 1] + x * p;    //f(x)=a[0]+x*(a[1]+x*(...(a[n-1]+x*(a[n]))...))
	}
	return p;
}

int main()
{
	double a[] = { 0,1,2,3,4,5,6,7,8,9 };

	clock_t startTime, endTime;
	startTime = clock();//计时开始
	for (int i = 0; i < 1e7; i++)  //重复调用函数以获得充分多的时钟打点数
	{
		f1(a, 9, 1.1);
	}
	//f1(a, 9, 1.1);
	endTime = clock();//计时结束
	//cout << "The run time of f1 is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC  << "s" << endl;  //常数CLOCKS_PER_SEC为机器时钟每秒所走的时钟打点数
	cout << "The run time of f1 is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC / 1e7 << "s" << endl;  //计算函数单次运行时间
	cout << "f1(1.1) = " << f1(a, 9, 1.1) << endl;

	startTime = clock();//计时开始
	for (int i = 0; i < 1e7; i++)
	{
		f2(a, 9, 1.1);
	}
	//f2(a, 9, 1.1);
	endTime = clock();//计时结束
	//cout << "The run time of f2 is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC  << "s" << endl;
	cout << "The run time of f2 is: " << (double)(endTime - startTime) / CLOCKS_PER_SEC / 1e7 << "s" << endl;
	cout << "f2(1.1) = " << f2(a, 9, 1.1) << endl;

	system("pause");

	return 0;
}