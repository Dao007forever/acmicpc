#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 405;
struct Point {
	double x, y;
}p[maxn];
int n;
double dp[maxn][maxn][2];

double dist(int i, int j) {
	Point A = p[i], B = p[j];
	double dx = A.x - B.x;
	double dy = A.y - B.y;
	return sqrt(dx * dx + dy * dy);
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lf%lf", &p[i].x, &p[i].y);
	for (int i = n + 1; i <= 2 * n; i++)
		p[i] = p[i - n];

	for (int i = 1; i <= 2 * n; i++) {
		dp[i][i][0] = dp[i][i][1] = 0.0;
	}

	for (int l = 2; l <= n; l++)
		for (int i = 1; i <= 2 * n - l + 1; i++) {
			int j = i + l - 1;
			dp[i][j][0] = min(dp[i + 1][j][0] + dist(i, i + 1), dp[i + 1][j][1] + dist(i, j));
			dp[i][j][1] = min(dp[i][j - 1][0] + dist(i, j), dp[i][j - 1][1] + dist(j, j - 1));
		}
	double ret = 1e12;
	for (int i = 1; i <= n; i++) {
		double tmp = min(dp[i][i + n - 1][0], dp[i][i + n - 1][1]);
		ret = min(ret, tmp);
	}

	printf("%.3lf\n", ret);
	return 0;
}
