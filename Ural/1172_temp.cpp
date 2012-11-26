#include <cstdio>

int n;
int dp[111][5][33][33];

int main() {
	scanf("%d", &n);
	dp[1][0][0][0] = 1;
	for (int i = 2; i <= 3 * n; i++)
		for (int s = 0; s < 3; s++)
			for (int j = 0; j <= n; j++)
				for (int k = 0; k <= n; k++) {
					if (s == 0) {
						dp[i][0][j][k] = dp[i - 1][1][j][k] * j + dp[i - 1][2][j][k] * k;
					}
					if (s == 1 && j) {
						dp[i][1][j][k] = dp[i - 1][2][j - 1][k] * k;
						if (i - j - k > 0)
							dp[i][1][j][k] += dp[i - 1][0][j - 1][k] * (i - j - k);
					}
					if (s == 2 && k) {
						dp[i][2][j][k] = dp[i - 1][1][j][k - 1] * j;
						if (i - j - k > 0)
							dp[i][2][j][k] += dp[i - 1][0][j][k - 1] * (i - j - k);
					}
				}
	int ret = dp[3 * n][1][n][n];
	printf("%d\n", ret);
	return 0;
}
