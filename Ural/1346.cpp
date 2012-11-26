#include <cstdio>
#include <iostream>
using namespace std;

const int maxn = 100000 + 5;
const int inf = 1000000000;
int dp[maxn][2];
int a[maxn];
int n, A, B;

int main()
{
	freopen("in.txt", "r", stdin);
	cin >> A >> B;
	n = 0;
	for (int i = A; i <= B; i++) {
		int x;
		cin >> x;
		if (n == 0 || x != a[n - 1])
			a[n++] = x;
	}
	for (int i = 0; i < n; i++)
		dp[i][0] = dp[i][1] = inf;
	dp[0][0] = dp[0][1] = 1;
	for (int i = 1; i < n; i++) {
		if (a[i] < a[i - 1]) {
			dp[i][0] = dp[i - 1][0];
			dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + 1;
		} else {
			dp[i][1] = dp[i - 1][1];
			dp[i][0] = min(dp[i - 1][0], dp[i - 1][1]) + 1;
		}
	}
	int ret = min(dp[n - 1][0], dp[n - 1][1]);
	cout << ret << endl;
	return 0;
}
