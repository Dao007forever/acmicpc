#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int n, m;
int a[111][111], dp[1111], g[111], sum[111];

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	memset(dp, 0, sizeof(dp));
	for (int i = 1; i <= n; i++) {			
		memset(sum, 0, sizeof(sum));
		memset(g, 0, sizeof(g));
		scanf("%d", &a[i][0]);
		for (int j = 1; j <= a[i][0]; j++) {
			scanf("%d", &a[i][j]);
			sum[j] = sum[j - 1] + a[i][j];
		}
		
		for (int j = 1; j <= a[i][0]; j++)
			for (int k = 0; k <= j; k++)
				g[j] = max(g[j], sum[k] + sum[a[i][0]] - sum[a[i][0] - (j - k)]);
		for (int j = m; j > 0; j--)
			for (int k = 1; k <= a[i][0] && k <= j; k++)
				dp[j] = max(dp[j], dp[j - k] + g[k]);
	}
	printf("%d\n", dp[m]);
	return 0;
}
