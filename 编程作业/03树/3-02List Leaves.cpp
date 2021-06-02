#include<iostream>
using namespace std;
#define MaxTree 10
#define Null -1
#include<queue>

#define Tree int
struct TreeNode {
	Tree left;   // 左子树的下标 
	Tree right;  // 右子树的下标 
}T[MaxTree];

// 建二叉树，返回根结点
Tree BuildTree(struct TreeNode T[])
{
	int i, n;
	int check[MaxTree];  //创建一个check数组来确定根节点，若在静态链表中未出现的下标则为根节点
	char left, right;
	Tree root = Null;   //若n为0，返回Null

	cin >> n;
	if (n)
	{
		for (i = 0; i < n; i++)
		{
			check[i] = 0;
		}
		for (i = 0; i < n; i++)
		{
			cin >> left >> right;
			if (left != '-')
			{
				T[i].left = left - '0';   //若输入不为'-',那字符减去字符0转换为整型数值
				check[T[i].left] = 1; //把在静态链表中出现过的数值标记为1
			}
			else if (left == '-')
				T[i].left = Null;
			if (right != '-')
			{
				T[i].right = right - '0';
				check[T[i].right] = 1;
			}
			else if (right == '-')
				T[i].right = Null;
		}

		for (i = 0; i < n; i++)
		{
			if (!check[i])
				break;
		}
		root = i;

	}
	return root;
}

//层序遍历，输出叶结点
void PrintLeava(int root)
{
	if (root == Null)  //如果根结点为空证明是空树
	{
		cout << "-1" << endl;
		return;
	}

	queue<int>q;
	q.push(root);
	int i = 0;
	int leave[MaxTree];
	while (!q.empty())
	{
		int s = q.front();
		q.pop();
		if (T[s].left == Null && T[s].right == Null)  //如果该结点既没有左孩子又没有右孩子就是叶子
		{
			leave[i++] = s;
		}
		else
		{
			if (T[s].left != Null)/*如果左孩子不为空就push左孩子*/
			{
				q.push(T[s].left);
			}
			if (T[s].right != Null)  //如果右孩子不为空就push右孩子
			{
				q.push(T[s].right);
			}
		}
	}
	for (int j = 0; j < i; j++)  //按顺序输出叶子
	{
		if (j < i - 1)  //相邻数字之间必须有一个空格
		{
			cout << leave[j] << " ";
		}
		else  //j=i-1为行尾不能有多余的空格
		{
			cout << leave[j];
		}
	}
}

int main()
{
	Tree root = BuildTree(T);
	PrintLeava(root);
	system("pause");
	return 0;
}