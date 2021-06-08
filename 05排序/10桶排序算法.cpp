#include<iostream>
using namespace std;
#include<algorithm>

void BubbleSort(int arr[], int len)
{
	for (int i = 0; i < len - 1; i++)
	{
		for (int j = 0; j < len - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				std::swap(arr[j], arr[j + 1]);
			}
		}
	}
}

void BucketSort(int* arr, int len)
{

	int bucket[5][5];  //分配5个桶
	int bucketsize[5];  //每个桶中元素个数的计数器

	//初始化桶和桶计数器
	memset(bucket, 0, sizeof(bucket));
	memset(bucketsize, 0, sizeof(bucketsize));

	for (int i = 0; i < len; i++)  //把数组中的数据放入桶中
	{
		bucket[arr[i] / 10][bucketsize[arr[i] / 10]++] = arr[i];
	}

	for (int i = 0; i < len; i++)  //对每个桶中的数据进行排序
		BubbleSort(bucket[i], bucketsize[i]);

	int k = 0;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < bucketsize[i]; j++)
		{
			arr[k++] = bucket[i][j];  //将每个桶中的元素填充到数组中去
		}
	}
}

int main()
{
	int a[] = { 21,3,30,44,15,36,6,10,9,19,25,48,5,23,47 };
	int len = sizeof(a) / sizeof(a[0]);

	cout << "排序前：" << endl;
	for (int i = 0; i < len; i++)
	{
		cout << a[i] << "  ";
	}
	cout << endl;

	BucketSort(a, len);

	cout << "排序后：" << endl;
	for (int i = 0; i < len; i++)
	{
		cout << a[i] << "  ";
	}
	cout << endl;

	system("pause");
	return 0;
}