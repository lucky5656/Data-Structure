#include <iostream>
using namespace std;
#define MaxTree 30
#include <stack>
#include<string>

typedef struct Node {
	int data;
	struct Node *left, *right;
}Node, *Tree;

bool flag = true;//后序输出时是否输出空格 

//已知前序和中序遍历，建立一棵二叉树
Tree BuildTree(int n, int *PreOrder, int *InOrder) 
{
	if (n == 0)
		return NULL;
	Tree tree = (Tree)malloc(sizeof(Node));
	tree->data = PreOrder[0];
	tree->left = tree->right = NULL;
	int i;
	for (i = 0; i < n; i++) 
	{
		if (PreOrder[0] == InOrder[i])
			break;
	}
	int L = i;  //左子树结点点数
 	int R = n - (i + 1);  //右子树结点数
	tree->left = BuildTree(L, PreOrder + 1, InOrder);
    tree->right = BuildTree(R, PreOrder + L + 1, InOrder + L + 1);
	return tree;
}

//进行后序遍历
void PostOrder(Tree tree) 
{
	if (!tree)
		return;
	PostOrder(tree->left);
	PostOrder(tree->right);
	if (flag) 
	{
		flag = false;
		cout << tree->data;
	}
	else 
	{
		cout << " " << tree->data;
	}
}

int main() 
{
	int n, num;
	cin >> n;
	int PreOrder[MaxTree], InOrder[MaxTree];
	int p = 0, k = 0;
	string s;
	stack<int> st;
	for (int i = 0; i < 2 * n; i++)
	{
		cin >> s;
		if (s == "Push") 
		{
			cin >> num;
			PreOrder[p++] = num;  //PreOrder中存放先序遍历的序列
			st.push(num);
		}
		else {
			InOrder[k++] = st.top();  //InOrder中存放中序遍历的序列
			st.pop();
		}
	}
	Tree tree = BuildTree(n, PreOrder, InOrder);
	PostOrder(tree);
	system("pause");
	return 0;
}