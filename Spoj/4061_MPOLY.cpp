#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

#define abs(x) ((x) > 0 ? x : -(x))

const int inf = 100000000;
const double eps = 1e-8;
struct Point
{
	double x, y;
}cp[111];
int N, K;
int ans, cnt;
int dp[111][111];

int sig(double d) {
	return (d > eps) - (d < -eps);
}

double cross(Point o, Point a, Point b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

bool cmp(const Point &a, const Point &b) {
	return sig(cross(cp[0], a, b)) < 0;
}

void init() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%lf%lf", &cp[i].x, &cp[i].y);
}

void solve() {
	ans = 0;
	sort(cp + 1, cp + N + 1, cmp);
	memset(dp, 0, sizeof(dp));
	for (int i = 1; i <= N; i++)
		dp[0][i] = 2;
	for (int i = 0; i < N; i++)
		for (int j = i + 1; j <= N; j++)
			if (dp[i][j]) {
				for (int k = j + 1; k <= N; k++)
					if (sig(cross(cp[i], cp[j], cp[k])) < 0)
						dp[j][k] = max(dp[j][k], dp[i][j] + 1);
			}
	for (int i = 0; i < N; i++)
		for (int j = i + 1; j <= N; j++)
			if (sig(cross(cp[i], cp[j], cp[0])) < 0)
				ans = max(ans, dp[i][j]);
	printf("%d\n", ans);
}

int main() {
	freopen("in", "r", stdin);
	init();
	solve();
	return 0;
}
