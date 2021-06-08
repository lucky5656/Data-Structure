#include<iostream>
using namespace std;

#define MAXTABLESIZE 100000   // 允许开辟的最大散列表长度
typedef int Index;  // 散列地址类型
typedef int ElementType;  // 关键词类型用整型

// 单链表的定义
typedef struct LNode *PtrToLNode;
struct LNode {   // 单链表 
	ElementType Data;
	PtrToLNode Next;
};
typedef PtrToLNode Position;
typedef PtrToLNode List;

typedef struct TblNode *HashTable;  // 散列表
struct TblNode {  // 散列表结点定义
	int TableSize;   // 表的最大长度 
	List Heads;  // 指向链表头结点的数组 
};

// 查找素数 
int NextPrime(int N) 
{
	int p = (N % 2) ? (N + 2) : (N + 1);   // 比 tablesize 大的奇数 
	int i;
	while (p <= MAXTABLESIZE) 
	{
		for (i = (int)sqrt(p); i > 2; i--)
			if (!(p%i))
				break;
		if (i == 2)  // 找到素数了 
			break;
		p += 2; // 下一个奇数
	}
	return p;
}

// 创建哈希表 
HashTable CreateTable(int TableSize) 
{
	HashTable H;
	H = (HashTable)malloc(sizeof(struct TblNode));
	H->TableSize = NextPrime(TableSize);
	H->Heads = (List)malloc(sizeof(struct TblNode) * H->TableSize);
	for (int i = 0; i < H->TableSize; i++)
		H->Heads[i].Next = NULL;  // 链表头：H->Heads[i] 是不存东西的 
	return H;
}

// 除留余数法哈希函数 
Index Hash(int TableSize, ElementType Key) 
{
	return  Key % TableSize;
}

// 查找
Position Find(HashTable H, ElementType Key) 
{
	Index pos = Hash(H->TableSize, Key);  // 初始散列位置
	Position P = H->Heads[pos].Next;  // 从该链表的第1个结点开始 
	while (P && P->Data != Key)  // 当未到表尾，并且Key未找到时
		P = P->Next;
	return P;  // 此时P或者指向找到的结点，或者为NULL
}

// 插入
bool Insert(HashTable H, ElementType Key) 
{
	Position P, NewCell;
	Index pos;

	P = Find(H, Key);
	if (!P)  // 关键词未找到，可以插入 
	{
		NewCell = (Position)malloc(sizeof(struct LNode));
		NewCell->Data = Key;
		pos = Hash(H->TableSize, Key);   // 初始散列表地址
		NewCell->Next = H->Heads[pos].Next;  // 将NewCell插入为H->Heads[Pos]链表的第1个结点
		H->Heads[pos].Next = NewCell;
		return true;
	}
	else  // 关键词已存在
	{
		cout << "键值已存在" << endl;
		return false;
	}
}

void Print(HashTable H) 
{
	for (int i = 0; i < H->TableSize; i++) 
	{
		cout << i;
		List p = H->Heads[i].Next;
		while (p) 
		{
			cout << " " << p->Data;
			p = p->Next;
		}
		cout << endl;
	}
}

void DestroyTable(HashTable H) 
{
	Position P, tmp;
	for (int i = 0; i < H->TableSize; i++)  // 释放每个链表的结点
	{
		P = H->Heads[i].Next;
		while (P)
		{
			tmp = P->Next;
			free(P);
			P = tmp;
		}
	}
	free(H->Heads);  // 释放头结点数组
	free(H);  // 释放散列表结点
}

int main() 
{
	HashTable H = CreateTable(9);
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) 
	{
		int tmp;
		cin >> tmp;
		Insert(H, tmp);
	}
	Print(H);
	DestroyTable(H);
	system("pause");
	return 0;
}