#include <iostream>
using namespace std;
#include <algorithm>

// 最大堆调整
void MaxHeapify(int arr[], int start, int end) 
{
	// 建立父结点指标和子结点指标
	int Parent = start;
	int Child = Parent * 2 + 1;
	while (Child <= end)  // 若子结点指标在范围内才做比较
	{
		if (Child + 1 <= end && arr[Child] < arr[Child + 1]) // 先比较两个子结点指标大小，选择最大的
			Child++;
		if (arr[Parent] > arr[Child]) // 如果父结点大于子结点代表调整完毕，直接跳出函数
			return;
		else { // 否则交换父子内容再继续子结点和孙结点比较
			swap(arr[Parent], arr[Child]);
			Parent = Child;
			Child = Parent * 2 + 1;
		}
	}
}

void HeapSort(int arr[], int len) 
{
	// 初始化，i从最后一个父结点开始调整
	for (int i = len / 2 - 1; i >= 0; i--)
		MaxHeapify(arr, i, len - 1);
	// 先将第一个元素和已经排好的元素前一位做交换，再重新调整（刚调整的元素之前的元素），直到排序完毕
	for (int i = len - 1; i > 0; i--) 
	{
		swap(arr[0], arr[i]);
		MaxHeapify(arr, 0, i - 1);
	}
}

int main() 
{
	int arr[] = { 4,2,8,0,5,7,1,3,6,9 };
	int len = (int) sizeof(arr) / sizeof(*arr);

	cout << "排序前：" << endl;
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << "  ";
	}
	cout << endl;

	HeapSort(arr, len);

	cout << "排序后：" << endl;
	for (int i = 0; i < len; i++)
	{
		cout << arr[i] << "  ";
	}
	cout << endl;

	system("pause");
	return 0;
}