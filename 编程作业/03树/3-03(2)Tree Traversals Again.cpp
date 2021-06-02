#include <iostream>
using namespace std;
#define MaxTree 30
#include <stack>
#include<string>

int pre[MaxTree], in[MaxTree], post[MaxTree];

//前序起始位置，中序起始位置，后序起始位置，元素个数
void PostOrder(int prel, int inl, int postl, int n)
{
	if (n == 0)
		return;//递归结束
	if (n == 1)
	{
		post[postl] = pre[prel];
		return;
	}
	int root = pre[prel];
	post[postl + n - 1] = root;
	int i;
	for (i = 0; i < n; i++)  //找到根在中序中的位置
	{
		if (in[inl + i] == root)
			break;
	}
	int L = i;  //左子树结点点数
	int R = n - (i + 1);  //右子树结点数
	PostOrder(prel + 1, inl, postl, L);  //建立左子树
	PostOrder(prel + L + 1, inl + L + 1, postl + L, R);  //建立右子树
}

int main()
{
	int n, num;
	cin >> n;
	int p = 0, k = 0;
	string s;
	stack<int> st;
	for (int i = 0; i < 2 * n; i++)
	{
		cin >> s;
		if (s == "Push")
		{
			cin >> num;
			pre[p++] = num;
			st.push(num);
		}
		else
		{
			in[k++] = st.top();
			st.pop();
		}
	}
	PostOrder(0, 0, 0, n);
	for (int i = 0; i < n; i++)
	{
		if (i == 0)
			cout << post[i];
		else
			cout << " " << post[i];
	}
	system("pause");
	return 0;
}