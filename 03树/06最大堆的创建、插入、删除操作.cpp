#include<iostream>
using namespace std;
#define MaxData 100000
#define ERROR -1
typedef int ElementType;
typedef struct HeapStruct*MaxHeap;
struct HeapStruct {
	ElementType *Elements;  //存储堆元素的数组
	int Size;  //堆的当前元素个数
	int Capacity;  //堆的最大容量
};

MaxHeap Create_T(int MaxSize);  // 建堆 
bool IsFull(MaxHeap H);    // 判断堆是否满
bool Insert(MaxHeap H, ElementType item);   // 插入元素
bool IsEmpty(MaxHeap H);    //  判断堆是否为空
ElementType DeleteMax(MaxHeap H);  // 删除并返回堆中最大元素
void LevelOrderTraversal(MaxHeap H);  // 层序遍历 

// 建堆 (创建容量为MaxSize的空的最大堆)
MaxHeap Create_T(int MaxSize) 
{
	MaxHeap H = (MaxHeap)malloc(sizeof(struct HeapStruct));
	// Elements[0] 作为哨兵，堆元素从  Elements[1] 开始存放 
	H->Elements = (ElementType *)malloc((MaxSize + 1) * sizeof(ElementType));
	H->Size = 0;
	H->Capacity = MaxSize;
	H->Elements[0] = MaxData;  // "哨兵"大于堆中所有可能的值 
	return H;
}

// 插入，从完全二叉树的最后一个位置插入 
bool Insert(MaxHeap H, ElementType item) 
{
	if (IsFull(H)) 
	{
		cout << "最大堆已满，无法插入！" << endl;
		return false;
	}
	int i = ++H->Size;  //i指向插入后堆中的最后一个元素的位置
	for (; H->Elements[i / 2] < item; i /= 2)  // 向上找比item大的结点(H->Elements[0]是哨兵元素，不小于堆中的最大元素，控制顺环结束)
		H->Elements[i] = H->Elements[i / 2];  //  向下赋值 
	H->Elements[i] = item;  //item插入 
	return true;
}

ElementType DeleteMax(MaxHeap H)  //从最大堆H中取出键值为最大的元素，并删除一个结点
{
	int Parent, Child;
	ElementType MaxItem, temp;
	if (IsEmpty(H))
	{
		cout << "最大堆已为空" << endl;
		return ERROR;
	}
	MaxItem = H->Elements[1];  //取出根结点最大值
	temp = H->Elements[H->Size--];  //拿到完全二叉树最后一个元素,用最大堆中最后一个元素从根结点开始向上过滤下层结点
	for (Parent = 1; Parent * 2 <= H->Size; Parent = Child)   //Parent=1先将最大堆中最后一个元素放到1的位置；判别条件：Parent*2<=H->size判别是否有左儿子
	{
		Child = Parent * 2;
		if ((Child != H->Size) && (H->Elements[Child] < H->Elements[Child + 1]))  //Child!=H->Size表示Child不为当前最后一个结点，即Parent有右孩子结点
			Child++;  //Child指向左右子结点的较大者
		//给temp找个合适的位置  
		if (temp >= H->Elements[Child])  //如果当前左右孩子结点比temp都小，说明temp位置已经合适
			break;
		else  //移动temp元素到下一层
			H->Elements[Parent] = H->Elements[Child];
	}
	H->Elements[Parent] = temp;  //在合适的位置把temp放进去
	return MaxItem;
}

// 判断是否已经满 
bool IsFull(MaxHeap H) 
{
	return (H->Size == H->Capacity);
}

// 判断是否为空
bool IsEmpty(MaxHeap H) 
{
	return !H->Size;
}

// 层序遍历
void LevelOrderTraversal(MaxHeap H) 
{
	cout << "层序遍历的结果是：";
	for (int i = 1; i <= H->Size; i++) 
	{
		cout << H->Elements[i]<<" ";
	}
	cout << endl;
}

int main() 
{
	MaxHeap H;
	int MaxSize = 100;
	H = Create_T(MaxSize);
	Insert(H, 55);
	Insert(H, 66);
	Insert(H, 44);
	Insert(H, 33);
	Insert(H, 11);
	Insert(H, 22);
	Insert(H, 88);
	Insert(H, 99);
	/*
		 99
		/  \
	   88  66
	  / \  / \
	 55 11 22 44
	/
   33
	*/
	LevelOrderTraversal(H);
	DeleteMax(H);
	LevelOrderTraversal(H);
	DeleteMax(H);
	LevelOrderTraversal(H);
	DeleteMax(H);
	LevelOrderTraversal(H);
	DeleteMax(H);
	LevelOrderTraversal(H);
	system("pause");
	return 0;
}