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

const int MAXN = 2010;
const long long inf = 1LL << 62;
struct Edge
{
	int v, next;
}edge[2000000];
int N, M, Q;
long long dis[111][111];
int T[MAXN], P[MAXN];
int cy[MAXN], mk[MAXN];
int Head[MAXN], num;

inline void addEdge(int u, int v)
{
	edge[num].v = v;
	edge[num].next = Head[u];
	Head[u] = num++;
}

inline int path(int u)
{
        for (int i = Head[u]; i != -1; i = edge[i].next)
        {
			int v = edge[i].v;
                if ((!mk[v]))
                {
                        mk[v] = 1;
                        if (!cy[v] || path(cy[v]))
                        {
                                cy[v] = u;
                                return 1;
                        }
                }
        }
        return 0;
}

inline int MaxMatch()
{
        int res = 0;
        memset(cy, 0, sizeof(cy));
        for (int i = 1; i <= Q; i++)
        {
            memset(mk, 0, sizeof(mk));
            res += path(i);
        }
        return res;
}

int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; cas <= Test; cas++)
	{
		memset(Head, -1, sizeof(Head));
		num = 0;
		printf("Case %d: ", cas);
		scanf("%d%d%d", &N, &M, &Q);
		
		memset(dis, 0x3f, sizeof(dis));
		for (int i = 1; i <= N; i++)
			dis[i][i] = 0;

		for (int i = 1; i <= M; i++)
		{
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			a++; b++;
			if (c < dis[a][b]) dis[a][b] = dis[b][a] = (long long)c;
		}
		for (int i = 1; i <= Q; i++)
		{
			scanf("%d%d", &P[i], &T[i]);
			P[i]++;
		}
		for (int k = 1; k <= N; k++)
		for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
		if (i != j && j != k && i != k)
			if (dis[i][k] + dis[k][j] < dis[i][j])
				dis[i][j] = dis[i][k] + dis[k][j];

		for (int i = 1; i <= Q; i++)
		for (int j = 1; j <= Q; j++)
		if (i != j)
		{
			int u = P[i], v = P[j];
			if (T[j] - T[i] >= dis[u][v]) addEdge(i, j);
		}
		int ans = Q - MaxMatch();
		printf("%d\n", ans - 1);
	}
	return 0;
}
