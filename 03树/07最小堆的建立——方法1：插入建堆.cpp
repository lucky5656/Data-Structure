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

// 判断是否已经满 
bool IsFull(MaxHeap H)
{
	return (H->size == H->capacity);
}

// 判断是否为空
bool IsEmpty(MaxHeap H)
{
	return !H->size;
}

// 插入
void Insert(MaxHeap H, int x) 
{
	if (IsFull(H)) 
	{
		cout << "最大堆已满，无法插入！" << endl;
		return;
	}
	int i = ++H->size;  // 指向数组最后一个 
	for (; H->data[i / 2] < x; i /= 2)
		H->data[i] = H->data[i / 2];
	H->data[i] = x;
}

// 遍历 
void Traversal(MaxHeap H) 
{
	for (int i = 1; i <= H->size; i++)
		cout << H->data[i] << " ";
	cout << endl;
}

int main() 
{
	MaxHeap H;
	H = Create_T();
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) 
	{
		int t;
		cin >> t;
		Insert(H, t);
	}
	Traversal(H);
	system("pause");
	return 0;
}