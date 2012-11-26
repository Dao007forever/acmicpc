#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int MAXN = 50000 + 10;
const int inf = 2000000000;
struct Edge
{
	int u , v , w;
}edge[MAXN];
int dis[MAXN * 2];
int N , a , b , c , pos , s , t;

void Bellman_ford()
{
	for (int i = 0 ; i <= t ; i++)
		dis[i] = -inf;
	dis[s] = 0;
	for (int i = 0 ; i < t - s ; i++)
	{
		int flag = 0;
		for (int j = 0 ; j < N ; j++)
		{
			if (dis[edge[j].u] != -inf && dis[edge[j].v] < dis[edge[j].u] + edge[j].w)
			{
				dis[edge[j].v] = dis[edge[j].u] + edge[j].w;
				flag = 1;
			}
		}
		for (int j = s ; j < t ; j++)
		{
			if (dis[j] != -inf && dis[j + 1] < dis[j])
			{
				dis[j + 1] = dis[j];
				flag = 1;
			}
		}
		for (int j = t ; j > s ; j--)
		{
			if (dis[j] != -inf && dis[j - 1] < dis[j] - 1)
			{
				dis[j - 1] = dis[j] - 1;
				flag = 1;
			}
		}
		if (!flag) break;
	}
}

int main()
{
//	freopen("a" , "r" , stdin);
	int Test;
	cin >> Test;
	while (Test--)
	{
		cin >> N;
		s = inf, t = -1;
		for (int i = 0 ; i < N ; i++)
		{
			scanf("%d%d%d" , &a , &b , &c);
			edge[i].u = a;
			s = min(s , a);
			edge[i].v = b + 1;
			t = max(t , b + 1);
			edge[i].w = c;
		}
		Bellman_ford();
		printf("%d\n" , dis[t]);
	}
	return 0;
}
