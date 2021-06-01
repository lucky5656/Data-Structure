#include<iostream>
using namespace std;

// 算法1：确定子列的首部和尾部，再遍历累加，时间复杂度为O(n^3)
int MaxSubseqSum1(int a[], int n)
{
	int ThisSum, MaxSum = 0;
	for (int i = 0; i < n; i++)  //i为子列左端位置
	{
		for (int j = 0; j < n; j++)  //j是子列右端位置
		{
			ThisSum = 0;  //ThisSum是从a[i]到a[j]的子列和
			for (int k = i; k <= j; k++)
			{
				ThisSum += a[k];
			}
			if (ThisSum > MaxSum)  //如果刚得到的这个子列和更大，则更新结果
			{
				MaxSum = ThisSum;
			}
		}
	}
	return MaxSum;
}

//算法2：确定子列的首部，逐个累加，时间复杂度为O(n^2)
int MaxSubseqSum2(int a[], int n)
{
	int ThisSum, MaxSum = 0;
	for (int i = 0; i < n; i++)  //i为子列左端位置
	{
		ThisSum = 0;  //ThisSum是从a[i]到a[j]的子列和
		for (int j = i; j < n; j++)  //j是子列右端位置
		{
			ThisSum += a[j];
			if (ThisSum > MaxSum)  //如果刚得到的这个子列和更大，则更新结果
			{
				MaxSum = ThisSum;
			}
		}
	}
	return MaxSum;
}

//算法3：分而治之，递归分成两份，分别求每个分割后最大子列和，时间复杂度为O(nlogn)
//返回左边最大子列和、右边最大子列和、横跨划分边界的最大子列和三者中最大值
int MaxSum(int A, int B, int C)
{
	return (A > B) ? ((A > C) ? A : C) : ((B > C) ? B : C);
}
//分治
int DivideAndConquer(int a[], int left, int right)
{
	if (left == right) 	//递归结束条件：子列只有一个数字
	{
		if (a[left] > 0)  // 当该数为正数时，最大子列和为其本身
		{
			return a[left];
		}
		return 0;	// 当该数为负数时，最大子列和为 0
	}

	//分别递归找到左右最大子列和
	int mid = left + (right - left) / 2;  //利用left+(right - left)/2求mid是为了防止整数溢出问题
	int MaxLeftSum = DivideAndConquer(a, left, mid);
	int MaxRightSum = DivideAndConquer(a, mid + 1, right);

	//再分别找左右跨界最大子列和
	int MaxLeftBorderSum = 0;
	int LeftBorderSum = 0;
	for (int i = mid; i >= left; i--)  //应该从边界出发向左边找
	{
		LeftBorderSum += a[i];
		if (LeftBorderSum > MaxLeftBorderSum)
			MaxLeftBorderSum = LeftBorderSum;
	}
	int MaXRightBorderSum = 0;
	int RightBorderSum = 0;
	for (int i = mid + 1; i <= right; i++)  // 从边界出发向右边找
	{
		RightBorderSum += a[i];
		if (RightBorderSum > MaXRightBorderSum)
			MaXRightBorderSum = RightBorderSum;
	}

	//最后返回分解的左边最大子列和，右边最大子列和，和跨界最大子列和三者中最大的数
	return MaxSum(MaxLeftSum, MaxRightSum, MaXRightBorderSum + MaxLeftBorderSum);
}
int MaxSubseqSum3(int a[], int n)
{
	return DivideAndConquer(a, 0, n - 1);
}

//算法4：在线处理，直接累加，如果累加到当前的和为负数，置当前值或0，时间复杂度为 O(n)
int MaxSubseqSum4(int a[], int n)
{
	int ThisSum = 0;
	int MaxSum = 0;
	for (int i = 0; i < n; i++)
	{
		ThisSum += a[i];  //向右累加
		if (ThisSum < 0)  //如果刚得到的这个子列和为负，则不能使后面的部分和增大，抛弃
		{
			ThisSum = 0;
		}
		else if (ThisSum > MaxSum)  //如果刚得到的这个子列和更大，则更新结果
		{
			MaxSum = ThisSum;
		}
	}
	return MaxSum;
}

int main() {
	int n;
	int a[100000 + 5];
	cin >> n; 
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	//算法1
	//int MaxSum1 = MaxSubseqSum1(a, n);
	//cout << MaxSum1 << endl;

	//算法2
	//int MaxSum2 = MaxSubseqSum2(a, n);
	//cout << MaxSum2 << endl;

	//算法3
	//int MaxSum3 = MaxSubseqSum3(a, n);
	//cout << MaxSum3 << endl;

	//算法4
	int MaxSum4 = MaxSubseqSum4(a, n);
	cout << MaxSum4 << endl;

	system("pause");

	return 0;
}