#include<iostream>
using namespace std;
#include<vector> 
#include<queue>
#include<algorithm>

typedef struct TreeNode *BinTree;
struct TreeNode {
	int Data;  // 存值 
	BinTree Left;    // 左儿子结点 
	BinTree Right;   // 右儿子结点 
};
BinTree CreatBinTree();   // 创建一个二叉树
void  PreOrderTraversal_Recursion(BinTree BT);  // 先序递归遍历
void PreOrderTraversal(BinTree BT);   // 先序遍历，根左右
void InOrderTraversal_Recursion(BinTree BT);  // 中序递归遍历
void InOrderTraversal(BinTree BT);    // 中序遍历，左根右
void PostOrderTraversal_Recursion(BinTree BT);  // 后序递归遍历
void PostOrderTraversal(BinTree BT);  // 后序遍历，左右根 

typedef struct SNode *Stack;
struct SNode {
	BinTree Data;
	Stack Next;
};


Stack CreateStack();  // 初始化链栈 
int IsEmpty(Stack S);  // 判断链栈是否为空 
void Push(Stack S, BinTree item);  // 入栈 
BinTree Pop(Stack S);  // 出栈


// 初始化 
Stack CreateStack() 
{
	Stack S;
	S = (Stack)malloc(sizeof(struct SNode));
	S->Next = NULL;
	return S;
}

// 判断是否为空 
int IsEmpty(Stack S) 
{
	return (S->Next == NULL);
}

// 入栈
void Push(Stack S, BinTree item) 
{
	Stack tmp;
	tmp = (Stack)malloc(sizeof(struct SNode));
	tmp->Data = item;
	// 链栈栈顶元素是链表头结点，新入栈的链表在栈顶元素后面 
	tmp->Next = S->Next;
	S->Next = tmp;
}

// 出栈
BinTree Pop(Stack S) 
{
	Stack First;
	BinTree TopVal;
	if (IsEmpty(S)) 
	{
		cout << "堆栈空" << endl;
		return 0;
	}
	else 
	{
		First = S->Next;   // 出栈第一个元素在栈顶元素后面 
		S->Next = First->Next;  //把第一个元素从链栈删除 
		TopVal = First->Data;   // 取出被删除结点的值 
		free(First);  // 释放空间 
		return TopVal;
	}
}

BinTree Insert(int Data) 
{
	BinTree BT;
	BT = (BinTree)malloc(sizeof(struct TreeNode));
	BT->Data = Data;
	BT->Left = NULL;
	BT->Right = NULL;
	return BT;
}

// 初始化二叉树 
BinTree CreatBinTree() 
{
	BinTree BT;
	BT = (BinTree)malloc(sizeof(struct TreeNode));
	return BT;
}

// 先序递归
void  PreOrderTraversal_Recursion(BinTree BT)
{
	if(BT){
		cout << BT->Data;  // 打印根
		PreOrderTraversal_Recursion(BT->Left);  // 进入左子树
		PreOrderTraversal_Recursion(BT->Right);  // 进入右子树
	}
} 

// 先序非递归 
void PreOrderTraversal(BinTree BT) 
{
	BinTree T = BT;
	Stack S = CreateStack();  // 创建并初始化堆栈 S
	while (T || !IsEmpty(S)) {  // 当树不为空或堆栈不空 
		while (T) {
			Push(S, T);    // 压栈，第一次遇到该结点 
			cout << T->Data;  // 访问结点
			T = T->Left;   // 遍历左子树 
		}
		if (!IsEmpty(S)) {  // 当堆栈不空 
			T = Pop(S);    // 出栈，第二次遇到该结点 
			T = T->Right;  // 访问右结点 
		}
	}
}

// 中序递归 
void InOrderTraversal_Recursion(BinTree BT)
{
	if(BT){
		InOrderTraversal_Recursion(BT->Left);  // 进入左子树
		cout << BT->Data;  // 打印根
		InOrderTraversal_Recursion(BT->Right);  // 进入右子树
	}
} 

// 中序非递归
void InOrderTraversal(BinTree BT) 
{
	BinTree T = BT;
	Stack S = CreateStack();  // 创建并初始化堆栈 S
	while (T || !IsEmpty(S)) {  // 当树不为空或堆栈不空 
		while (T) {
			Push(S, T);    // 压栈
			T = T->Left;   // 遍历左子树 
		}
		if (!IsEmpty(S)) {  // 当堆栈不空 
			T = Pop(S);    // 出栈
			cout << T->Data;  // 访问结点
			T = T->Right;  // 访问右结点 
		}
	}
}

// 后序递归
void PostOrderTraversal_Recursion(BinTree BT)
{
	if(BT)
	{
		PostOrderTraversal_Recursion(BT->Left);  // 进入左子树
		PostOrderTraversal_Recursion(BT->Right);  // 进入右子树
		cout << BT->Data;  // 打印根
	}
} 

// 后序遍历 
void PostOrderTraversal(BinTree BT) 
{
	BinTree T = BT;
	Stack S = CreateStack();  // 创建并初始化堆栈 S
	vector<BinTree> v;
	Push(S, T);
	while (!IsEmpty(S)) {  // 当树不为空或堆栈不空 
		T = Pop(S);
		v.push_back(T);
		if (T->Left)
			Push(S, T->Left);
		if (T->Right)
			Push(S, T->Right);
	}
	reverse(v.begin(), v.end());  // 逆转 
	for (int i = 0; i < v.size(); i++)
	    cout << v[i]->Data;
}

// 层次遍历
void LevelOrderTraversal(BinTree BT) 
{
	queue<BinTree> q;
	BinTree T;
	if (!BT)
		return;
	q.push(BT);  // BT 入队 
	while (!q.empty()) {
		T = q.front();  // 访问队首元素 
		q.pop();  // 出队
		cout << T->Data;
		if (T->Left)
			q.push(T->Left);
		if (T->Right)
			q.push(T->Right);
	}
}
// 输出叶子结点
void  FindLeaves(BinTree BT) 
{
	if (BT) 
	{
		if (!BT->Left && !BT->Right)
			cout << BT->Data;  // 打印叶子结点
		FindLeaves(BT->Left);  // 进入左子树 
		FindLeaves(BT->Right);  // 进入右子树 
	}
}

// 求树高度
int  GetHeight(BinTree BT) 
{
	int HL, HR, MaxH;
	if (BT) {
		HL = GetHeight(BT->Left);  // 求左子树高度 
		HR = GetHeight(BT->Right);  // 求右子树高度 
		MaxH = (HL > HR) ? HL : HR;
		return MaxH + 1;  // 当前结点高度为左右子树最大的高度+1 
	}
	else
		return 0;
}
int main() 
{
	BinTree BT;
	BT = CreatBinTree();
	BT->Data = 1;
	BT->Left = Insert(2);
	BT->Right = Insert(3);
	BT->Left->Left = Insert(4);
	BT->Left->Right = Insert(6);
	BT->Left->Right->Left = Insert(5);
	BT->Right->Left = Insert(7);
	BT->Right->Right = Insert(9);
	BT->Right->Left->Right = Insert(8);

	cout << "先序递归遍历：";
	PreOrderTraversal_Recursion(BT);
	cout << "\n先序非递归遍历：";
	PreOrderTraversal(BT);

	cout << "\n中序递归遍历：";
	InOrderTraversal_Recursion(BT);
	cout << "\n中序非递归遍历：";
	InOrderTraversal(BT);

	cout << "\n后序递归遍历：";
	PostOrderTraversal_Recursion(BT);
	cout << "\n后序非递归遍历：";
	PostOrderTraversal(BT);

	cout << "\n层次遍历：";
	LevelOrderTraversal(BT);

	cout << "\n输出叶子结点：";
	FindLeaves(BT);

	cout << "\n输出树的高度：" << GetHeight(BT) << endl;

	system("pause");

	return 0;
}