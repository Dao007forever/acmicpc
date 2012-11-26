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
int n, m, L, K, inf = 0x3f3f3f3f;
std::vector<pair<int, int> > pos(10);
int mat[55][55];
int dp[55][55][11][1<<5];
bool vis[55][55][11][1<<5];
struct node {
	int x, y, rest, mon;
	node() {}
	node(int x, int y, int rest, int mon) : x(x), y(y), rest(rest), mon(mon) {}
};

bool check(int x, int y) {
	return (x >= 1 && x <= n && y >= 1 && y <= m && mat[x][y] != -1);
}

int findMonster(int x, int y) {
	for (int i = 0; i < K; i++)
		if (pos[i].first == x && pos[i].second == y)
			return i;
	return -1;
}

void spfa(int sx, int sy) {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			for (int u = 0; u <= L; u++) {
				for (int v = 0; v < 1<<K; v++) {
					dp[i][j][u][v] = inf, vis[i][j][u][v] = false;
				}
			}
		}
	}
	dp[sx][sy][L][0] = 0;
	queue<node> q;
	q.push(node(sx, sy, L, 0));
	while (!q.empty()) {
		node cur = q.front(); q.pop();
		vis[cur.x][cur.y][cur.rest][cur.mon] = 0;

		int newRest = cur.rest;
		if (mat[cur.x][cur.y] > 0 && (cur.mon & (1 << (mat[cur.x][cur.y]-1))) == 0)
			newRest = 0;
		int newMon = cur.mon;
		int t = findMonster(cur.x, cur.y);
		if (t != -1)
			newMon |= (1 << t);
		int upd = dp[cur.x][cur.y][cur.rest][cur.mon];
		if (newRest == 0) upd++, newRest = L - 1;
		else newRest--;

		for (int k = 0; k < 4; k++) {
			int x = cur.x + dx[k], y = cur.y + dy[k];
			if (!check(x, y)) continue;
			if (dp[x][y][newRest][newMon] > upd) {
				dp[x][y][newRest][newMon] = upd;
				if (!vis[x][y][newRest][newMon]) {
					vis[x][y][newRest][newMon] = 1;
					q.push(node(x, y, newRest, newMon));
				}
			}
		}
	}
}

int main(int argc, char const *argv[])
{
	while (~scanf("%d%d%d", &n, &m, &L)) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				scanf("%d", &mat[i][j]);
			}
		}
		scanf("%d", &K);
		for (int i = 0; i < K; i++) {
			scanf("%d%d", &pos[i].first, &pos[i].second);
		}
		int sx, sy, ex, ey;
		scanf("%d%d%d%d", &sx, &sy, &ex, &ey);
		spfa(sx, sy);
		int ret = inf;
		for (int i = 0; i <= L; i++)
			for (int j = 0; j < 1 << K; j++)
				ret = min(ret, dp[ex][ey][i][j]);
		if (ret == inf) puts("We need God's help!");
		else printf("%d\n", ret);
	}
	return 0;
}