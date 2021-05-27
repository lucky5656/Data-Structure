#include<iostream>
using namespace std;
typedef int ElementType;
typedef struct SNode *Stack;
struct SNode {
	ElementType Data;
	Stack Next;
};
Stack S;

Stack CreateStack();  // 初始化链栈 
int IsEmpty(Stack S);  // 判断链栈是否为空 
void Push(Stack S, ElementType item);  // 入栈 
ElementType Pop(Stack S);  // 出栈


// 初始化 
Stack CreateStack() {
	S = (Stack)malloc(sizeof(struct SNode));
	S->Next = NULL;
	return S;
}

// 判断是否为空 
int IsEmpty(Stack S) {
	return (S->Next == NULL);
}

// 入栈
void Push(Stack S, ElementType item) {
	Stack tmp;
	tmp = (Stack)malloc(sizeof(struct SNode));
	tmp->Data = item;
	// 链栈栈顶元素是链表头结点，新入栈的链表在栈顶元素后面 
	tmp->Next = S->Next;
	S->Next = tmp;
}

// 出栈
ElementType Pop(Stack S) {
	Stack First;
	ElementType TopVal;
	if (IsEmpty(S)) {
		cout << "堆栈空" << endl;
		return NULL;
	}
	else {
		First = S->Next;   // 出栈第一个元素在栈顶元素后面 
		S->Next = First->Next;  //把第一个元素从链栈删除 
		TopVal = First->Data;   // 取出被删除结点的值 
		free(First);  // 释放空间 
		return TopVal;
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