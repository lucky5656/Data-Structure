#include<iostream>
using namespace std;

/* 邻接矩阵存储的图 - BFS */

#define MaxVertexNum 100    // 最大顶点数设为100
#define INFINITY 65535     // ∞设为双字节无符号整数的最大值65535  
#define ERROR 0  
typedef int Vertex;         // 用顶点下标表示顶点,为整型
typedef int WeightType;        // 边的权值设为整型
typedef char DataType;        // 顶点存储的数据类型设为字符型
bool Visited[MaxVertexNum];

// 边的定义
typedef struct ENode *PtrToENode;
struct ENode {
	Vertex V1, V2;    // 有向边<V1,V2> 
	WeightType Weight;  // 权重 
};
typedef PtrToENode Edge;

// 图结点的定义
typedef struct GNode *PtrToGNode;
struct GNode {
	int Nv;   // 顶点数 
	int Ne;   // 边数
	WeightType G[MaxVertexNum][MaxVertexNum];  //邻接矩阵
	DataType Data[MaxVertexNum]; // 存顶点的数据(注意：很多情况下，顶点无数据，此时Data[]可以不用出现)
};
typedef PtrToGNode MGraph;  // 以邻接矩阵存储的图类型

struct Node {
	int Data;
	struct Node *Next;
};

struct QNode {
	struct Node *rear;
	struct Node *front;
};
typedef struct QNode *Queue;

// 初始化图 
MGraph CreateGraph(int VertexNum)
{
	Vertex V, W;
	MGraph Graph;

	Graph = (MGraph)malloc(sizeof(struct GNode));  // 建立图
	Graph->Nv = VertexNum;
	Graph->Ne = 0;
	/* 初始化邻接矩阵 */
	/* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
	for (V = 0; V < VertexNum; V++)
		for (W = 0; W < VertexNum; W++)
			Graph->G[V][W] = 0;
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

	cin >> (Graph->Ne);  // 读入边数 
	if (Graph->Ne != 0)  // 如果有边
	{
		E = (Edge)malloc(sizeof(struct ENode));  // 建立边结点
		for (i = 0; i < Graph->Ne; i++)
		{
			cin >> E->V1 >> E->V2 >> E->Weight;// 读入边，格式为"起点 终点 权重"，插入邻接矩阵 
			InsertEdge(Graph, E);
		}
	}

	// 如果顶点有数据的话，读入数据
	for (V = 0; V < Graph->Nv; V++)
		cin >> (Graph->Data[V]);

	return Graph;
}

int IsEmpty(Queue Q) 
{
	return(Q->front == NULL);
};

Queue CreateQueue() 
{
	Queue PtrQ;
	PtrQ = (Queue)malloc(sizeof(struct QNode));
	struct Node *rear;
	struct Node *front;
	rear = (Node*)malloc(sizeof(struct Node));
	rear = NULL;
	front = (Node*)malloc(sizeof(struct Node));
	front = NULL;
	PtrQ->front = front;
	PtrQ->rear = rear;
	return PtrQ;
};

int DeleteQ(Queue PtrQ) 
{
	struct Node *FrontCell;
	int FrontElem;

	if (IsEmpty(PtrQ)) 
	{
		cout << "队列空" << endl;
		return ERROR;
	}
	FrontCell = PtrQ->front;
	if (PtrQ->front == PtrQ->rear)
		PtrQ->front = PtrQ->rear = NULL;
	else 
		PtrQ->front = PtrQ->front->Next;
	FrontElem = FrontCell->Data;
	free(FrontCell);
	return FrontElem;
}

void InsertQ(int item, Queue PtrQ) 
{
	struct Node *FrontCell;
	FrontCell = (Node*)malloc(sizeof(struct Node));
	FrontCell->Data = item;
	FrontCell->Next = NULL;

	if (IsEmpty(PtrQ)) 
	{
		PtrQ->front = FrontCell;
		PtrQ->rear = FrontCell;
	}
	else 
	{
		PtrQ->rear->Next = FrontCell;
		PtrQ->rear = FrontCell;
	}
};

/* IsEdge(Graph, V, W)检查<V, W>是否图Graph中的一条边，即W是否V的邻接点。  */
/* 此函数根据图的不同类型要做不同的实现，关键取决于对不存在的边的表示方法。*/
/* 例如对有权图, 如果不存在的边被初始化为INFINITY, 则函数实现如下:         */
bool IsEdge(MGraph Graph, Vertex V, Vertex W)
{
	return Graph->G[V][W] < INFINITY ? true : false;
}

// 以S为出发点对邻接矩阵存储的图Graph进行BFS搜
void BFS(MGraph Graph, Vertex S, void(*Visit)(Vertex))
{
	Queue Q;
	Vertex V, W;

	Q = CreateQueue();  // 创建空队列
	Visit(S);
	Visited[S] = true;  // 标记S已访问，Visited[]为全局变量，已经初始化为false
	InsertQ(S, Q);  // S入队列

	while (!IsEmpty(Q)) 
	{
		V = DeleteQ(Q);   // 弹出V
		for (W = 0; W < Graph->Nv; W++)  // 对图中的每个顶点W
			// 若W是V的邻接点并且未访问过
			if (!Visited[W] && IsEdge(Graph, V, W)) 
			{
				Visit(W);  // 访问顶点
				Visited[W] = true;  // 标记W已访问
				InsertQ(W, Q);  // W入队列
			}
	} /* while结束*/
}

void Visit(Vertex V)
{
	cout << "正在访问顶点" << V << endl;
}

int main() 
{
	MGraph Graph = BuildGraph();
	for (int i = 0; i < MaxVertexNum; i++)
	    Visited[i] = false;
	BFS(Graph, 0, Visit);
	system("pause");
	return 0;
}
