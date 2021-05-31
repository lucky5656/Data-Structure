#include<iostream>
using namespace std;
#define MaxSize 1000
typedef int ElementType;
typedef struct {
	ElementType Data; // 存值
	int Parent;  // 指向父结点 
}SetType;

// 查找 
int Find(SetType S[], ElementType X) 
{
	int i;
	for (i = 0; i < MaxSize && S[i].Data != X; i++);  // 找到数组中该值对应的下标 
	if (MaxSize <= i) // 如果没有找到，返回 -1 
		return -1;
	for (; S[i].Parent >= 0; i = S[i].Parent); 	// 找到该结点的根结点 
	return i; // 返回根结点在数组S中的下标 
}

// 并 
void Union(SetType S[], ElementType X1, ElementType X2) 
{
	int root1 = Find(S, X1);  // 找到 X1 的根结点下标 
	int root2 = Find(S, X2);  // 找到 X2 的根结点下标 
	// 如果根结点的下标不同，说明不是一个集合
	if (root1 != root2) 
	{
		S[root1].Parent = root2;   // 把X1挂到X2的集合 
	}
}

int main() 
{
	SetType S[MaxSize];
	// 初始化数组，父结点全部指向-1 
	for (int i = 0; i < MaxSize; i++) 
	{
		S[i].Data = i + 1;
		S[i].Parent = -1;
	}
	cout << Find(S, 5) << endl;
	Union(S, 3, 5);
	cout << Find(S, 4) << endl;
	cout << Find(S, 3) << endl;
	Union(S, 1, 3);
	Union(S, 2, 4);
	Union(S, 8, 6);
	cout << Find(S, 6) << endl;
	cout << Find(S, 8) << endl;
	system("pause");
	return 0;
}