#include <map>
#include <set>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <bitset>
#include <vector>
#include <cstdio>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct Node
{
	char num[55];
	int len;
	int res;
};
int A;
bool resflag[20000];
queue<Node> Q;

int main()
{
	freopen("a", "r", stdin);
	int t;
	scanf("%d", &t);
	while (t--)
	{
		scanf("%d", &A);
		memset(resflag, 0, sizeof(resflag));
		while (!Q.empty())
			Q.pop();
		Node temp, x;
		temp.res = 1;
		temp.len = 1;
		temp.num[0] = '1';
		Q.push(temp);
		bool find = false;
		while (!Q.empty())
		{
			temp = Q.front();
			Q.pop();
			if (temp.res % A == 0)
			{
				find = true;
				break;
			}
			//添加一个0
			for (int i = 0; i < temp.len; i++)
				x.num[i] = temp.num[i];
			//memcpy(x.num, temp.num, sizeof(temp.num));
			x.len = temp.len + 1;
			x.num[x.len - 1] = '0';
			//x.out = temp.out;
			//x.out += '0';
			x.res = temp.res * 10;
			x.res %= A;
			if (!resflag[x.res])
				Q.push(x);
			resflag[x.res] = true;
			//添加一个1
			x.num[x.len - 1] = '1';
			//x.out = temp.out;
			//x.out += '1';
			x.res = temp.res * 10 + 1;
			x.res %= A;
			if (!resflag[x.res])
				Q.push(x);
			resflag[x.res] = true;
		}
		if (find)
			for (int i = 0; i < temp.len; i++)
				printf("%c", temp.num[i]);
		printf("\n");
	}
	return 0;
}
