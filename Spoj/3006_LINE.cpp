#include <cstdio>
#include <cmath>
using namespace std;

const double eps = 1e-8;
struct Point
{
	double x, y;
};
struct Line
{
	Point A, B;
	void input()
	{
		scanf("%lf%lf%lf%lf", &A.x, &A.y, &B.x, &B.y);
	}
}line[15];
int N;
double dp[1 << 15][30];

double dist(Point a, Point b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

void init()
{
	for (int i = 0; i < N; i++)
		line[i].input();
}

void update(double &a, double b)
{
	if (b < a) a = b;
}

void solve()
{
	for (int i = 0; i < (1 << N); i++)
	for (int j = 0; j < 2 * N; j++)
		dp[i][j] = 1e99;
	for (int i = 0; i < N; i++)
		dp[1 << i][i] = dp[1 << i][N + i] = 0;

	for (int i = 0; i < (1 << N); i++)
	for (int j = 0; j < 2 * N; j++)
	if (dp[i][j] < 1e50)
	{
		Point tmp;
		if (j < N) tmp = line[j].A;
		else tmp = line[j - N].B;

		for (int k = 0; k < N; k++)
		if (!(i & (1 << k)))
		{
			update(dp[i | (1 << k)][k + N], dp[i][j] + dist(tmp, line[k].A));
			update(dp[i | (1 << k)][k], dp[i][j] + dist(tmp, line[k].B));
		}
	}
	double ans = 1e99;
	for (int i = 0; i < 2 * N; i++)
		update(ans, dp[(1 << N) - 1][i]);
	for (int i = 0; i < N; i++)
		ans += dist(line[i].A, line[i].B);
	printf("%.5lf\n", ans);
}

int main()
{
	freopen("in", "r", stdin);
	int cas = 1;
	while (scanf("%d", &N) && N)
	{
		printf("Case %d: ", cas++);
		init();
		solve();
	}
	return 0;
}
