#include<iostream>
using namespace std;

/* 邻接矩阵储存——无权图的单源最短路算法 */

#define INFINITY 65535   // ∞设为双字节无符号整数的最大值65535      
#define MaxVertexNum 100   //最大顶点数设为100     
typedef int Vertex;   //用顶点下标表示顶点,为整型
typedef int WeightType;   //边的权值设为整型
typedef char DataType;   //顶点存储的数据类型设为字符型

int Visited[MaxVertexNum];
int dist[MaxVertexNum];
int path[MaxVertexNum];

// 边的定义
typedef struct ENode *PtrToENode;
struct ENode {
	Vertex V1, V2;      // 有向边<V1, V2>
};
typedef PtrToENode Edge;

// 图结点的定义
typedef struct GNode *PtrToGNode;
struct GNode {
	int Nv;  // 顶点数
	int Ne;  // 边数
	WeightType G[MaxVertexNum][MaxVertexNum];  // 邻接矩阵
};
typedef PtrToGNode MGraph; // 以邻接矩阵存储的图类型

#define ERROR 0      

struct Node {
	int Data;
	struct Node *Next;
};

struct QNode {
	struct Node *rear;
	struct Node *front;
};
typedef struct QNode *Queue;

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
	for (V = 0; V < Graph->Nv; V++)
		for (W = 0; W <= Graph->Nv; W++)
			Graph->G[V][W] = INFINITY;

	return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
	/* 插入边 <V1, V2> */
	Graph->G[E->V1][E->V2] = 1;
	/* 若是无向图，还要插入边<V2, V1> */
	//Graph->G[E->V2][E->V1] = 1;  
}

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
			cin >> E->V1 >> E->V2;// 读入边，格式为"起点 终点"，插入邻接矩阵 
			InsertEdge(Graph, E);
		}
	}

	return Graph;
}

void Visit(Vertex V)
{
	cout << "正在访问顶点" << V;
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
	else {
		PtrQ->front = PtrQ->front->Next;
	}
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
	else {
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

/* dist[]和path[]为全局变量，已经初始化为-1 */
void Unweighted(MGraph Graph, Vertex S)
{   /* 以S为出发点对邻接矩阵存储的图Graph进行BFS搜索 */
	Queue Q = CreateQueue(); /* 创建空队列, MaxSize为外部定义的常数 */
	Vertex V, W;

	Visit(S);
	cout << endl;
	/* 访问顶点S：此处可根据具体访问需要改写 */
	dist[S] = 0; /* 标记S已访问 */
	InsertQ(S, Q); /* S入队列 */

	while (!IsEmpty(Q))
	{
		V = DeleteQ(Q);  /* 弹出V */
		for (W = 1; W <= Graph->Nv; W++) /* 对V的每个邻接点W->AdjV */
			if ((dist[W] == -1) && (IsEdge(Graph, V, W)))    /* 若W->AdjV未被访问 */
			{
				Visit(W);
				dist[W] = dist[V] + 1;
				cout<< "  到初始点的距离是："<<dist[W];
				/* 访问顶点W */
				path[W] = V;
				cout << "  其上一个节点是：" << path[W] << endl;
				InsertQ(W, Q); /* W入队列 */
			}
	} /* while结束*/
}

int main() 
{
	MGraph Graph = BuildGraph();

	for (int i = 1; i <= MaxVertexNum; i++)
	{
		Visited[i] = false;
		dist[i] = path[i] = -1;
	}
	Unweighted(Graph, 3);
	system("pause");
	return 0;
}
