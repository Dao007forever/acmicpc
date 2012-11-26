#include <cstdio>
#include <iostream>
using namespace std;

const int mod = 1000000007;
int n, m, k;
long long dp[1111][1111], s[1111][1111], t[1111][1111];

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= 1001; i++)
		dp[i][1] = 1;

	for (int j = 2; j <= 1001; j++) {
		for (int i = 1; i <= 1001; i++) {
			s[i][j - 1] = (s[i - 1][j - 1] + dp[i][j - 1]) % mod;
			t[i][j - 1] = (t[i - 1][j - 1] + dp[i][j - 1] * i) % mod;
		} 
		for (int i = 2; i <= 1001; i++) {
			dp[i][j] = (s[i - 2][j - 1] * (i - 1) - t[i - 2][j - 1]) % mod;
			if (dp[i][j] < 0) dp[i][j] += mod;
		}
	}

	long long x = dp[n][k + 1], y = dp[m][k + 1];
	cout << (x * y) % mod << endl;
	return 0;
}
