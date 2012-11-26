#include <map>
#include <set>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <bitset>
#include <vector>
#include <cstdio>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int N, S;
double dp[55][55];

int main() {
	freopen("in", "r", stdin);
	while (scanf("%d%d", &N, &S) != EOF) {
		if (S > N) {
			printf("100.00000\n");
			continue;
		}
		if (S == 0) {
			printf("0.00000\n");
			continue;
		}
		memset(dp, 0, sizeof(dp));
		dp[0][0] = 1.0;
		for (int i = 1; i <= N; i++)
			for (int j = 0; j <= S; j++) {
				if (j == 0) dp[i][j] = dp[i - 1][j] * 2.0;
				else dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j] * 2.0;
			}
		double sum = 0.0;
		for (int i = 0; i <= S; i++)
			sum += dp[N][i];
		double ret = 1.0 - dp[N][S] / sum;
		printf("%.5lf\n", ret * 100);
	}
	return 0;
}
