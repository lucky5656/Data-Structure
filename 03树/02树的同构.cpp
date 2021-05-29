#include<iostream>
using namespace std;
#define MaxTree 10
#define ElementType char
#define Tree int
#define Null -1
struct TreeNode {
	ElementType data;    // 存值 
	Tree left;   // 左子树的下标 
	Tree right;  // 右子树的下标 
}T1[MaxTree], T2[MaxTree];

// 返回根结点的第一种方法 （根节点编号未出现在其他结点编号的后面，创建一个check数组来确定）
// 建二叉树，返回根结点
Tree BuildTree(struct TreeNode T[])
{
	int i;
	int n;
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
			cin >> T[i].data >> left >> right;
			if (left != '-') 
			{
				T[i].left = left - '0';   //若输入不为'-',那字符减去字符0转换为整型数值
				check[T[i].left] = 1; //把在静态链表中出现过的数值标记为1
			}
			else if (left == '-') 
			{
				T[i].left = Null;
			}
			if (right != '-') 
			{
				T[i].right = right - '0';
				check[T[i].right] = 1;
			}
			else if (right == '-') 
			{
				T[i].right = Null;
			}
		}

		for (i = 0; i < n; i++) 
		{
			if (!check[i]) 
			{
				break;
			}
		}
		root = i;

	}
	return root;
}

//// 返回根结点的第二种方法 （根节点编号 = 行号和 - 左右结点编号和）
//// 建二叉树，返回根结点
//Tree BuildTree(struct TreeNode T[])
//{
//	int n;  //n为树的结点数
//	int root = 0;
//	char left, right;
//	cin >> n;
//	if (!n)
//		return Null;
//	for (int i = 0; i < n; i++) 
//	{
//		cin >> T[i].data >> left >> right;
//		if (left == '-')
//			T[i].left = Null;
//		else 
//		{
//			T[i].left = left - '0';
//			root -= T[i].left;
//		}
//		if (right == '-')
//			T[i].right = Null;
//		else 
//		{
//			T[i].right = right - '0';
//			root -= T[i].right;
//		}
//		// 0 累加到 n-1 
//		root += i;
//	}
//	return root;
//}


// 判断是否同构
bool Isomorphic(int R1, int R2) 
{
	if (R1 == Null && R2 == Null)   // 都为空 
		return true;
	if (R1 == Null && R2 != Null || R1 != Null && R2 == Null)    // 一个为空，一个不为空
		return false;
	if (T1[R1].data != T2[R2].data)   // 值不同
		return false;
	if ((T1[R1].left == Null) && (T2[R2].left == Null))  //左儿子均为空
	{
		return Isomorphic(T1[R1].right, T2[R2].right);
	}
	if ((T1[R1].left != Null && T2[R2].left != Null) && (T1[T1[R1].left].data == T2[T2[R2].left].data))  // 左儿子不为空且值相等
		return Isomorphic(T1[R1].left, T2[R2].left) && Isomorphic(T1[R1].right, T2[R2].right);
	else   // 左儿子不为空且值不等  或者 某一个左儿子为空（有可能左边和右边同构，右边和左边同构）
		return Isomorphic(T1[R1].right, T2[R2].left) && Isomorphic(T1[R1].left, T2[R2].right);
}
int main() {
	Tree R1, R2;
	R1 = BuildTree(T1);
	R2 = BuildTree(T2);
	cout << "是否同构？" << endl;
	if (Isomorphic(R1, R2))
		cout << "是" << endl;
	else
		cout << "否" << endl;

	system("pause");

	return 0;
}