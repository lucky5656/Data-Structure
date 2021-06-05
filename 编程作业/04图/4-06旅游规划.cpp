#include<iostream>
using namespace std;
#define INF 1000000
#define MaxVertex 505

typedef int Vertex;
int value[MaxVertex][MaxVertex];    //收费矩阵
int G[MaxVertex][MaxVertex];    //距离矩阵
int dist[MaxVertex];  // 距离
int cost[MaxVertex];  // 费用
bool collected[MaxVertex];  // 被收录集合

int N;   // 城市的个数
int M;   // 高速公路的条数
int S;  // 出发地的城市编号
int D;  // 目的地的城市编号

// 初始化图信息
void BuildGraph() 
{
	Vertex v1, v2, w1, w2;
	cin >> N >> M >> S >> D;  // 输入：城市的个数、高速公路的条数、出发地的城市编号、目的地的城市编号
	for (Vertex i = 0; i < N; i++) 
	{
		for (Vertex j = 0; j < N; j++) 
		{
			G[i][j] = INF;
			value[i][j] = INF;
		}
		cost[i] = 0;
		collected[i] = false;
		dist[i] = INF;
	}
	for (int i = 0; i < M; i++) 
	{
		cin >> v1 >> v2 >> w1 >> w2;  // 输入：城市1、城市2、高速公路长度、收费额
		G[v1][v2] = w1;
		G[v2][v1] = w1;
		value[v1][v2] = w2;
		value[v2][v1] = w2;
	}
}

void Init() 
{
	dist[S] = 0;
	collected[S] = true;
	for (Vertex i = 0; i < N; i++)
		if (G[S][i]) 
		{
			dist[i] = G[S][i];
			cost[i] = value[S][i];
		}
}

// 查找未收录顶点中dist最小者
Vertex FindMin() 
{
	int min = INF;
	Vertex x = -1;
	for (Vertex i = 0; i < N; i++)
		if (S != i && !collected[i] && dist[i] < min) 
		{
			min = dist[i];
			x = i;
		}
	return x;
}


void Dijkstra() 
{
	Init();
	while (1) 
	{
		Vertex v = FindMin();
		if (v == -1)
			break;
		collected[v] = true;
		for (Vertex w = 0; w < N; w++) 
		{
			if (!collected[w] && G[v][w]) 
			{
				if (dist[v] + G[v][w] < dist[w]) 
				{
					dist[w] = dist[v] + G[v][w];
					cost[w] = cost[v] + value[v][w];
				}
				else if (dist[v] + G[v][w] == dist[w] && cost[v] + value[v][w] < cost[w]) 
				{
					cost[w] = cost[v] + value[v][w];
				}
			}
		}
	}
}

int main() 
{
	BuildGraph();
	Dijkstra();
	cout << dist[D] << " " << cost[D] << endl;
	system("pause");
	return 0;
}