#include<iostream>
using namespace std;
#include<map>
#include<string>

int main() 
{
	int N;
	char command;
	string qq;
	string ps;
	map<string, string> m;
	cin >> N;
	for (int i = 0; i < N; i++) 
	{
		getchar();
		cin >> command >> qq >> ps;
		if (command == 'N')     // 新用户
		{  
			if (m.find(qq) != m.end())    // qq号已经存在(map容器查找的key若存在，返回该键的元素的迭代器；若不存在，返回m.end()) 
				cout << "ERROR: Exist";
			else  // 注册成功
			{     
				cout << "New: OK";
				m[qq] = ps;
			}
		}
		else if (command == 'L')   // 老用户 
		{
			if (m.find(qq) == m.end())  // 没找到 
				cout << "ERROR: Not Exist";
			else if (m[qq] == ps)   // 密码正确 
				cout << "Login: OK";
			else
				cout << "ERROR: Wrong PW";
		}
		cout << endl;
	}
	system("pause");
	return 0;
}
