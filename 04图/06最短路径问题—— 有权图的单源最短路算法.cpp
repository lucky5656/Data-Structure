//#include<iostream>
//using namespace std;
//
///* 邻接矩阵储存——有权图的单源最短路算法 */
//
//#define ERROR 0        
//#define INFINITY 65535   // ∞设为双字节无符号整数的最大值65535      
//#define MaxVertexNum 100   //最大顶点数设为100     
//typedef int Vertex;   //用顶点下标表示顶点,为整型
//typedef int WeightType;   //边的权值设为整型
//
//int Visited[MaxVertexNum];
//int dist[MaxVertexNum];
//int path[MaxVertexNum];
//
//// 边的定义
//typedef struct ENode *PtrToENode;
//struct ENode {
//	Vertex V1, V2;   // 有向边<V1, V2>
//	WeightType Weight;  // 权重
//};
//typedef PtrToENode Edge;
//
//// 图结点的定义
//typedef struct GNode *PtrToGNode;
//struct GNode {
//	int Nv;  // 顶点数
//	int Ne;  // 边数
//	WeightType G[MaxVertexNum][MaxVertexNum];  // 邻接矩阵
//};
//typedef PtrToGNode MGraph; // 以邻接矩阵存储的图类型
//
//// 初始化一个有VertexNum个顶点但没有边的图
//MGraph CreateGraph(int VertexNum)
//{
//	Vertex V, W;
//	MGraph Graph;
//
//	Graph = (MGraph)malloc(sizeof(struct GNode));  // 建立图
//	Graph->Nv = VertexNum;
//	Graph->Ne = 0;
//	/* 初始化邻接矩阵 */
//	/* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
//	for (V = 0; V <= Graph->Nv; V++)
//		for (W = 0; W <= Graph->Nv; W++)
//			Graph->G[V][W] = INFINITY;
//
//	return Graph;
//}
//
//void InsertEdge(MGraph Graph, Edge E)
//{
//	/* 插入边 <V1, V2> */
//	Graph->G[E->V1][E->V2] = E->Weight;
//	/* 若是无向图，还要插入边<V2, V1> */
//	//Graph->G[E->V2][E->V1] = 1;    
//}
//
//// 建图 
//MGraph BuildGraph() 
//{
//	MGraph Graph;
//	Edge E;
//	Vertex V;
//	int Nv, i;
//
//	cin >> Nv;   // 读入顶点数 
//	Graph = CreateGraph(Nv);  // 初始化有Nv个顶点但没有边的图
//
//	cin >>(Graph->Ne);  // 读入边数 
//	if (Graph->Ne != 0)  // 如果有边
//	{
//		E = (Edge)malloc(sizeof(struct ENode));  // 建立边结点
//		for (i = 0; i < Graph->Ne; i++) 
//		{
//			cin >> E->V1 >> E->V2 >> E->Weight;// 读入边，格式为"起点 终点 权重"，插入邻接矩阵 
//			InsertEdge(Graph, E);
//		}
//	}
//
//	return Graph;
//}
//
///* IsEdge(Graph, V, W)检查<V, W>是否图Graph中的一条边，即W是否V的邻接点。  */
///* 此函数根据图的不同类型要做不同的实现，关键取决于对不存在的边的表示方法。*/
///* 例如对有权图, 如果不存在的边被初始化为INFINITY, 则函数实现如下:         */
//bool IsEdge(MGraph Graph, Vertex V, Vertex W)
//{
//	return Graph->G[V][W] < INFINITY ? true : false;
//}
//
//// 返回未被收录顶点中的最小dist者
//Vertex FindMinDist(MGraph Graph) 
//{
//	Vertex MinV, V;
//	int MinDist = INFINITY;
//
//	for (V = 1; V <= Graph->Nv; V++) 
//	{
//		if (Visited[V] == false && dist[V] < MinDist)  // 若V未被收录，且dist[V]更小 
//		{
//			MinDist = dist[V];  // 更新最小距离
//			MinV = V;  // 更新最小顶点
//		}
//	}
//	if (MinDist < INFINITY)  // 若找到最小dist
//		return MinV;  // 返回对应的顶点下标
//	else return ERROR;  // 若这样的顶点不存在，返回错误标记
//}
//
//// 以S为出发点对邻接矩阵存储的图Graph进行BFS搜索
//bool Dijkstra(MGraph Graph, Vertex S)
//{
//	Vertex V, W;
//
//	// 初始化：此处默认邻接矩阵中不存在的边用INFINITY表示
//	for (V = 1; V <= Graph->Nv; V++) 
//	{
//		dist[V] = Graph->G[S][V];
//		if (dist[V] < INFINITY)
//			path[V] = S;
//		else
//			path[V] = -1;
//		Visited[V] = false;
//	}
//	// 先将起点收入集合
//	dist[S] = 0;
//	Visited[S] = true;
//
//	while (1)
//	{
//		// 找到未被收入顶点中dist最小者
//		V = FindMinDist(Graph);
//		if (V == ERROR)  // 若这样的V不存在
//			break;  //算法结束  
//		Visited[V] = true;  //收录V  
//
//		for (W = 1; W <= Graph->Nv; W++)  //对图中每个顶点W  
//			if (Visited[W] == false && Graph->G[V][W] < INFINITY)  //若W未被收录并且是V的邻接点
//			{  
//				if (Graph->G[V][W] < 0)  //若有负边  
//					return false;  //不能正确解决，返回错误标记  
//				if (dist[V] + Graph->G[V][W] < dist[W])  //若收录V使得dist[W]变小  
//				{
//					dist[W] = dist[V] + Graph->G[V][W];  //更新dist[W]  
//					path[W] = V;  //更新S到W的路径  
//				}
//			}
//	}/*while结束*/
//	return true;  //算法执行完毕，返回正确标记
//}
//
//int main() 
//{
//	MGraph Graph = BuildGraph();
//
//	for (int i = 1; i <= MaxVertexNum; i++) 
//	{ 
//		Visited[i] = false; 
//		dist[i] = INFINITY; 
//		path[i] = -1; 
//	}
//	Dijkstra(Graph, 1);
//	for (int i = 1; i <= Graph->Nv; i++) 
//	{
//		cout << "点 " << i << " 到源点 1 的最短距离是：" << dist[i] << "  上一步结点是：" << path[i] << endl;
//	}
//	system("pause");
//	return 0;
//}