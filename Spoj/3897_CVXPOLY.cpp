#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define abs(x) ((x) > 0 ? x : -(x))

const int inf = 100000000;
const double eps = 1e-8;
const int mod = 1234567;
struct Point
{
	double x, y;
}ps[111], cp[111];
int N, K;
int ans, cnt;
int dp[111][111];

inline int sig(double d)
{
	return (d > eps) - (d < -eps);
}

inline double cross(Point o, Point a, Point b)
{
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

inline bool cmp(const Point &a, const Point &b)
{
	return sig(cross(cp[0], a, b)) < 0;
}

inline void init()
{
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%lf%lf", &ps[i].x, &ps[i].y);
}

inline void solve()
{
	ans = 0;
	for (int i = 1; i <= N; i++)
	{
		cnt = 0;
		cp[0] = ps[i];
		for (int j = 1; j <= N; j++)
			if (sig(ps[j].x - ps[i].x) > 0 || sig(ps[j].x - ps[i].x) == 0 && sig(ps[j].y - ps[i].y) > 0)
				cp[++cnt] = ps[j];
		sort(cp + 1, cp + cnt + 1, cmp);
		memset(dp, 0, sizeof(dp));
		for (int j = 1; j <= cnt; j++)
			dp[0][j] = 1;
		for (int j = 0; j < cnt; j++)
		for (int k = j + 1; k <= cnt; k++)
		if (dp[j][k])
			for (int l = k + 1; l <= cnt; l++)
				if (sig(cross(cp[j], cp[k], cp[l])) < 0) {
					dp[k][l] += dp[j][k];
					dp[k][l] %= mod;
				}
		for (int j = 0; j < cnt; j++)
		for (int k = j + 1; k <= cnt; k++)
		if (sig(cross(cp[j], cp[k], ps[i])) < 0) {
			ans += dp[j][k];
			ans %= mod;
		}
	}
	printf("%d\n", ans);
}

int main()
{
	freopen("in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		init();
		solve();
	}
	return 0;
}
