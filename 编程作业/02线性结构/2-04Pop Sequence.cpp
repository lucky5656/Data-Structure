#include<iostream>
using namespace std;
#include<vector>
#include<stack>

int main() 
{
	int m, n, k;
	cin >> m >> n >> k;
	for (int i = 0; i < k; i++) 
	{
		stack<int> s;
		vector<int> v(n + 1);
		for (int j = 1; j <= n; j++)  //输入需要判断的是否可能是堆栈出栈的序列
			cin >> v[j];
		int cur = 0;  //出栈的次数
		for (int j = 1; j <= n; j++)
		{
			s.push(j);  //将数字1,...,n按顺序依次压入堆栈
			if (s.size() > m)  //如果s的大小已经大于堆栈的容量，说明还没有元素跟需要判断的pop序列的首元素对应上而被弹出，这个pop序列不可能是堆栈的pop序列
				break;
			while (!s.empty() && s.top() == v[cur + 1])  //当s不为空且s的栈顶元素与需要判断的pop序列的元素对应上时，弹出此元素
			{
				s.pop();  //弹出
				cur++;  //出栈的次数+1
			}
		}
		if (cur == n)  //出栈次数等于push序列的长度，说明需要判断的pop序列的所有元素均已出栈，这个pop序列可能是堆栈的pop序列
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
	system("pause");
	return 0;
}