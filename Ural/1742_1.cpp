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

const int MAXN = 100000 + 10;
int N, cnt, scnt;
int id[MAXN], post[MAXN], tmpost[MAXN], st[MAXN];
vector<int> gra[MAXN], revgra[MAXN], g[MAXN];

void dfs(vector<int> g[], int x)
{
	stack<int> S;
	int i;
	S.push(x);
	while (!S.empty())
	{
		int top = S.top();
		if (id[top] == -1)
			id[top] = scnt;
		int tt = g[top].size();
		if (st[top] == tt)
		{
			post[++cnt] = top;
			S.pop();
		}
		else
		{
			for (int i = st[top]; i < tt; i++)
			{
				st[top] = i + 1;
				if (id[g[top][i]] == -1)
				{
					S.push(g[top][i]);
					break;
				}
			}
		}
	}
}

void Tarjan()
{
	scnt = cnt = 0;
	for (int i = 1; i <= N; i++)
	{
		id[i] = -1;
	}
	for (int i = 1; i <= N; i++)
		if (id[i] == -1)
			dfs(revgra, i);
	for (int i = 1; i <= N; i++)
	{
		tmpost[i] = post[i];
		id[i] = -1;
	}
	cnt = scnt = 0;
	memset(st, 0, sizeof(st));
	for (int i = N; i > 0; i--)
	{
		if (id[tmpost[i]] == -1)
		{
			++scnt;
			dfs(gra, tmpost[i]);
		}
	}
}

int main()
{
	freopen("a", "r", stdin);
	set<int> S;
	cin >> N;
	for (int i = 1; i <= N; i++)
	{
		int x;
		cin >> x;
		if (i != x)
		{
			gra[i].push_back(x);
			revgra[x].push_back(i);
		}
	}
	Tarjan();
	for (int i = 1; i <= N; i++)
		if (gra[i].size() > 0 && id[i] != id[gra[i][0]])
			S.insert(id[gra[i][0]]);
	cout << scnt - S.size() << " " << scnt << endl;
	return 0;
}
