#include <cstdio>
#include <cstring>

int n;
int dp[905][8105], pre[905][8105], cnt[10];

void No() {
	printf("No solution\n");
}

void Print(int sum, int sqsum) {
	if (sum == 0 && sqsum == 0) return;
	int k = pre[sum][sqsum];
	cnt[k]++;
	Print(sum - k, sqsum - k * k);
}

int main() {
	freopen("in.txt", "r", stdin);
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i <= 900; i++)
		for (int j = 0; j <= 8100; j++)
			pre[i][j] = 10;
	dp[0][0] = 0;
	for (int i = 0; i <= 900; i++)
		for (int j = 0; j <= 8100; j++)
			if (dp[i][j] != -1) {
				for (int k = 1; k < 10; k++)
					if (i + k <= 900 && j + k * k <= 8100) {
						if (dp[i + k][j + k * k] == -1 || dp[i][j] + 1 <= dp[i + k][j + k * k]) {
							dp[i + k][j + k * k] = dp[i][j] + 1;
							if (k < pre[i + k][j + k * k]) {
								pre[i + k][j + k * k] = k;
							}
						}
					}
			}
	int n;
	scanf("%d", &n);
	while (n--) {
		memset(cnt, 0, sizeof(cnt));
		int s1, s2;
		scanf("%d%d", &s1, &s2);
		if (s1 > 900 || s2 > 8100) {
			No();
			continue;
		}
		if (dp[s1][s2] == -1 || dp[s1][s2] > 100) {
			No();
			continue;
		}
		Print(s1, s2);
		for (int i = 1; i <= 9; i++) {
			for (int j = 0; j < cnt[i]; j++)
				printf("%d", i);
		}
		printf("\n");
	}
	return 0;
}
