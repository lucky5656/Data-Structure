#include<iostream>
using namespace std;

struct PolyNode {
	int coef;  //系数
	int expon;  //指数
	struct PolyNode *link;  //指向下一个节点的指针
};
typedef struct PolyNode *Polynomial;
Polynomial P1, P2;

Polynomial PolyAdd(Polynomial P1, Polynomial P2);
void Attach(int c, int e, Polynomial *pRear);
int Compare(int a, int b);
void PrintPoly(Polynomial P);

Polynomial PolyAdd(Polynomial P1, Polynomial P2)
{
	Polynomial front, rear, temp;
	int sum;
	rear = (Polynomial)malloc(sizeof(struct PolyNode));  //为方便表头插入，先产生一个临时空结点作为结果多项式链表头
	front = rear;  //由front记录结果多项式链表头结点
	while (P1 && P2)  //当两个多项式都有非零项待处理时
	{
		switch (Compare(P1->expon, P2->expon))
		{
		case 1:  //P1中的数据项指数较大
			Attach(P1->coef, P1->expon, &rear);
			P1 = P1->link;
			break;
		case -1:  //P2中的数据项指数较大
			Attach(P2->coef, P2->expon, &rear);
			P2 = P2->link;
			break;
		case 0:  //两数据项指数相等
			sum = P1->coef + P2->coef;
			if (sum)  //注意判断系数和是否为0
				Attach(sum, P1->expon, &rear);
			P1 = P1->link;
			P2 = P2->link;
			break;
		}
	}
	//将未处理完的另一个多项式的所有节点依次复制到结果多项式中去
	for (; P1; P1 = P1->link)  //P1不为空
		Attach(P1->coef, P1->expon, &rear);
	for (; P2; P2 = P2->link)  //P2不为空
		Attach(P2->coef, P2->expon, &rear);
	rear->link = NULL;
	temp = front;
	front = front->link;  //令front指向结果多项式第一个非零项
	free(temp);  //释放临时空表头结点
	return front;
}

int Compare(int a, int b) 
{
	if (a > b)
		return 1;
	else if (a < b) 
		return -1;
	else 
		return 0;
}

// 新增一个节点
void Attach(int c, int e, Polynomial *pRear)  //由于在本函数中需要改变当前结果表达式尾项指针的值，所以函数传递进来的是结点指针的地址，*pRear指向尾项
{
	Polynomial P;
	P = (Polynomial)malloc(sizeof(struct PolyNode));  //申请新结点
	P->coef = c;  //对新结点赋值
	P->expon = e;
	P->link = NULL;  
	//将P指向的新结点插入到当前结果表达式尾项的后面
	(*pRear)->link = P;  // 尾节点指向P
	*pRear = P;  //修改pRear指针指向的值
}

void PrintPoly(Polynomial P)
{
	Polynomial tmp = P;
	for (; tmp; tmp = tmp->link)
	{ 
		cout << tmp->coef << "  " << tmp->expon << "    ";
	}
	cout << endl;
}

int main()
{
	int P1Coef[5] = { 3, 4, -1, 2, -1 };
	int P1expon[5] = { 5, 4, 3, 1, 0 };
	int P2Coef[4] = { 2, 1, -7, 1 };
	int P2expon[4] = { 4, 3, 2, 1 };

	P1 = (Polynomial)malloc(sizeof(struct PolyNode));
	P2 = (Polynomial)malloc(sizeof(struct PolyNode));

	Polynomial P1Rear;
	P1Rear = P1;

	Polynomial P2Rear;
	P2Rear = P2;

	for (int i = 0; i < 5; ++i)
	{
		Attach(P1Coef[i], P1expon[i], &P1Rear); // 注意这里传的是地址！！！
	}
	P1 = P1->link; // 因为第一个节点没有存储数据，所以 P1 要往后挪一位

	for (int i = 0; i < 4; ++i)
	{
		Attach(P2Coef[i], P2expon[i], &P2Rear);
	}
	P2 = P2->link;

	Polynomial res = PolyAdd(P1, P2);

	cout << "P1：   ";
	PrintPoly(P1);
	cout << "P2：   ";
	PrintPoly(P2);
	cout << "P1+P2：";
	PrintPoly(res);

	system("pause");

	return 0;
}