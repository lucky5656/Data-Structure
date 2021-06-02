#include<iostream>
using namespace std;

//搜索树表示
typedef struct TreeNode *Tree;
struct TreeNode
{
	int v;  //用v表示结点的信息
	Tree Left, Right;  //用链表形式表示树
	int flag;  //flag为某个结点是否被访问过的标志，用来判别一个序列是否与树一样，如果某个结点未被访问，flag=0，否则flag=1
};

//建新结点（一般为第一个结点）
Tree NewNode(int V)
{
	Tree T = (Tree)malloc(sizeof(struct TreeNode));
	T->v = V;
	T->Left = T->Right = NULL;
	T->flag = 0;
	return T;
}

//后续结点的插入
Tree Insert(Tree T, int V)
{
	if (!T)  //T为空
	{
		T = NewNode(V);  //通过NewNode(V)为T构造第一个结点
	}
	else  //T不为空
	{
		if (V > T->v)
			T->Right = Insert(T->Right, V);
		else
			T->Left = Insert(T->Left, V);
	}
	return T;
}

//构建搜索树
Tree MakeTree(int N)
{
	Tree T;
	int V;

	cin >> V;  //首先读入第一个元素放入V中
	T = NewNode(V);  //为T构造新结点
	for (int i = 1; i < N; i++)
	{
		cin >> V;  //依次读入序列后面的元素
		T = Insert(T, V);  //读入的后面元素依次插入树T
	}
	return T;
}

//如何判别（已经访问过的结点要进行标记，使flag=1）
//在树T中按顺序搜索序列中的每个数，如果每次搜索所经过的结点在前面均出现过，则一致；
//                             否则如果某次搜索中遇到前面未出现的结点，则不一致。
int check(Tree T, int V)
{
	if (T->flag)  //某个结点被访问过(因为之前的V == T->v，才使得flag =1)
	{
		if (V < T->v)
			return check(T->Left, V);
		else if (V > T->v)
			return check(T->Right, V);
		else  //如果V == T->v，意味着这个序列中有两个元素出现了两次以上，即重复出现，认为不一致
			return 0;
	}
	else  //某个结点未被访问过
	{
		if (V == T->v)  //如果未被访问过的结点刚好是所搜索的，使flag=1
		{
			T->flag = 1;
			return 1;
		}
		else  //否则未被访问过的结点不是所搜索的，即遇到前面未出现的结点，使flag=0
			return 0;
	}
}

int Judge(Tree T, int N)
{
	int V, same = 1;
	//same：1代表目前还一致，0代表已经不一致

	cin >> V;

	if (V != T->v)  //序列第一个元素与T的根结点不一致
		same = 0;  //两棵树已经不一致
	else
		T->flag = 1;

	for (int i = 1; i < N; i++)
	{
		cin >> V;
		if ((same) && (!check(T, V)))
			same = 0;
	}

	if (!same)
		return 0;
	else
		return 1;
}

//清除T中各个结点的标记
void ResetT(Tree T)
{
	if (T->Left)
		ResetT(T->Left);
	if (T->Right)
		ResetT(T->Right);
	T->flag = 0;
}

//释放T的空间
void FreeTree(Tree T)
{
	if (T->Left)
		FreeTree(T->Left);
	if (T->Right)
		FreeTree(T->Right);
	free(T);
}

int main()
{
	Tree T;
	int N, L;  // N个结点，L个序列
	cin >> N;
	while (N)
	{
		cin >> L;
		T = MakeTree(N);  //根据第一行序列建N个结点的树T
		for (int i = 0; i < L; i++)  //依据树T分别判别后面的L个序列是否能与T形成同一搜索树并输出结果
		{
			if (Judge(T, N))
				cout << "Yes" << endl;
			else
				cout << "No" << endl;
			ResetT(T); //清除T中的标记flag
		}
		FreeTree(T);
		cin >> N;
	}
	system("pause");
	return 0;
}