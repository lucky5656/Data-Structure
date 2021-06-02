#include<iostream>
using namespace std;
#include<algorithm>
#define MaxNum 1001
int LevelOrder[MaxNum];
int j = 0;

void InOrder_BST(int root, int N, int InOrder[]) 
{
	if (root <= N) 
	{
		//完全二叉树在层序输出时，下标为i的结点的左孩子和右孩子的下标分别为2i,2i+1
		InOrder_BST(root * 2, N, InOrder);
		LevelOrder[root] = InOrder[j++];
		InOrder_BST(root * 2 + 1, N, InOrder);
	}
}

int main() 
{
	int N, InOrder[MaxNum];
	cin >> N;
	for (int i = 0; i < N; i++) 
	{
		cin >> InOrder[i];
	}
	sort(InOrder, InOrder + N);  //二叉搜索树的中序输出为一个升序的序列，当对输入的数据进行升序排列后获得了完全二叉排序树的中序遍历结果
	InOrder_BST(1, N, InOrder);
	cout << LevelOrder[1];
	for (int i = 2; i <= N; i++) 
	{
		cout << " " << LevelOrder[i];
	}
	system("pause");
	return 0;
}