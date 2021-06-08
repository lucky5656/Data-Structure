#include <iostream>
using namespace std;

//将a[low, mid]和a[mid+1, high]两个有序数组合并为一个有序数组
void Merge(int *a, int *temp, int low, int mid, int high)
{
	int i = low;  //左边部分数组指针
	int j = mid + 1;  //右边部分数组指针
	int k = low;  //对temp数组进行操作的指针
	while (i <= mid && j <= high)
	{
		if (a[i] <= a[j])
		{
			//temp[k] = a[i];
			//k++;
			//i++;
			temp[k++] = a[i++];  //等价于上面三行代码
		}
		else
		{
			temp[k++] = a[j++];
		}
	}
	if (i <= mid)
	{
		while (i <= mid)  //查看左边序列是否为空
		{
			temp[k++] = a[i++];
		}
	}
	else
	{
		while (j <= high)  //查看右边序列是否为空
		{
			temp[k++] = a[j++];
		}
	}
	for (int n = low; n <= high; n++)  //移动回原数组
	{
		a[n] = temp[n];

	}
}

void MergeSort(int *a, int *temp, int low, int high)  // a为待排序的数组；temp为辅助数组
{
	if (low < high)  // low == high时，就递归到只有一个元素，为终止条件
	{
		int mid = low + (high - low) / 2;  //分：将数组一分为二（(利用low + (high - low) / 2求mid是为了防止整数溢出问题)）
		MergeSort(a, temp, low, mid);  //治：将左边的数组排序(a[low] ~ a[mid])
		MergeSort(a, temp, mid + 1, high);  //治：将右边的数组排序(a[mid+1] ~ a[high])
		Merge(a, temp, low, mid, high);  //合：合并两个有序数组
	}
}

int main()
{
	int a[] = { 4,2,5,0,7,1,6,3 };
	int b[8] = { 0 };  //用于存放归并后的结果

	cout << "排序前：" << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << a[i] << "  ";
	}
	cout << endl;

	MergeSort(a, b, 0, 7);

	cout << "排序后：" << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << a[i] << "  ";
	}
	cout << endl;

	system("pause");

	return 0;
}