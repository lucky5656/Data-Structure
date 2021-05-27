#include<iostream>
using namespace std;
#define MaxSize 100   // 堆栈元素的最大个数 
typedef int ElementType; // ElementType 暂时定义为 int 类型 
typedef struct SNode *Stack;
struct SNode {
	ElementType Data[MaxSize];   // 存储堆栈元素
	int Top;  // 记录栈顶元素下标 
};
Stack S;

Stack CreateStack();  // 初始化堆栈 
int IsFull(Stack S); // 判断堆栈是否已满 
int IsEmpty(Stack S);  // 判断堆栈是否为空 
void Push(Stack S, ElementType item);  // 入栈 
ElementType Pop(Stack S);  // 出栈

// 初始化堆栈 
Stack CreateStack() {
	S = (Stack)malloc(sizeof(struct SNode));
	S->Top = -1;
	return S;
}

// 是否已满 
int IsFull(Stack S) {
	return (S->Top == MaxSize - 1);
}

// 是否为空 
int IsEmpty(Stack S) {
	return (S->Top == -1);
}

// 入栈 
void Push(Stack S, ElementType item) {
	if (IsFull(S)) {   // Top 从 0 开始 
		cout << "堆栈满" << endl;
		return;
	}
	else {
		S->Top++;   // 栈顶元素加一 
		S->Data[S->Top] = item;   // 放进最上 
		return;
	}
}

// 出栈
ElementType Pop(Stack S) {
	if (IsEmpty(S)) {
		cout << "堆栈空" << endl;
		return NULL;
	}
	else {
		ElementType val = S->Data[S->Top];  //取出最上 
		S->Top--;  // 栈顶元素减一 
		return val;
	}
}
int main() {
	S = CreateStack();

	cout << "1入栈" << endl;
	Push(S, 1);

	cout << "2入栈" << endl;
	Push(S, 2);

	cout << "3入栈" << endl;
	Push(S, 3);

	cout << Pop(S) << "出栈" << endl;

	cout << Pop(S) << "出栈" << endl;

	system("pause");

	return 0;
}