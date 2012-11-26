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

#define MAXN 105
int N, K;
string dp[MAXN][MAXN][9];
string st[MAXN];
int p[MAXN];
char tmp[MAXN];

bool cmp(const string &a, const string &b) {
	return a + b > b + a;
}

void update(string &a, string b) {
	if (a.size() < b.size() || (a.size() == b.size() && a < b))
		a = b;
}

int main() {
	freopen("in.txt", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d%d", &N, &K);
		for (int i = 0; i < N; i++) {
			scanf("%d", &p[i]);
			sprintf(tmp, "%d", p[i]);
			st[i] = tmp;
		}
		sort(st, st + N, cmp);
		for (int i = 0; i < N; i++)
			p[i] = atoi(st[i].c_str());

		for (int i = 0; i < N; i++)
			for (int j = 0; j <= K; j++)
				for (int k = 0; k < 9; k++) {
					dp[i][j][k].clear();
				}

		for (int i = 0; i < N; i++)
			update(dp[i][1][p[i] % 9], st[i]);
		for (int i = 0; i + 1 < N; i++)
			for (int j = 1; j <= K; j++)
				for (int k = 0; k < 9; k++)
					if (dp[i][j][k].size()) {
						update(dp[i + 1][j][k], dp[i][j][k]);
						update(dp[i + 1][j + 1][(k + p[i + 1]) % 9], dp[i][j][k] + st[i + 1]);
   					}
		if (dp[N - 1][K][0].size() == 0) {
			puts("-1");
		} else {
			puts(dp[N - 1][K][0].c_str());
		}
	}
	return 0;
}
