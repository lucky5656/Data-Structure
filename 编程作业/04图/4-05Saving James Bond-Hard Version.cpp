#include<iostream>
using namespace std;
#include<queue>
#include<stack>
#include<algorithm>

int n, m;
#define MINLEN 42.5
#define MaxVertex 105
struct Pointer {  // 存鳄鱼位置信息
	int x;   // 横坐标 
	int y;   // 纵坐标 
}point[MaxVertex];
bool answer = false;  // 记录007能否安全逃生
bool visited[MaxVertex] = { false };  // 判断当前点是否被访问过
int path[MaxVertex] = { -1 };  // 记录跳跃过程中踩过的鳄鱼

// 判断从当前点能否跳到岸上
bool isSave(int v) 
{
	if ((point[v].x - m <= -50) || (point[v].x + m >= 50) || (point[v].y - m <= -50) || (point[v].y + m >= 50))
		return true;
	return false;
}

// 判断2个点距离是否在跳跃能力内
bool Jump(int v1, int v2) 
{ 
	int p1 = pow(point[v1].x - point[v2].x, 2);
	int p2 = pow(point[v1].y - point[v2].y, 2);
	int r = m * m;
	if (p1 + p2 <= r)
		return true;
	return false;
}

// 当007处于孤岛时，第一次可以选择跳的鳄鱼
int FirstJump(int v) 
{
	int p1 = pow(point[v].x, 2);
	int p2 = pow(point[v].y, 2);
	int r = (m + 7.5) * (m + 7.5);
	if (p1 + p2 <= r) 
	{
		return p1 + p2;
	}
	return 0;
}

bool cmp(int a, int b) 
{
	return FirstJump(a) < FirstJump(b);
}

// 用BFS来判断最少要踩几个鳄鱼才能上岸
void BFS() 
{ 
	int b[MaxVertex];
	queue<int>q;
	// 将第一步能踩到的鳄鱼按距离从小到大的顺序进队列，因为输出结果要保证在踩的鳄鱼数量相等的情况下，输出第一步距离最短的
	for (int i = 0; i < n; i++)
		b[i] = i;
	sort(b, b + n, cmp);  // 按照第一步的距离排序（如果cmp返回是0的话，那么它就会交换位置，如果是1，保持原来位置不变）结果：0 1 2 3 4 5 7 8 9 10 12 13 15 16 6 11 14
	for (int i = 0; i < n; i++)
	{
		cout << b[i] << " ";
	}
	cout << endl;
	int last;
	for (int i = 0; i < n; i++) 
	{
		if (FirstJump(b[i]))  // 能跳上去！
		{
			q.push(b[i]);
			visited[b[i]] = true;  // 指向当前层数最后一个数
			last = b[i];
		}
	}
	int step = 2;  // 记录最少要跳跃的次数
	int tail = 0;
	while (!q.empty()) 
	{
		int p = q.front();
		q.pop();
		if (isSave(p)) 
		{
			int k = 1;
			stack<int> s;
			cout << step << endl;
			while (k < step)
			{
				s.push(p);
				p = path[p];
				k++;
			}
			while (!s.empty())
			{
				p = s.top();
				s.pop();
				cout << point[p].x << " " << point[p].y << endl;
			}
			return;
		}
		for (int i = 0; i < n; i++) 
		{
			if (!visited[i] && Jump(p, i))  // 没踩过并且能跳到
			{
				q.push(i);
				path[i] = p;  // 记得当前进队节点的父节点
				visited[i] = true;
				tail = i;  // 指向下一层的最后一个元素 
			}
		}
		if (last == p)  // 即将进入下一层
		{
			step += 1;
			last = tail;
		}
	}
	if (q.empty())  // 如果队列为空  说明没跳出去
	{
		cout << "0" << endl;
	}
}

int main() 
{
	cin >> n >> m;
	for (int i = 0; i < n; i++) 
	{
		cin >> point[i].x >> point[i].y;
	}
	if (m >= MINLEN)  // 可以直接从孤岛上跳到岸上，直接输出
	{
		cout << "1" << endl;
		return 0;
	}
	BFS();
	system("pause");
	return 0;
}