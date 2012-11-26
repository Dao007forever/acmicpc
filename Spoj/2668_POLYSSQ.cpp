#include <cstdio>
#include <algorithm>
using namespace std;

#define abs(x) ((x) > 0 ? x : -(x))

const int inf = 100000000;
struct Point
{
	int x, y;
}ps[55], cp[55];
int N, K;
int ans, cnt;
int dp[55][55][55];
int flag[55][55][55];

inline int cross(Point o, Point a, Point b)
{
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

inline bool cmp(const Point &a, const Point &b)
{
	return cross(cp[0], a, b) < 0;
}

inline void init()
{
	scanf("%d%d", &N, &K);
	for (int i = 1; i <= N; i++)
		scanf("%d%d", &ps[i].x, &ps[i].y);
}

inline int getArea(Point o, Point a, Point b)
{
	return abs(cross(o, a, b));
}

inline void solve()
{
	if (K < 3)
	{
		printf("0\n");
		return;
	}
	ans = inf;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			for (int k = 1; k <= K; k++)
				dp[i][j][k] = inf;
	for (int i = 1; i <= N; i++)
	{
		cnt = 0;
		cp[0] = ps[i];
		for (int j = 1; j <= N; j++)
			if (ps[j].x > ps[i].x || (ps[j].x == ps[i].x && ps[j].y > ps[i].y))
				cp[++cnt] = ps[j];
		if (cnt < 3) continue;
		sort(cp + 1, cp + cnt + 1, cmp);

		for (int j = 1; j <= cnt; j++)
		{
			dp[0][j][2] = 0;
			flag[0][j][2] = i;
		}
		for (int k = 2; k < K; k++)
		for (int u = 0; u <= cnt; u++)
		for (int v = u + 1; v <= cnt; v++)
		if (flag[u][v][k] == i)
		{
			for (int w = v + 1; w <= cnt; w++)
			if (cross(cp[u], cp[v], cp[w]) < 0 && cross(cp[v], cp[w], ps[i]) < 0)
			{
				int area = getArea(ps[i], cp[v], cp[w]);
				if (flag[v][w][k + 1] != i)
					dp[v][w][k + 1] = dp[u][v][k] + area;
				else if (dp[u][v][k] + area < dp[v][w][k + 1])
					dp[v][w][k + 1] = dp[u][v][k] + area;
				if (dp[v][w][k + 1] < ans) flag[v][w][k + 1] = i;
				else flag[v][w][k + 1] = -1;
			}
		}
		for (int u = 1; u <= cnt; u++)
			for (int v = u + 1; v <= cnt; v++)
			{
				ans = min(ans, dp[u][v][K]);
				if (ans == 0)
				{
					printf("%d %d %d\n", i, u, v);
				}
			}
	}
	if (ans == inf) ans = 0;
	printf("%d\n", ans / 2);
}

int main()
{
	freopen("in", "r", stdin);
	init();
	solve();
	return 0;
}
