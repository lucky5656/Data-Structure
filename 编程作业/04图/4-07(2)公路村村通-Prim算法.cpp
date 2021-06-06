#include<iostream>
using namespace std;
#include<vector>

#define Inf 100000
#define MaxSize 1001
int G[MaxSize][MaxSize];
int parent[MaxSize];
int dist[MaxSize];
int N;  // 顶点 
int M;  // 边
int sum;
vector<int>MST;

void BuildGraph()
{
	int v1, v2;
	int w;
	cin >> N >> M;
	for (int i = 1; i <= N; i++) 
	{
		for (int j = 1; j <= N; j++) 
		{
			G[i][j] = 0;
		}
		dist[i] = Inf;
		parent[i] = -1;
	}
	for (int i = 0; i < M; i++) 
	{
		cin >> v1 >> v2 >> w;
		G[v1][v2] = w;
		G[v2][v1] = w;
	}
}

void Init(int x)       //初始化第一个点和到周围点的距离
{
	dist[x] = 0;
	MST.push_back(x);
	for (int i = 1; i <= N; i++) 
	{
		if (G[x][i]) 
		{
			dist[i] = G[x][i];
			parent[i] = x;
		}
	}
}

int FindMin()      //找点周围路径最短的点
{
	int min = Inf;
	int xb = -1;
	for (int i = 1; i <= N; i++) 
	{
		if (dist[i] && dist[i] < min) 
		{
			min = dist[i];
			xb = i;
		}
	}
	return xb;
}

void Prim(int s)
{
	Init(s);
	while (1) 
	{
		int v = FindMin();
		if (v == -1)       //不存在这样的点
			break;
		sum += dist[v];
		dist[v] = 0;
		MST.push_back(v);
		for (int i = 1; i <= N; i++) 
		{
			if (G[v][i] && G[v][i] < dist[i]) 
			{
				dist[i] = G[v][i];
				parent[i] = v;
			}
		}
	}
}

int main()
{
	BuildGraph();
	Prim(1); 
	if (MST.size() == N)
		cout << sum << endl;
	else
		cout << -1 << endl;
	system("pause");
	return 0;
}