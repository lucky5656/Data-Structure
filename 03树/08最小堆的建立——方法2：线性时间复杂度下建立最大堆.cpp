#include<iostream>
using namespace std;
const int MaxData = 100000;  // 哨兵值
const int MaxSize = 1005;   // 最大个数 
using namespace std;
typedef struct HeapStruct *MaxHeap;
struct HeapStruct {
	int *data;   // 存值的数组 
	int size;   // 当前元素个数 
	int capacity;  // 最大容量 
};

// 初始化堆
MaxHeap Create_T() 
{
	MaxHeap H;
	H = (MaxHeap)malloc(sizeof(struct HeapStruct));
	H->data = (int *)malloc(sizeof(int) * (MaxSize + 1));
	H->size = 0;
	H->capacity = MaxSize;
	H->data[0] = MaxData;
	return H;
}

// 排序，类似堆的"删除操作" 
void sort(MaxHeap H, int i)  //下滤：将H中以H->Data[p]为根的子堆调整为最大堆
{
	int Child, Parent;
	int temp = H->data[i];  // 拿到当前"根结点的值" 
	for (Parent = i; Parent * 2 <= H->size; Parent = Child) 
	{
		Child = 2 * Parent;
		if ((Child != H->size) && (H->data[Child] < H->data[Child + 1]))
			Child++;  //Child指向左右子结点的较大者
		if (temp >= H->data[Child])
			break;
		else
			H->data[Parent] = H->data[Child];
	}
	H->data[Parent] = temp;
}

// 建最大堆(调整H->Data[]中的元素，使满足最大堆的有序性)
void BuildHeap(MaxHeap H) 
{
	for (int i = H->size / 2; i > 0; i--)  //从最后一个结点的父节点开始，到根结点1
	{
		// 以每个有孩子结点的结点作为根结点，对其子树进行堆排序 
		sort(H, i);
	}
}

// 遍历 
void Traversal(MaxHeap H) 
{
	for (int i = 1; i <= H->size; i++) 
	{
		cout << H->data[i] << " ";
	}
	cout << endl;
}

int main() 
{
	MaxHeap H;
	H = Create_T();
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> H->data[++H->size];
	BuildHeap(H);
	Traversal(H);
	system("pause");
	return 0;
}