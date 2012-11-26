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

const int MAXN = 1000 + 10;
const int inf = 1000000001;
const long long INF = (1LL) << 40;
int N, M, X, Y;
int Map[MAXN][MAXN], T[MAXN], C[MAXN], use[MAXN];
long long dis[MAXN], Left[MAXN];

void Init()
{
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= N; i++)
	for (int j = 1; j <= N; j++)
		if (i != j)
		{
			Map[i][j] = inf;
		}
	scanf("%d%d", &X, &Y);
	for (int i = 1; i <= M; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		if (w < Map[u][v])
			Map[u][v] = Map[v][u] = w;
	}
	for (int i = 1; i <= N; i++)
		scanf("%d%d", &T[i], &C[i]);
}

queue<int> Q;
void Work()
{
	for (int i = 1; i <= N; i++)
		dis[i] = INF;
	memset(use, 0, sizeof(use));
	dis[X] = 0;
	use[X] = true;
	Q.push(X);
	while (!Q.empty())
	{
		int v = Q.front();
		Q.pop();
		for (int i = 1; i <= N; i++)
		{
			if (Left[v] >= Map[v][i] && dis[v] < dis[i])
			{
				dis[i] = dis[v];
				Left[i] = Left[v] - Map[v][i];
				if (!use[i])
				{
					use[i] = true;
					Q.push(i);
				}
			}
			else if (T[v] >= Map[v][i] && dis[v] + C[v] < dis[i])
			{
				dis[i] = dis[v] + C[v];
				Left[i] = T[v] - Map[v][i];
				if (!use[i])
				{
					use[i] = true;
					Q.push(i);
				}
			}
		}
		use[v] = false;
	}
}

int main()
{
	freopen("a", "r", stdin);
	Init();
	Work();
	if (dis[Y] >= INF) dis[Y] = -1;
	cout << dis[Y] << endl;
	return 0;
}
