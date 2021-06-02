#include<iostream>
using namespace std;

typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode {
	ElementType Data;
	BinTree Left;
	BinTree Right;
};

void PreorderTraversal(BinTree BT);
void InorderTraversal(BinTree BT);

BinTree Insert(BinTree BST, ElementType X);
BinTree Delete(BinTree BST, ElementType X);
BinTree Find(BinTree BST, ElementType X);
BinTree FindMin(BinTree BST);
BinTree FindMax(BinTree BST);

int main()
{
	BinTree BST, MinP, MaxP, Tmp;
	ElementType X;
	int N, i;

	BST = NULL;
	cin >> N;
	for (i = 0; i < N; i++) 
	{
		cin >> X;
		BST = Insert(BST, X);
	}
	cout << "Preorder:";
	PreorderTraversal(BST); 
	cout << endl;
	MinP = FindMin(BST);
	MaxP = FindMax(BST);
	cin >> N;
	for (i = 0; i < N; i++) 
	{
		cin >> X;
		Tmp = Find(BST, X);
		if (Tmp == NULL)
			cout << X << " is not found" << endl;
		else {
			cout << Tmp->Data << " is found" << endl;
			if (Tmp == MinP)
				cout << Tmp->Data << " is the smallest key" << endl;
			if (Tmp == MaxP) 
				cout << Tmp->Data << " is the largest key" << endl;
		}
	}
	cin >> N;
	for (i = 0; i < N; i++) 
	{
		cin >> X;
		BST = Delete(BST, X);
	}
	cout << "Inorder:"; 
	InorderTraversal(BST); 
	cout << endl;

	system("pause");
	return 0;
}

// 查找递归实现 
BinTree Find(BinTree BST, ElementType X)
{
	if (!BST)  // 如果根结点为空，返回 NULL 
		return NULL;
	if (X < BST->Data) // 比根结点小，去左子树查找 
		return Find(BST->Left, X);
	else if (BST->Data < X)  // 比根结点大，去右子树查找 
		return Find(BST->Right, X);
	else if (BST->Data == X) // 找到了 
		return BST;
}

// 查找最小值的递归实现
BinTree FindMin(BinTree BST)
{
	if (!BST)    // 如果为空了，返回 NULL 
		return NULL;
	else if (BST->Left)   // 还存在左子树，沿左分支继续查找 
		return FindMin(BST->Left);
	else  // 找到了 
		return BST;
}

// 查找最大值的非递归实现
BinTree FindMax(BinTree BST)
{
	if (BST)  // 如果不空 
		while (BST->Right)   // 只要右子树还存在 
			BST = BST->Right;
	return BST;
}

// 插入
BinTree Insert(BinTree BST, ElementType X)
{
	if (!BST)  // 如果为空，初始化该结点
	{
		BST = (BinTree)malloc(sizeof(struct TNode));
		BST->Data = X;
		BST->Left = NULL;
		BST->Right = NULL;
	}
	else  // 不为空
	{
		if (X < BST->Data)  // 如果小，挂在左边 
			BST->Left = Insert(BST->Left, X);
		else if (BST->Data < X)  // 如果大，挂在右边 
			BST->Right = Insert(BST->Right, X);
		// 如果相等，什么都不用做 
	}
	return BST;
}

// 删除
BinTree Delete(BinTree BST, ElementType X)
{
	BinTree tmp;
	if (!BST)
		cout << "Not Found" << endl;
	else if (X < BST->Data)   // X 比当前结点值小，在左子树继续查找删除 
		BST->Left = Delete(BST->Left, X);
	else if (BST->Data < X)   // X 比当前结点值大，在右子树继续查找删除 
		BST->Right = Delete(BST->Right, X);
	else  //  找到被删除结点
	{
		if (BST->Left && BST->Right)  // 被删除结点有俩孩子结点
		{
			tmp = FindMin(BST->Right);   // 找到右子树中值最小的
			BST->Data = tmp->Data;     // 用找到的值覆盖当前结点 
			BST->Right = Delete(BST->Right, tmp->Data);   // 把前面找到的右子树最小值结点删除 
		}
		else  // 被删除结点只有一个孩子结点或没有孩子结点
		{
			tmp = BST;
			if (!BST->Left && !BST->Right)  // 没有孩子结点 
				BST = NULL;
			else if (BST->Left && !BST->Right)  // 只有左孩子结点 
				BST = BST->Left;
			else if (!BST->Left && BST->Right)  // 只有右孩子结点 
				BST = BST->Right;
			free(tmp);
		}
	}
	return BST;
}

// 先序遍历 
void PreorderTraversal(BinTree BT)
{
	if (BT)
	{
		cout << BT->Data << " ";  // 打印根 
		PreorderTraversal(BT->Left);  // 进入左子树 
		PreorderTraversal(BT->Right);  // 进入右子树 
	}
}

// 中序遍历 
void InorderTraversal(BinTree BT)
{
	if (BT)
	{
		InorderTraversal(BT->Left);  // 进入左子树 
		cout << BT->Data << " ";  // 打印根 
		InorderTraversal(BT->Right);  // 进入右子树 
	}
}