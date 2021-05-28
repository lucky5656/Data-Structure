#include<iostream>
using namespace std;
typedef int ElementType;
typedef struct QNode *Queue;
struct Node {
	ElementType Data;
	struct Node *Next;
};
struct QNode {
	struct Node *rear;    // 指向队尾结点 
	struct Node *front;   // 指向队头结点 
};
Queue Q;

Queue CreateQueue();  // 初始化队列 
void AddQ(Queue Q, ElementType item);  //  入队
ElementType DeleteQ(Queue Q);  // 出队 
int IsEmpty(Queue Q); // 判断队列是否为空 

// 初始化 
Queue CreateQueue() {
	Q = (Queue)malloc(sizeof(struct QNode));
	Q->front = NULL;
	Q->rear = NULL;
	return Q;
}

// 是否为空 
int IsEmpty(Queue Q) {
	return (Q->front == NULL);
}

// 入队
void AddQ(Queue Q, ElementType item) {
	struct Node *node;
	node = (struct Node *)malloc(sizeof(struct Node));
	node->Data = item;
	node->Next = NULL;
	if (Q->rear == NULL) {  //此时队列空 
		Q->rear = node;
		Q->front = node;
	}
	else { //不为空 
		Q->rear->Next = node;  // 将结点入队 
		Q->rear = node;   // rear 仍然保持最后 
	}
}

// 出队
ElementType DeleteQ(Queue Q) {
	struct Node *FrontCell;
	ElementType FrontElem;
	if (IsEmpty(Q)) {
		cout << "队列空" << endl;
		return 0;
	}
	FrontCell = Q->front;
	if (Q->front == Q->rear) { // 队列中只有一个元素 
		Q->front = Q->rear = NULL;
	}
	else {
		Q->front = Q->front->Next;
	}
	FrontElem = FrontCell->Data;
	free(FrontCell);
	return FrontElem;
}

int main() {
	Q = CreateQueue();

	cout << "入队1" << endl;
	AddQ(Q, 1);

	cout << "入队2" << endl;
	AddQ(Q, 2);

	cout << "入队3" << endl;
	AddQ(Q, 3);

	cout << "出队" << DeleteQ(Q) << endl;
	cout << "出队" << DeleteQ(Q) << endl;
	cout << "出队" << DeleteQ(Q) << endl;
	cout << DeleteQ(Q) << endl;

	system("pause");

	return 0;
}