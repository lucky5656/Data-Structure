#include<iostream>
using namespace std;

/* 邻接矩阵储存——多源最短路算法 */

#define INFINITY 65535   // ∞设为双字节无符号整数的最大值65535      
#define MaxVertexNum 100   //最大顶点数设为100     
typedef int Vertex;   //用顶点下标表示顶点,为整型
typedef int WeightType;   //边的权值设为整型

// 图结点的定义
typedef struct GNode *PtrToGNode;
struct GNode {
	int Nv;  // 顶点数
	int Ne;  // 边数
	WeightType G[MaxVertexNum][MaxVertexNum];  // 邻接矩阵
};
typedef PtrToGNode MGraph; // 以邻接矩阵存储的图类型

//边的数据结构
typedef struct ENode *PtrToENode;
struct ENode {
	Vertex V1, V2;  // 有向边<V1, V2>
	WeightType Weight;  // 权重
};
typedef PtrToENode Edge;

// 初始化一个有VertexNum个顶点但没有边的图
MGraph CreateGraph(int VertexNum)
{
	Vertex V, W;
	MGraph Graph;

	Graph = (MGraph)malloc(sizeof(struct GNode));  // 建立图
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* 初始化邻接矩阵 */
	/* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
	for (V = 0; V <= Graph->Nv; V++)
		for (W = 0; W <= Graph->Nv; W++)
			Graph->G[V][W] = INFINITY;

	return Graph;
}

// 插入边 
void InsertEdge(MGraph Graph, Edge E) 
{
	// 插入边 <V1,V2>
	Graph->G[E->V1][E->V2] = E->Weight;

	// 如果是无向图，还需要插入边 <V2,V1>
	Graph->G[E->V2][E->V1] = E->Weight;
}

// 建图 
MGraph BuildGraph() 
{
	MGraph Graph;
	Edge E;
	Vertex V;
	int Nv, i;

	cin >> Nv;   // 读入顶点数 
	Graph = CreateGraph(Nv);  // 初始化有Nv个顶点但没有边的图

	cin >>(Graph->Ne);  // 读入边数 
	if (Graph->Ne != 0)  // 如果有边
	{
		E = (Edge)malloc(sizeof(struct ENode));  // 建立边结点
		for (i = 0; i < Graph->Ne; i++) 
		{
			cin >> E->V1 >> E->V2 >> E->Weight;// 读入边，格式为"起点 终点 权重"，插入邻接矩阵 
			InsertEdge(Graph, E);
		}
	}

	return Graph;
}

//多源最短路径
bool Floyd(MGraph Graph, WeightType D[][MaxVertexNum], Vertex path[][MaxVertexNum])
{
	Vertex i, j, k;

	// 初始化
	for (i = 1; i <= Graph->Nv; i++)
		for (j = 1; j <= Graph->Nv; j++) 
		{
			D[i][j] = Graph->G[i][j];
			path[i][j] = -1;
		}

	for (k = 1; k <= Graph->Nv; k++)
		for (i = 1; i <= Graph->Nv; i++)
			for (j = 1; j <= Graph->Nv; j++)
				if (D[i][k] + D[k][j] < D[i][j]) 
				{
					D[i][j] = D[i][k] + D[k][j];
					if (i == j && D[i][j] < 0)  // 若发现负值圈
						return false;  // 不能正确解决，返回错误标记
					path[i][j] = k;
				}
	return true;  // 算法执行完毕，返回正确标记
}

//路径的打印
void PrintPath(Vertex path[][MaxVertexNum], Vertex v1, Vertex v2)
{
	cout << v2 << " ";
	while (1) 
	{
		if (path[v1][v2] != -1)
			cout << path[v1][v2] << " ";
		else
			break;
		v2 = path[v1][v2];
	}
	cout << v1 << endl;
}

int main() 
{
	MGraph Graph = BuildGraph();

	WeightType Weight[MaxVertexNum][MaxVertexNum];
	Vertex path[MaxVertexNum][MaxVertexNum];
	Floyd(Graph, Weight, path);

	cout << "请输入要查询最短路径的两个顶点：";
	Vertex v1, v2;
	cin >> v1 >> v2;
	cout << "最短路径为：";
	PrintPath(path, v1, v2);
	cout << "最短路径对应的权值为：" << Weight[v1][v2] << endl;

	system("pause");
	return 0;
}