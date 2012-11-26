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
const int MAXM = 500000 + 10;
int T, N, M, S;
int tot;
struct Edge
{
	int v, next;
}edge[MAXM];
int Head[MAXN], col[MAXN];

void AddEdge(int u, int v)
{
	edge[tot].v = v;
	edge[tot].next = Head[u];
	Head[u] = tot++;
}

bool BFS(int s)
{
	bool flag = false;
	int cnt = 1;
	queue<int> Q;
	Q.push(s);
	col[s] = 1;
	while (!Q.empty())
	{
		int p = Q.front();
		Q.pop();
		for (int i = Head[p]; i != -1; i = edge[i].next)
		{
			if (col[edge[i].v] == col[p])
			{
				flag = true;
				continue;
			}
			if (col[edge[i].v] == -1)
			{
				col[edge[i].v] = col[p] ^ 1;
				cnt++;
				Q.push(edge[i].v);
			}
		}
	}
	if (cnt == N && flag) return true;
	return false;
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++)
	{
		memset(Head, -1, sizeof(Head));
		memset(col, -1, sizeof(col));
		printf("Case %d: ", cas);
		scanf("%d%d%d", &N, &M, &S);
		tot = 1;
		for (int i = 1; i <= M; i++)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			AddEdge(u, v);
			AddEdge(v, u);
		}
		if (BFS(S))
			printf("YES\n");
		else printf("NO\n");
	}
}
