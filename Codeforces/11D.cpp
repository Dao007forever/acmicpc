/*
 * 求一个无向图中环的个数
 * f(mask, i)表示当前状态为mask，在第i个节点的方案数，为了防止重复计数，在转移过程中需要记录开始的那个节点first，最后要找的就是求和所有的长度>=3且adj[first][last]=1的f（mask, last）
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

int n, m;
long long dp[20][1 << 20];
int adj[22][22];

int count(int mask) {
	int ret = 0;
	for (int i = 0; i < n; i++)
		if (mask & (1 << i)) ret++;
	return ret;
}

int first(int mask) {
	for (int i = 0; i < n; i++)
		if (mask & (1 << i)) return i;
}

long long DP(int first, int last, int cnt, int mask) {
	long long& ret = dp[last][mask];
	if (ret != -1) return ret;

	ret = 0;
	if (cnt >= 3 && adj[last][first]) {
		ret++;
	}
	for (int i = first + 1; i < n; i++) {
		if (adj[last][i] && (mask & (1 << i)) == 0) {
			ret += DP(first, i, cnt + 1, mask | (1 << i));
		}
	}
	return ret;
}

int main() {
//	freopen("in", "r", stdin);
	memset(adj, 0, sizeof(adj));
	cin >> n >> m;
	while (m--) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		adj[a][b] = adj[b][a] = 1;
	}
	memset(dp, -1, sizeof(dp));
	long long ret = 0;
	for (int i = 0; i < n; i++) {
		ret += DP(i, i, 1, 1 << i);
	}
	ret /= 2;
	cout << ret << endl;
	return 0;
}
