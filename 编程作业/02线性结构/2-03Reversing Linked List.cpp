#include <iostream>
#include<iomanip>
using namespace std;
#define MAXSIZE 100005

typedef int ElementType;
typedef struct node {
	ElementType data;
	ElementType next;
} Node;

//反转链表函数，每K个结点，反转一下 
int reverList(Node list[], int K, int head, int N)
{
	int flag = 1;
	int last_head;	//用于记录上一次反转后，子链表的最后结点地址
					//待与下一次反转的子链表的头部相连 
	int rev_head = head;//下一次待反转子链表的头结点地址 
	int mid_head = head;//反转过程中的中间结点地址 
	int mid_next;		//反转过程中的中间结点地址 

	while (N - K >= 0)//当剩余结点不够K个时，则不再反转 
	{
		N -= K;

		//反转子链表 
		for (int i = 0; i < K - 1; i++) 
		{
			mid_next = list[rev_head].next;
			list[rev_head].next = list[mid_next].next;
			list[mid_next].next = mid_head;
			mid_head = mid_next;
		}//反转子链表 

		//从第二次开始，需要把这次反转后的子链表的头结点连接到上一段的尾部 
		if (flag == 0) 
{
			list[last_head].next = mid_head;
		}

		//记录第一次反转后的头结点，作为最终List的头结点并返回 
		if (flag) 
		{
			head = mid_head;
			flag = 0;
		}

		last_head = rev_head;
		rev_head = list[rev_head].next;//下次开始的头结点地址 
		mid_head = rev_head;
	}
	return head;
}

void printList(Node list[], int head)
{
	int next = head;
	while (list[next].next != -1) 
	{
		cout << setw(5) << setfill('0') << next << " " << list[next].data << " " << setw(5) << setfill('0') << list[next].next << endl;
		next = list[next].next;
	}
	cout << setw(5) << setfill('0') << next << " " << list[next].data << " " << list[next].next << endl;
}

int main()
{
	int Head, N, K;  //Head为第一个结点的地址,N为结点的总数，K为要反转的子列表的长度
	cin >> Head >> N >> K;
	Node list[MAXSIZE];
	int i, Address, Data, Next;  //Address是结点的位置，Data是一个整数，Next是下一个结点的位置
	for (i = 0; i < N; i++) 
	{
		cin >> Address >> Data >> Next;
		list[Address].data = Data;
		list[Address].next = Next;
	}
	int next = Head;
	int num = 1;//所给数据结点并不都是链表中的结点，用于计数真正的结点个数 
	while (list[next].next != -1) {
		num++;
		next = list[next].next;
	}
	if (K > 1)	//如果是1，则不需要反转，原序输出 
		Head = reverList(list, K, Head, num);
	printList(list, Head);

	system("pause");
	return 0;
}