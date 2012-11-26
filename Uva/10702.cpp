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

int C, S, E, T;
int tag[111], adj[111][111];
int dp[1111][111];

int main() {
	freopen("in", "r", stdin);
	while (cin >> C >> S >> E >> T) {
		if (C == 0 && S == 0 && E == 0 && T == 0) break;
		S--;
		memset(dp, -1, sizeof(dp));
		memset(tag, 0, sizeof(tag));
		for (int i = 0; i < C; i++)
			for (int j = 0; j < C; j++)
				cin >> adj[i][j];
		for (int i = 0; i < E; i++) {
			int x;
			cin >> x;
			x--;
			tag[x] = 1;
		}

		dp[0][S] = 0;
		for (int i = 0; i < T; i++)
			for (int j = 0; j < C; j++)
				if (dp[i][j] >= 0) {
					for (int k = 0; k < C; k++)
						if (dp[i][j] + adj[j][k] > dp[i + 1][k])
							dp[i + 1][k] = dp[i][j] + adj[j][k];
				}
		int ret = 0;
		for (int i = 0; i < C; i++)
			if (tag[i])
				ret = max(ret, dp[T][i]);
		cout << ret << endl;
	}
	return 0;
}
