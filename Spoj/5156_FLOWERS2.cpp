/*
 * Author: Yang Zhang
 * Created Time: Mon 27 Aug 2012 03:47:50 PM CST
 * File Name: 5156_FLOWERS2.cpp
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

#define MAXN 205
bool mk[MAXN], done[MAXN], adj[MAXN][MAXN];
int cx[MAXN], cy[MAXN];
int mat[MAXN][MAXN];
int n, m, kth;

bool find(int i) {
	for (int j = 0; j < n; j++) {
		if (!done[j] && !mk[j] && adj[i][j]) {
			mk[j] = true;
			if (cy[j] == -1 || find(cy[j])) {
				cy[j] = i;
				cx[i] = j;
				return true;
			}
		}
	}
	return false;
}

void hungary() {
	int ret = 0;
	memset(cy, -1, sizeof(cy));
	for (int i = 0; i < n; i++) {
		memset(mk, 0, sizeof(mk));
		if (find(i)) ret++;
	}
}

bool dfs(int cur) {
	if (cur == n) return !(--kth);
	for (int i = 0; i < n; i++) {
		if (done[i] || !adj[cur][i]) continue;
		cy[cx[cur]] = -1;
		memset(mk, 0, sizeof(mk));
		mk[i] = true;
		if (cy[i] == -1 || find(cy[i])) {
			cy[i] = cur;
			cx[cur] = i;
			done[i] = true;
			if (dfs(cur + 1)) return true;
			done[i] = false;
		}
	}
	return false;
}

int main() {
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; cas <= Test; cas++) {
		scanf("%d%d%d", &n, &m, &kth);
		for (int i = 0; i < m; i++)
			for (int j = 0; j < n; j++) {
				scanf("%d", &mat[i][j]);
				mat[i][j]--;
			}
		printf("Case #%d: ", cas);
		bool ok = m != n;
		if (ok) {
			memset(adj, 1, sizeof(adj));
			for (int i = 0; i < m; i++)
				for (int j = 0; j < n; j++)
					adj[j][mat[i][j]] = false;
			memset(done, 0, sizeof(done));
			hungary();
			ok = dfs(0);
		}
		if (!ok) {
			puts("-1");
		} else {
			for (int i = 0; i < n; i++)
				printf("%d%c", cx[i] + 1, i == n - 1 ? '\n' : ' ');
		}
	}
	return 0;
}

