#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 100000 + 5;
int N, T, W;
int a[111];
int dp[maxn], pre[maxn], h[maxn];
vector<int> ans;

void output(int m) {
	if (m == 0) return;
	ans.push_back(h[m]);
	output(pre[m]);
}

int main()
{
	freopen("in.txt", "r", stdin);
	cin >> T;
	cin >> N;
	W = 0;
	for (int i = 0; i < N; i++) {
		cin >> a[i];
		W += a[i];
	}
	W -= T;
	if (W < 0) {
		cout << 0 << endl;
		return 0;
	}

	dp[0] = 1;
	for (int i = 0; i < N; i++)
		for (int j = W; j >= a[i]; j--)
			if (dp[j - a[i]]) {
				if (dp[j] == 0) {
					pre[j] = j - a[i];
					h[j] = i;
				}
				dp[j] += dp[j - a[i]];
			}
	if (dp[W] == 0) {
		cout << 0 << endl;
	} else if (dp[W] > 1) {
		cout << -1 << endl;
	} else {
		output(W);
		//cout << ans.size() << endl;
		sort(ans.begin(), ans.end());
		for (int i = 0; i < ans.size(); i++)
			printf("%d ", ans[i] + 1);
	}
	return 0;
}
