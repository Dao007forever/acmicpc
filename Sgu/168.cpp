#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 1005;
int n, m;
short a[maxn][maxn], dp[maxn][maxn];

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			scanf("%d", &a[i][j]);
			dp[i][j] = a[i][j];
		}

	for (int i = n - 1; i >= 1; i--)
		dp[i][m] = min(dp[i][m], dp[i + 1][m]);
	for (int j = m - 1; j >= 1; j--) {
		for (int i = n; i >= 1; i--) {
			dp[i][j] = min(dp[i][j], dp[i][j + 1]);
			if (i > 1) dp[i][j] = min(dp[i][j], dp[i - 1][j + 1]);
			if (i < n) dp[i][j] = min(dp[i][j], dp[i + 1][j]);
		}
	}

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j < m; j++)
			printf("%d ", dp[i][j]);
		printf("%d\n", dp[i][m]);
	}
	return 0;
}
