#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
const int maxn = 105, DOWN = 25, MAXS = 8, INF = 0x3f3f3f3f;
int n, take, book[maxn], type[maxn], num[maxn];
int dp[maxn][MAXS][1 << MAXS];

void update(int &a, int up) {
	a = min(a, up);
}

int calNum(int set) {
	int ret = 0;
	for (; set; set >>= 1)
		ret += (set & 1);
	return ret;
}

int main() {
freopen("test.in", "r", stdin);
	for (int Case = 1; scanf("%d %d", &n, &take) && n + take; Case++) {
		for (int i = 1; i <= n; i++)
			scanf("%d", book + i);
		int cnt = 1, ALL = 0;
		type[1] = book[1] - DOWN;
		num[1] = 1;
		for (int i = 2; i <= n; i++)
			if (book[i] != book[i - 1]) {
				cnt++;
				type[cnt] = book[i] - DOWN;
				num[cnt] = 1;
			} else 
				num[cnt]++;
		int total = n;	//
		n = cnt;
		for (int i = 1; i <= n; i++)
			ALL |= (1 << type[i]);
		int upSet = 1 << MAXS;
		memset(dp, 63, sizeof(dp));
		for (int i = 1; i <= n; i++) {
			for (int j = total; j >= 0; j--)
			for (int last = MAXS - 1; last >= 0; last--)
			for (int set = 0; set < upSet; set++)
			if (dp[j][last][set] != INF) {
				update(dp[j + num[i]][type[i]][set | (1 << type[i])], dp[j][last][set] + (!(last == type[i])));
			}
			dp[num[i]][type[i]][(1 << type[i])] = 1;
		}
		int res = INF;
		for (int j = total - take; j <= total; j++)
		for (int last = 0; last < MAXS; last++)
		for (int set = 0; set < upSet; set++)
		if (dp[j][last][set] != INF)
			update(res, dp[j][last][set] + calNum(set ^ ALL));
		printf("Case %d: %d\n\n", Case, res);
	}
}
