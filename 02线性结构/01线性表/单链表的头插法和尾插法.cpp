#include<iostream>
using namespace std;

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
	ElementType Data;
	PtrToNode   Next;
};
typedef PtrToNode List;

List HeadCreatList() //头插法建立链表
{
	List L = (List)malloc(sizeof(PtrToNode));   //初始化空表，申请一个头结点
	L->Next = NULL;        //头指针为空
	for (int i = 0; i < 2; i++) 
	{
		List p = (List)malloc(sizeof(struct Node));  //p指向新申请的结点
		cout << "输入要插入的第" << i + 1 << "个元素：";
		cin >> p->Data;
		p->Next = L->Next;
		L->Next = p;
	}
	return L;
}

List TailCreatList() //尾插法建立链表
{
	List L = (List)malloc(sizeof(PtrToNode));   //初始化空表，申请一个头结点
	L->Next = NULL;        //头指针为空
	List last = L;     //last为指向尾结点的指针
	for (int i = 0; i < 2; i++)
	{
		List p = (List)malloc(sizeof(struct Node));  //p指向新申请的结点
		cout << "输入要插入的第" << i + 1 << "个元素：";
		cin >> p->Data;
		last->Next = p;
		last = p;  //last指向尾结点
	}
	last->Next = NULL;

	return L;
}

void Print(List L)
{
	if (L->Next)
	{
		List p = L;
		while (p->Next)
		{
			p = p->Next;
			cout << p->Data << " ";
		}
	}
	else
	{
		cout << "NULL";  //空链表将输出NULL 
	}
	cout << endl;
}

int main()
{
	//头插法
	cout << "头插法建立链表：" << endl;
	List L1 = HeadCreatList();
	cout << "L1：";
	Print(L1);

	//尾插法
	cout << "尾插法建立链表：" << endl;
	List L2 = TailCreatList();
	cout << "L2：";
	Print(L2);

	system("pause");

	return 0;
}