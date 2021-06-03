#include <iostream>
using namespace std;
#include<iomanip>
#include <queue>
#include <algorithm>
typedef int Vertex;

const int N = 10010;
const int M = 40000;
int G[N][N];
int n, m;
bool visited[N];

int BFS(Vertex v)
{
	queue<int> q;
	visited[v] = true;
	int level = 0;  // 层数
	int last = v;  // 记录每一圈的最后一个点
	int tail = 0;  // 缓存每一圈的最后一个点
	int count = 1;   // 6层内的点数
	q.push(v);
	while (!q.empty()) 
	{
		int temp = q.front();
		q.pop();
		for (int w = 0; w < n; w++) 
		{
			if (!visited[w] && G[temp][w]) 
			{
				visited[w] = true;
				q.push(w);
				tail = w;  // 记下当前圈的最后一个点的编号
				count++;
			}
		}

		if (last == temp)  // 如果该当前结点是这层最后一个结点
		{
			level++;  // 层数 +1
			last = tail;   // 更改 last 
		}
		if (level == 6)
			break;  // 只遍历6层，6层后停止
	}
	return count;
}

void init() 
{
	for (int i = 0; i < n; i++) 
	{
		visited[i] = false;
	}
}

int main()
{
	cin >> n >> m;
	for (int i = 0; i < m; i++) 
	{
		int V1, V2;
		cin >> V1 >> V2;
		G[V1 - 1][V2 - 1] = 1;
		G[V2 - 1][V1 - 1] = 1;
	}

	for (int i = 0; i < n; i++) 
	{
		init();
		visited[i] = false;
		cout << i + 1 << ":" << setiosflags(ios::fixed) << setprecision(2) << 1.0*BFS(i) * 100 / n << "%" << endl;
	}
	system("pause");
	return 0;
}