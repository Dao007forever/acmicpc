#include <cstdio>
#include <cstring>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const LL mod = 1000000007;
const int maxn = 100005;
int n, K, a[maxn], cnt[maxn], m;
map<int, int>mp;

bool isLucky(int x) {
	while (x) {
		int y = x % 10;
		if (y != 4 && y != 7) return false;
		x /= 10;
	}
	return true;
}

LL dp[1050][1050], h[maxn], r[maxn];

LL Pow(LL x, LL ct) {
	LL ret = 1;
	while (ct) {
		if (ct & 1) ret = ret * x % mod;
		x = x * x % mod;
		ct /= 2;
	}
	return ret;
}

LL C(int n, int m) {
	return h[n] * r[m] % mod * r[n - m] % mod;
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d%d", &n, &K);
	mp.clear();
	m = 0;
	int N = n;
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		if (isLucky(a[i])) {
			N--;
			if (mp.find(a[i]) == mp.end()) {
				cnt[m] = 1;
				mp[a[i]] = m++;
			}
			else cnt[mp[a[i]]]++;
		}
	}

	dp[0][0] = 1;
	for (int i = 0; i < m; i++)
		for (int j = 0; j <= m; j++)
			if (dp[i][j]) {
				dp[i + 1][j] += dp[i][j];
				dp[i + 1][j] %= mod;
				dp[i + 1][j + 1] += dp[i][j] * cnt[i] % mod;
				dp[i + 1][j + 1] %= mod;
			}

	h[0] = r[0] = h[1] = r[1] = 1;
	for (int i = 2; i < maxn; i++) {
		h[i] = h[i - 1] * i % mod;
		r[i] = Pow(h[i], mod - 2);
	}

	LL ret = 0;
	for (int i = 0; i <= min(m, K); i++) {
		if (N < K - i) continue;
		LL tmp = C(N, K - i) * dp[m][i] % mod;
		ret = (ret + tmp) % mod;
	}

	cout << ret << endl;
	return 0;
}
