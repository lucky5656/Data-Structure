#include<iostream>
using namespace std;
#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode {
	ElementType Data[MAXSIZE];
	Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput();
Position BinarySearch(List L, ElementType X);

int main()
{
	List L;
	ElementType X;
	Position P;

	L = ReadInput();
	cin >> X;
	P = BinarySearch(L, X);
	cout << P << endl;

	system("pause");

	return 0;
}

List ReadInput()
{
	LNode *L = (LNode*)malloc(sizeof(LNode));
	int Length;
	cin >> Length;
	for (int i = 1; i <= Length; i++)  //元素从下标1开始存储
	{
		cin >> L->Data[i];
	}
	L->Last = Length;
	return L;
}

Position BinarySearch(List L, ElementType X)
{
	Position left = 1;
	Position right = L->Last;
	Position mid;
	while (left <= right)
	{
		mid = left + (right - left) / 2;
		if (L->Data[mid] == X)
		{
			return mid;
		}
		else if (L->Data[mid] < X)
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}
	return NotFound;
}