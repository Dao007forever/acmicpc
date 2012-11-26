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

vector<int> v[222];
queue<int> Q;
int N, M;
int vis[222], num[3], col[222];

int BFS(int u)
{
	col[u] = 1;
	vis[u] = 1;
	Q.push(u);
	while (!Q.empty())
	{
		int k = Q.front();
		Q.pop();
		num[col[k]]++;
		int c = 1;
		if (col[k] == 1) c = 2;
		for (int i = 0; i < v[k].size(); i++)
		{
			if (!vis[v[k][i]])
			{
				vis[v[k][i]] = 1;
				col[v[k][i]] = c;
				Q.push(v[k][i]);
			}
			else if (col[v[k][i]] == col[k]) return -1;
		}
	}
	return 1;
}

void solve()
{
	int ans = 0;
	for (int i = 0; i < N; i++)
	if (!vis[i])
	{
		num[1] = num[2] = 0;
		int tmp = BFS(i);
		if (tmp < 0)
		{
			cout << tmp << endl;
			while (!Q.empty())
				Q.pop();
			return;
		}
		int Min = min(num[1], num[2]);
		if (!Min) Min = 1;
		ans += Min;
	}
	cout << ans << endl;
}

void free()
{
	for (int i = 0; i < N; i++)
	{
		v[i].clear();
		vis[i] = 0;
		col[i] = 0;
	}
	num[1] = num[2] = 0;
}

int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= M; i++)
		{
			int a, b;
			scanf("%d%d", &a, &b);
			v[a].push_back(b);
			v[b].push_back(a);
		}
		solve();
		free();
	}
	return 0;
}
