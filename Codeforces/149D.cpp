#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

typedef long long LL;
const int maxn = 700 + 5;
const LL mod = 1000000007;
LL dp[maxn][maxn][5][5];
int adj[5][5], match[maxn], brack[maxn][maxn], st[maxn];

LL calc(int l, int r, int cL, int cR) {
	if (dp[l][r][cL][cR] != -1) return dp[l][r][cL][cR];

	if (l + 1 == r) 
		return dp[l][r][cL][cR] = brack[cL][cR];
	LL ret = 0;
	if (match[l] == r) {
		if (!brack[cL][cR]) return dp[l][r][cL][cR] = 0;
		for (int i = 0; i < 3; i++)
			if (adj[cL][i])
				for (int j = 0; j < 3; j++)
					if (adj[j][cR]) {
						ret += calc(l + 1, r - 1, i, j);
						ret %= mod;
					}
	} else {
		int m = match[l];
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				if (adj[i][j]) {
					LL t1 = calc(l, m, cL, i);
					LL t2 = calc(m + 1, r, j, cR);
					ret += t1 * t2;
					ret %= mod;
				}
	}
	return dp[l][r][cL][cR] = ret;
}

int main() {
	string s;
	cin >> s;
	int sz = 0, n = s.size();
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == '(')
			st[sz++] = i;
		else match[st[--sz]] = i;
	}
	memset(brack, 0, sizeof(brack));
	memset(adj, 1, sizeof(adj));
	memset(dp, -1, sizeof(dp));
	brack[0][1] = brack[0][2] = brack[1][0] = brack[2][0] = true;
	adj[1][1] = adj[2][2] = false;
	LL ret = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			ret += calc(0, n - 1, i, j);
			ret %= mod;
		}
	cout << ret << endl;
	return 0;
}
