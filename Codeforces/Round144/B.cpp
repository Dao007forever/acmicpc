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
#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

#define MAXN 105
const int mod = 1000000007;
int N, K;
LL M, cnt[MAXN], mul[MAXN][MAXN * MAXN];
LL dp[MAXN][MAXN * MAXN], comb[MAXN][MAXN];

void update(LL &a, LL b) {
	a = (a + b) % mod;
}

LL quickPow(LL a, LL p, int m) {
	LL ret = 1;
	while (p) {
		if (p & 1) ret = ret * a % m;
		if (p >>= 1) a = a * a % m;
	}
	return ret;
}

void init() {
	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= i; j++) {
			if (j == 0) comb[i][j] = 1;
			else comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % mod;
		}
}

int main(int argc, char const *argv[])
{
	cin >> N >> M >> K;
	for (int i = 1; i <= N; i++) {
		cnt[i] = (M / N);
		if (M % N >= i) cnt[i]++;
	}
	init();
	for (int d = 0; d <= N; d++)
		for (int r = 1; r <= N; r++)
			mul[d][r] = quickPow(comb[N][d], cnt[r], mod);

	memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	for (int i = 0; i < N; i++) {
		for (int k = 0, kk = min(K, i * N); k <= kk; k++)
			if (dp[i][k]) {
				for (int d = 0; d <= N && k + d <= K; d++) {
					update(dp[i + 1][k + d], dp[i][k] * mul[d][i + 1]);
				}
			}
	}
	cout << dp[N][K] << endl;
	return 0;
}