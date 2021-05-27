#include<iostream>
using namespace std;
#define MaxSize 100   // 堆栈元素的最大个数 
typedef int ElementType; // ElementType 暂时定义为 int 类型 
typedef struct DStack *Stack;
struct DStack {
	ElementType Data[MaxSize];   // 存储堆栈元素
	int Top1; //堆栈1的栈顶指针
	int Top2; //堆栈2的栈顶指针
};
Stack S;

Stack CreateStack();  // 初始化堆栈 
void Push(Stack S, ElementType item, int Tag);  // 入栈 
ElementType Pop(Stack S, int Tag);  // 出栈

// 初始化堆栈 
Stack CreateStack() 
{
	S = (Stack)malloc(sizeof(struct DStack));
	S->Top1 = -1;
	S->Top2 = MaxSize;
	return S;
}

// 入栈 
void Push(Stack S, ElementType item, int Tag)  //Tag作为区分两个堆栈的标志，取值为1和2
{
	if (S->Top2 - S->Top1 == 1) 
	{  
		cout << "堆栈满" << endl;
		return;
	}
	if (Tag == 1)   //对第一个堆栈进行操作
	{
		S->Data[++(S->Top1)] = item;
	}
	else {  //对第二个堆栈进行操作
		S->Data[--(S->Top2)] = item;
	}
}

// 出栈
ElementType Pop(Stack S, int Tag) 
{
	if (Tag == 1)  //对第一个堆栈进行操作
	{
		if (S->Top1 == -1)  //堆栈1为空
		{
			cout << "堆栈1空" << endl;
			return NULL;
		}
		else
			return S->Data[(S->Top1)--];
	}

	if (Tag == 2)  //对第二个堆栈进行操作
	{
		if (S->Top2 == MaxSize)  //堆栈2为空
		{
			cout << "堆栈2空" << endl;
			return NULL;
		}
		else
			return S->Data[(S->Top2)++];
	}
}
int main() {
	S = CreateStack();

	cout << "1入栈1" << endl;
	Push(S, 1, 1);

	cout << "2入栈1" << endl;
	Push(S, 2, 1);

	cout << "3入栈1" << endl;
	Push(S, 3, 1);

	cout << "1入栈2" << endl;
	Push(S, 1, 2);

	cout << "2入栈2" << endl;
	Push(S, 2, 2);

	cout << "3入栈2" << endl;
	Push(S, 3, 2);

	cout << Pop(S,1) << "出栈1" << endl;

	cout << Pop(S,2) << "出栈2" << endl;

	system("pause");

	return 0;
}