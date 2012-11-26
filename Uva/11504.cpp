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

const int MAXN = 111111;
int N, M, scnt, cnt;
int st[MAXN], post[MAXN], tmpost[MAXN], id[MAXN], deg[MAXN];
vector<int> gra[MAXN], revgra[MAXN];

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
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		memset(st, 0, sizeof(st));
		memset(post, 0, sizeof(post));
		memset(tmpost, 0, sizeof(tmpost));
		memset(id, 0, sizeof(id));
		memset(deg, 0, sizeof(deg));
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= N; i++)
		{
			gra[i].clear();
			revgra[i].clear();
		}
		for (int i = 1; i <= M; i++)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			gra[u].push_back(v);
			revgra[v].push_back(u);
		}
		Tarjan();
		for (int u = 1; u <= N; u++)
			for (int i = 0; i < gra[u].size(); i++)
			{
				int v = gra[u][i];
				if (id[u] != id[v])
				{
					deg[id[v]]++;
				}
			}
		int ans = 0;
		for (int i = 1; i <= scnt; i++)
		if (!deg[i]) ans++;
		printf("%d\n", ans);
	}
	return 0;
}
