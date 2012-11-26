#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 505;
int n, K;
int cnt[maxn][maxn], dp[maxn][maxn];
int pre[maxn][maxn];
string s;

void output(int n, int k) {
	if (n == 0) return;
	output(pre[n][k], k - 1);
	if (pre[n][k] != 0) cout << "+";
	int l = pre[n][k], r = n - 1;
	int len = (r - l + 1) / 2;
	for (int i = 0; i < len; i++)
		if (s[l + i] != s[r - i]) s[l + i] = s[r - i];
	cout << s.substr(l, r - l + 1);
}

int main() {
	freopen("in.txt", "r", stdin);
	cin >> s >> K;
	n = s.size();
	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++) {
			int l = (j - i + 1) / 2;
			for (int k = 0; k < l; k++)
				if (s[i + k] != s[j - k])
					cnt[i + 1][j + 1]++;
		}

	memset(dp, -1, sizeof(dp));
	dp[0][0] = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < K; j++)
			if (dp[i][j] != -1) {
				for (int k = i + 1; k <= n; k++)
					if (dp[k][j + 1] == -1 || dp[i][j] + cnt[i + 1][k] < dp[k][j + 1]) {
						dp[k][j + 1] = dp[i][j] + cnt[i + 1][k];
						pre[k][j + 1] = i;
					}
			}
	int ret = -1, cur;
	for (int i = 0; i <= K; i++) {
		if (ret == -1 || dp[n][i] < ret) {
			ret = dp[n][i];
			cur = i;
		}
	}
	cout << ret << endl;
	output(n, cur);
	cout << endl;
	return 0;
}
