#include<iostream> 
using namespace std;

typedef struct PolyNode {
	int coef;//系数 
	int exp;//指数 
	struct PolyNode *next;
} *Polynomial;

Polynomial read(Polynomial P);
void print(Polynomial P);
Polynomial getMuti(Polynomial P1, Polynomial P2);
Polynomial getAdd(Polynomial P1, Polynomial P2);

Polynomial read(Polynomial P) 
{
	Polynomial s = NULL, temp;
	P = (struct PolyNode*)malloc(sizeof(struct PolyNode));
	temp = P;
	int n, COEF, EXP;
	cout << "多项式的项数：";
	cin >> n;
	cout << "多项式每项对应的系数和指数：";
	for (int i = 0; i < n; i++) 
	{
		cin >> COEF >> EXP;
		if (COEF != 0) 
		{
			s = (struct PolyNode *)malloc(sizeof(struct PolyNode));
			s->coef = COEF; 
			s->exp = EXP;
			P->next = s;
			P = s;
		}
	}
	P->next = NULL;
	return temp;
}


void print(Polynomial P) 
{
	int num = 0, temp = 0;  //temp用于统计P里面有多少个元素，num 用于统计有多少个系数为0的数 
	Polynomial val = P;
	while (val->next) 
	{
		val = val->next;
		temp++;
	}
	if (P->next != NULL) 
	{
		while (P->next) 
		{
			if (P->next->coef != 0) 
			{
				cout << P->next->coef << " " << P->next->exp;
				Polynomial val = P->next;
				while (val->next&&val->next->coef == 0) 
				{
					val = val->next;
				}
				if (val->next == NULL)
					cout << endl;
				else
					cout << " ";
			}
			else
				num++;
			P = P->next;
		}
		if (num == temp)
			cout << 0 << " " << 0 << endl;
	}
	else
		cout << 0 << " " << 0 << endl;
}


Polynomial getAdd(Polynomial P1, Polynomial P2) 
{
	Polynomial P, temp = NULL, s = NULL;
	P = (struct PolyNode *)malloc(sizeof(struct PolyNode));
	temp = P;

	while (P1->next&&P2->next) 
	{
		if (P1->next->exp > P2->next->exp) 
		{
			s = (struct PolyNode *)malloc(sizeof(struct PolyNode));
			s->coef = P1->next->coef;
			s->exp = P1->next->exp;
			P->next = s;
			P = s;
			P1 = P1->next;
		}
		else if (P1->next->exp < P2->next->exp) 
		{
			s = (struct PolyNode *)malloc(sizeof(struct PolyNode));
			s->coef = P2->next->coef;
			s->exp = P2->next->exp;
			P->next = s;
			P = s;
			P2 = P2->next;
		}
		else 
		{
			s = (struct PolyNode *)malloc(sizeof(struct PolyNode));
			s->coef = P2->next->coef + P1->next->coef;
			s->exp = P2->next->exp;
			P->next = s;
			P = s;
			P1 = P1->next;
			P2 = P2->next;
		}
	}
	if (P1->next)
		P->next = P1->next;
	else
		P->next = P2->next;
	return temp;
}


Polynomial getMuti(Polynomial P1, Polynomial P2) {
	/*
	在这里我们采用的是：逐项插入。
	1，先拿出P2的第一项，让它与P1的每一项相乘，从而得到P
	2，再拿出P2的第二项，让它与P1的每一项相乘，然后每乘一项，就将其插入到P中
	3，依次重复上面的步骤，最终得到P，将其打印出来
	*/
	Polynomial P, temp = NULL, s = NULL;
	P = (struct PolyNode *)malloc(sizeof(struct PolyNode));
	temp = P;
	Polynomial Pa = P1;

	//拿出P2的第一项，让它与P1的每一项相乘,从而得到P
	while (Pa->next) {
		s = (struct PolyNode *)malloc(sizeof(struct PolyNode));
		s->coef = Pa->next->coef * P2->next->coef;  //P1的每一项与P2的第一项的系数相乘
		s->exp = Pa->next->exp + P2->next->exp;  //P1的每一项与P2的第一项的指数相加
		P->next = s;
		P = s;
		Pa = Pa->next;
	}
	P->next = NULL;
	P = temp;
	Polynomial Pb = P2->next;
	while (Pb&&Pb->next) 
	{
		Pa = P1;
		while (Pa->next) 
		{
			s = (struct PolyNode *)malloc(sizeof(struct PolyNode));
			s->coef = Pa->next->coef * Pb->next->coef;
			s->exp = Pa->next->exp + Pb->next->exp;
			while (P->next) 
			{
				if (s->exp > P->next->exp) 
				{
					Polynomial val = P->next;
					P->next = s;
					s->next = val;
					break;
				}
				else if (s->exp == P->next->exp)
				{
					P->next->coef += s->coef;
					break;
				}
				P = P->next;
			}
			if (P->next == NULL) 
			{
				P->next = s;
				s->next = NULL;
			}
			P = temp;
			Pa = Pa->next;
		}
		Pb = Pb->next;
	}
	return temp;
}

int main() 
{
	Polynomial P1 = NULL;
	Polynomial P2 = NULL;
	Polynomial P = NULL;
	cout << "P1：" << endl;
	P1 = read(P1);
	cout << "P2：" << endl;
	P2 = read(P2);

	cout << "P1*P2：";
	P = getMuti(P1, P2);
	print(P);

	cout << "P1+P2：";
	P = getAdd(P1, P2);
	print(P);

	system("pause");
	return 0;
}