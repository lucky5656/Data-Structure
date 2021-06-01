#include<iostream>
using namespace std;

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
	ElementType Data;
	PtrToNode   Next;
};
typedef PtrToNode List;

List Read();
void Print(List L);  //空链表将输出NULL 
List Merge(List L1, List L2);

int main()
{
	List L1, L2, L;
	L1 = Read();
	L2 = Read();
	L = Merge(L1, L2);
	Print(L);
	Print(L1);
	Print(L2);
	system("pause");
	return 0;
}

List Read()
{
	List L = (List)malloc(sizeof(PtrToNode));   //申请一个头结点
	L->Next = NULL;        //头指针为空
	int n;
	cin >> n;
	if (n)    //当n不是0时
	{
		List last = L;     //last为指向尾结点的指针
		for (int i = 0; i < n; i++)
		{
			List p = (List)malloc(sizeof(struct Node));
			cin >> p->Data;    //尾插法
			last->Next = p;
			last = p;
		}
		last->Next = NULL;
	}
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

List Merge(List L1, List L2)
{
	List pa, pb, pc;
	List L = (List)malloc(sizeof(struct Node));
	pa = L1->Next;
	pb = L2->Next;
	pc = L;
	while (pa && pb)
	{
		if (pa->Data <= pb->Data)
		{
			pc->Next = pa;
			pc = pa;
			pa = pa->Next;
		}
		else
		{
			pc->Next = pb;
			pc = pb;
			pb = pb->Next;
		}
	}
	pc->Next = pa ? pa : pb;  //如果pa不为空，pc->Next = pa，否则pc->Next = pb
	L1->Next = NULL;
	L2->Next = NULL;
	return L;
}