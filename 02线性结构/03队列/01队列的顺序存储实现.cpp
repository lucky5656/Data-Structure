#include<iostream>
using namespace std;
#define MaxSize 100
typedef int ElementType;
typedef struct QNode *Queue;
struct QNode {
	ElementType Data[MaxSize];
	int front;   // 记录队头 
	int rear;    // 记录队尾 
};
Queue Q;

Queue CreateQueue();  // 初始化队列 
void AddQ(Queue Q, ElementType item);  //  入队
int IsFull(Queue Q); // 判断队列是否已满 
ElementType DeleteQ(Queue Q);  // 出队 
int IsEmpty(Queue Q); // 判断队列是否为空 

// 初始化 
Queue CreateQueue() {
	Q = (Queue)malloc(sizeof(struct QNode));
	Q->front = -1;
	Q->rear = -1;
	return Q;
}

// 判断队列是否已满
int IsFull(Queue Q) {
	return ((Q->rear + 1) % MaxSize == Q->front);
}

// 入队 
void AddQ(Queue Q, ElementType item) {
	if (IsFull(Q)) {
		cout << "队列满" << endl;
		return;
	}
	else {
		Q->rear = (Q->rear + 1) % MaxSize;  //front和rear指针的移动采用“加1取余”法,体现了顺序存储的“循环使用”
		Q->Data[Q->rear] = item;
	}
}

//判断队列是否为空
int IsEmpty(Queue Q) {
	return (Q->front == Q->rear);
}

// 出队
ElementType DeleteQ(Queue Q) {
	if (IsEmpty(Q)) {
		cout << "队列空" << endl;
		return 0;
	}
	else {
		Q->front = (Q->front + 1) % MaxSize;
		return Q->Data[Q->front];
	}
}

int main() {
	Q = CreateQueue();

	AddQ(Q, 1);
	cout << "1入队" << endl;

	AddQ(Q, 2);
	cout << "2入队" << endl;

	AddQ(Q, 3);
	cout << "3入队" << endl;

	cout << DeleteQ(Q) << "出队" << endl;
	cout << DeleteQ(Q) << "出队" << endl;

	system("pause");

	return 0;
}