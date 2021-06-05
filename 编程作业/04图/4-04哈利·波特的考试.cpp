#include<iostream>
using namespace std;

#define MaxVertexNum 100
#define INFINITY 65535;
typedef int Vertex;
typedef int WeightType;

// 边的定义
typedef struct ENode *PtrToENode;
struct ENode
{
	Vertex V1, V2;  //有向边<v1,v2>
	WeightType Weight;  //权重
};
typedef PtrToENode Edge;

// 图结点的定义
typedef struct GNode *PtrToGNode;
struct GNode
{
	int Nv;  //顶点数
	int Ne;  //边数
	WeightType G[MaxVertexNum][MaxVertexNum];  //邻接矩阵
};
typedef PtrToGNode MGraph;  //以邻接矩阵存储的图类型

// 初始化一个有VertexNum个顶点但没有边的图
MGraph CreateGraph(int VertexNum)
{
	Vertex V, W;
	MGraph Graph;

	Graph = (MGraph)malloc(sizeof(struct GNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	for (V = 0; V < Graph->Nv; V++)
	{
		for (W = 0; W < Graph->Nv; W++)
			Graph->G[V][W] = INFINITY;
	}
	return Graph;
}

//插入边
void InsertEdge(MGraph Graph, Edge E)
{
	Graph->G[E->V1][E->V2] = E->Weight;
	Graph->G[E->V2][E->V1] = E->Weight;
}

//建图
MGraph BuildGraph()
{
	MGraph Graph;
	Edge E;
	int Nv, i;
	cin >> Nv;
	Graph = CreateGraph(Nv);

	cin >> (Graph->Ne);
	if (Graph->Ne != 0)
	{
		E = (Edge)malloc(sizeof(struct ENode));
		for (i = 0; i < Graph->Ne; i++)
		{
			cin >> E->V1 >> E->V2 >> E->Weight;
			E->V1--;  //起始编号从0开始
			E->V2--;
			InsertEdge(Graph, E);
		}
	}
	return Graph;
}

void Floyd(MGraph Graph, WeightType D[][MaxVertexNum])
{
	Vertex i, j, k;

	for (i = 0; i < Graph->Nv; i++)
	{
		for (j = 0; j < Graph->Nv; j++)
		{
			D[i][j] = Graph->G[i][j];
		}
	}
	for (k = 0; k < Graph->Nv; k++)
	{
		for (i = 0; i < Graph->Nv; i++)
		{
			for (j = 0; j < Graph->Nv; j++)
			{
				if (D[i][k] + D[k][j] < D[i][j])
				{
					D[i][j] = D[i][k] + D[k][j];
				}
			}
		}
	}
}

WeightType FindMaxDist(WeightType D[][MaxVertexNum], Vertex i, int N)
{
	WeightType MaxDist;
	Vertex j;

	MaxDist = 0;
	for (j = 0; j < N; j++)  //找出i到其他动物j的最长距离
	{
		if (i != j && D[i][j] > MaxDist)
			MaxDist = D[i][j];
	}
	return MaxDist;
}

void FindAnimal(MGraph Graph)
{
	WeightType D[MaxVertexNum][MaxVertexNum], MaxDist, MinDist;
	Vertex Animal, i;

	Floyd(Graph, D);

	MinDist = INFINITY;
	for (i = 0; i < Graph->Nv; i++)
	{
		MaxDist = FindMaxDist(D, i, Graph->Nv);
		if (MaxDist == 65535)  //说明从i无法变出的动物
		{
			cout << "0" << endl;
			return;
		}
		if (MinDist > MaxDist)  //找到最长距离更小的动物
		{
			MinDist = MaxDist;  //更新距离，记录编号
			Animal = i + 1;
		}

	}
	cout << Animal << " " << MinDist << endl;
}

int main()
{
	MGraph G = BuildGraph();
	FindAnimal(G);
	system("pause");
	return 0;
}