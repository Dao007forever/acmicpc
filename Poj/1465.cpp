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
	string out;
	int res;
};
int N, A;
bool FLAG[10];
bool resflag[5000];

int main()
{
	freopen("a", "r", stdin);
	queue<Node> Q;
	int t;
	Node temp, x;
	while (scanf("%d", &A) != EOF)
	{
		if (A == 0)
		{
			scanf("%d", &N);
			for (int i = 0; i < N; i++)
				scanf("%d", &t);
			printf("0\n");
			continue;
		}
		for (int i = 0; i < A; i++)
			resflag[i] = false;
		bool find = false;
		for (int i = 0; i < 10; i++)
			FLAG[i] = false;
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
		{
			scanf("%d", &t);
			FLAG[t] = true;
		}
		for (int i = 1; i < 10; i++)
		{
			temp.out = '0' + i;
			temp.res = i % A;
			if (FLAG[i])
				Q.push(temp);
		}
		while (!Q.empty())
		{
			temp = Q.front();
			Q.pop();
			if (temp.res % A == 0)
			{
				find = true;
				break;
			}
			for (int i = 0; i < 10; i++)
			{
				if (FLAG[i])
				{
					x.out = temp.out;
					x.out += char(i + '0');
					x.res = temp.res * 10 + i;
					x.res %= A;
					if (!resflag[x.res])
						Q.push(x);
					resflag[x.res] = true;
				}
			}
		}
		if (find) cout << temp.out << endl;
		else cout << 0 << endl;
		while (!Q.empty())
			Q.pop();
	}
	return 0;
}
