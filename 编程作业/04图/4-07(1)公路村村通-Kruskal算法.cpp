#include<iostream>
using namespace std;
#include<queue>
#include<vector> 

#define MaxVertex 1005
typedef int Vertex;
int N;  // 顶点 
int M;  // 边 
int parent[MaxVertex];   // 并查集
struct Node {
	Vertex v1;
	Vertex v2;
	int weight;
	// 重载运算符 
	bool operator < (const Node &a) const
	{
		return weight > a.weight;
	}
};
priority_queue<Node> q;  // 最小堆 
vector<Node> MST; // 最小生成树 
int sum;

// 初始化图信息 
void BuildGraph() 
{
	Vertex v1, v2;
	int w;
	cin >> N >> M;
	for (int i = 1; i <= N; i++) 
	{
		parent[i] = -1;
	}
	// 初始化点
	for (int i = 0; i < M; i++) 
	{
		cin >> v1 >> v2 >> w;
		struct Node tmpE;
		tmpE.v1 = v1;
		tmpE.v2 = v2;
		tmpE.weight = w;
		q.push(tmpE);
	}
	sum = 0;
}

//  路径压缩查找 
int Find(int x) 
{
	if (parent[x] < 0)
		return x;
	else
		return parent[x] = Find(parent[x]);
}

//  按秩归并 
void Union(int x1, int x2) 
{
	x1 = Find(x1);
	x2 = Find(x2);
	if (parent[x1] < parent[x2]) 
	{
		parent[x1] += parent[x2];
		parent[x2] = x1;
	}
	else 
	{
		parent[x2] += parent[x1];
		parent[x1] = x2;
	}
}

void Kruskal() 
{
	while (MST.size() != M - 1 && !q.empty()) 
	{
		Node E = q.top();    // 最小堆，出队权重最小的 
		q.pop();
		if (Find(E.v1) != Find(E.v2))  // 判断是否属于同一集合 
		{
			sum += E.weight;
			Union(E.v1, E.v2);    // 并 
			MST.push_back(E);
		}
	}
}

int main() 
{
	BuildGraph();
	Kruskal();
	// 图连通 
	if (MST.size() == N - 1)
		cout << sum << endl;
	else
		cout << -1 << endl;
	system("pause");
	return 0;
}