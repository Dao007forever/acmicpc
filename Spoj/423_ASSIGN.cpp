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

int n;
int adj[22][22], cnt[1 << 20];
long long dp[1 << 20];

int count(int mask) {
	int ret = 0;
	for (int i = 0; i < n; i++)
		if (mask & (1 << i)) ret++;
	return ret;
}

int main() {
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	while (Test--) {
		cin >> n;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				cin >> adj[i][j];
		
		memset(dp, 0, sizeof(dp));
		dp[0] = 1;
		for (int i = 0; i < 1 << n; i++) {
			cnt[i] = count(i);
		}
		for (int i = 0; i < 1 << n; i++)
			for (int j = 0; j < n; j++)
				if (adj[cnt[i]][j] && (i & (1 << j)) == 0)
					dp[i | (1 << j)] += dp[i];
		cout << dp[(1 << n) - 1] << endl;
	}
	return 0;
}
