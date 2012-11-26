/*
 * Author : Yang Zhang
 */
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
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

#define MAXN 100005
int n;
int num[MAXN], dp[MAXN], last[MAXN], pre[MAXN];

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &num[i]);
	memset(last, -1, sizeof(last));
	dp[0] = 1;
	pre[0] = -1;
	last[num[0]] = 0;
	for (int i = 1; i < n; i++) {
		dp[i] = dp[i - 1] + 1;
		pre[i] = i - 1;
		if (last[num[i]] != -1) {
			int k = last[num[i]];
			if (dp[k] < dp[i]) {
				dp[i] = dp[k];
				pre[i] = pre[k];
			}
		}
		last[num[i]] = i;
	}
	vector<int> ans;
	for (int i = n - 1; i != -1; i = pre[i])
		ans.PB(num[i]);
	reverse(ans.begin(), ans.end());
	for (int i = 0; i < ans.size(); i++)
		printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
	return 0;
}
