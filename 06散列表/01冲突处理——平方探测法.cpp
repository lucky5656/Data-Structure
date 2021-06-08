#include<iostream>
using namespace std;

#define MAXTABLESIZE 100000   // 允许开辟的最大散列表长度 
typedef int Index;  // 散列地址类型
typedef int ElementType;  // 关键词类型用整型
typedef Index Position;  // 数据所在位置与散列地址是同一类型

// 散列单元状态类型，分别对应：有合法元素、空单元、有已删除元素
typedef enum {Legitimate, Empty, Deleted} EntryType;  // 定义单元状态类型 

typedef struct HashEntry Cell;  // 定义散列表单元类型
struct HashEntry {   //  哈希表存值单元 
	ElementType Data;  // 存放元素
	EntryType Info;  // 单元状态	
};

typedef struct HashTbl *HashTable;  // 散列表类型
struct HashTbl {  // 哈希表结构体 
	int TableSize;   // 表的最大长度 
	Cell *Cells;   // 存放散列单元数据的数组
};

int NextPrime(int N);  // 查找素数 
HashTable CreateTable(int TableSize); // 创建哈希表 
Index Hash(int Key, int TableSize);   // 哈希函数 

// 查找素数 
int NextPrime(int N)  // 返回大于N且不超过MAXTABLESIZE的最小素数
{
	int p = (N % 2) ? N + 2 : N + 1;  // 从大于 N 的下个奇数开始
	int i;

	while (p <= MAXTABLESIZE) 
	{
		for (i = (int)sqrt(p); i > 2; i--)
			if (!(p%i))  // p 不是素数 
				break;
		if (i == 2)  // for正常结束，说明p是素数
			break;
		p += 2;  // 继续试探下个奇数 
	}
	return p;
}

// 创建哈希表 
HashTable CreateTable(int TableSize) 
{
	HashTable H;
	H = (HashTable)malloc(sizeof(struct HashTbl));
	H->TableSize = NextPrime(TableSize);  // 保证散列表最大长度是素数 
	H->Cells = (Cell *)malloc(sizeof(Cell)*H->TableSize);  // 初始化单元数组 
	for (int i = 0; i < H->TableSize; i++)  // 初始化单元数组状态为“空单元”
		H->Cells[i].Info = Empty;
	return H;
}

// 平方探测查找 
Position Find(HashTable H, ElementType Key) 
{
	Position CurrentPos, NewPos;
	int CNum = 0;   // 记录冲突次数
	CurrentPos = NewPos = Hash(Key, H->TableSize);  // 初始散列位置
 
	while (H->Cells[NewPos].Info != Empty && H->Cells[NewPos].Data != Key) // 当该位置的单元非空，并且不是要找的元素时，发生冲突
	{
		// 统计1次冲突，并判断奇偶次
		if (++CNum % 2) { // 冲突奇数次发生 
			NewPos = CurrentPos + (CNum + 1) / 2 * (CNum + 1) / 2;  // 增量为+[(CNum+1)/2]^2
			while (H->TableSize <= NewPos)  // 如果越界，一直减直到再次进入边界
			{
				NewPos -= H->TableSize;  // 调整为合法地址
			}
		}
		else   // 冲突偶数次发生
		{  
			NewPos = CurrentPos - CNum / 2 * CNum / 2;  // 增量为-(CNum/2)^2 
			while (NewPos < 0)  // 如果越界，一直加直到再次进入边界
			{
				NewPos += H->TableSize;  // 调整为合法地址
			}
		}
	}
	return NewPos;  // 此时NewPos或者是Key的位置，或者是一个空单元的位置（表示找不到）
}

// 插入
bool Insert(HashTable H, ElementType Key, int i) 
{
	Position Pos = Find(H, Key);  // 先检查Key是否已经存在
	if (H->Cells[Pos].Info != Legitimate)  // 如果这个单元没有被占，说明Key可以插入在此 
	{
		H->Cells[Pos].Info = Legitimate;
		H->Cells[Pos].Data = Key;
		return true;
	}
	else 
	{
		cout << "键值已存在" << endl;
		return false;
	}
}

// 除留余数法哈希函数 
Index Hash(int Key, int TableSize) 
{
	return Key % TableSize;
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
		Insert(H, tmp, i);
	}
	for (int i = 0; i < H->TableSize; i++)
		cout << i << " " << H->Cells[i].Data << endl;
	system("pause");
	return 0;
}