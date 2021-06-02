#include<iostream>
using namespace std;
const int MinData = -100000;  // 哨兵值
const int MaxSize = 1005;   // 最大个数 
typedef struct HeapStruct *Heap;
struct HeapStruct {
	int *data;   // 存值的数组 
	int size;   // 当前元素个数 
	int capacity;  // 最大容量 
};

// 初始化堆
Heap Create()
{
	Heap H;
	H = (Heap)malloc(sizeof(struct HeapStruct));
	H->data = (int *)malloc(sizeof(int) * (MaxSize + 1));
	H->size = 0;
	H->capacity = MaxSize;
	H->data[0] = MinData;
	return H;
}

// 插入
void Insert(Heap H, int x)
{
	int i = ++H->size;  // 指向数组最后一个 
	for (; H->data[i / 2] > x; i /= 2)
		H->data[i] = H->data[i / 2];
	H->data[i] = x;
}

// 打印路径 
void Print(Heap H, int i)
{
	for (; i > 0; i /= 2)
	{
		cout << H->data[i];
		if (i != 1)
			cout << " ";
	}
	cout << endl;
}

int main()
{
	Heap H;
	H = Create();
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		int t;
		cin >> t;
		Insert(H, t);
	}
	for (int i = 0; i < m; i++)
	{
		int t;
		cin >> t;
		Print(H, t);
	}
	system("pause");
	return 0;
}