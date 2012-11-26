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
#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
int n, m, k;
bool vis[55][55], mk[55][55];
pair<int, int> mate[55][55];

int dfs(pair<int, int> u) {
	for (int k = 0; k < 4; k++) {
		int x = u.first + dx[k], y = u.second + dy[k];
		if (x >= 0 && x < n && y >= 0 && y < m && !vis[x][y]) {
			if (!mk[x][y]) {
				mk[x][y] = true;
				if (mate[x][y] == MP(-1, -1) || dfs(mate[x][y])) {
					mate[x][y] = u;
					return 1;
				}
			}
		}
	}
	return 0;
}

int maxMatch() {
	int ret = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			mate[i][j] = MP(-1, -1);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			if (((i + j) & 1) || vis[i][j]) continue;
			memset(mk, 0, sizeof(mk));
			ret += dfs(MP(i, j));
		}
	return ret;
}

int main(int argc, char const *argv[])
{
	while (~scanf("%d%d%d", &n, &m, &k)) {
		if ((n * m - k) & 1) {
			puts("NO");
			continue;
		}
		int cnt = (n * m - k) / 2;
		memset(vis, 0, sizeof(vis));
		while (k--) {
			int x, y;
			scanf("%d%d", &x, &y);
			x--; y--;
			vis[y][x] = 1;
		}
		int ret = maxMatch();
		printf("%s\n", ret == cnt ? "YES" : "NO");
	}
	return 0;
}