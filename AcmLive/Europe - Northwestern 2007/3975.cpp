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
typedef long long LL;

#define MAXL 1005
const int dx[4] = {0, 0, -1, 1};
const int dy[4] = {-1, 1, 0, 0};
int dist[MAXL][MAXL], d[MAXL][MAXL];
int N, X, Y;
int sx, sy, ex, ey;
queue<pair<int, int> > Q;

void init() {
	memset(dist, -1, sizeof(dist));
	while (!Q.empty())
		Q.pop();
}

bool check(int x, int y) {
	if (0 <= x && x < X && 0 <= y && y < Y) return true;
	return false;
}

int reach(int limit) {
	memset(d, -1, sizeof(d));
	while (!Q.empty())
		Q.pop();

	d[sx][sy] = 0;
	Q.push(MP(sx, sy));
	while (!Q.empty()) {
		pair<int, int> cur = Q.front();
		Q.pop();
		int x = cur.first, y = cur.second;

		for (int k = 0; k < 4; k++) {
			int xx = x + dx[k], yy = y + dy[k];

			if (!check(xx, yy)) continue;
			if (dist[xx][yy] < limit || d[xx][yy] >= 0) continue;

			d[xx][yy] = d[x][y] + 1;
			Q.push(MP(xx, yy));
		}
	}
	return d[ex][ey] >= 0;
}

int main() {
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	while (Test--) {
		init();
		cin >> N >> X >> Y;
		cin >> sx >> sy >> ex >> ey;
		while (N--) {
			int x, y;
			cin >> x >> y;
			dist[x][y] = 0;
			Q.push(MP(x, y));
		}

		while (!Q.empty()) {
			pair<int, int> cur = Q.front();
			Q.pop();
			int x = cur.first, y = cur.second;
			for (int k = 0; k < 4; k++) {
				int xx = x + dx[k], yy = y + dy[k];

				if (!check(xx, yy)) continue;
				if (dist[xx][yy] >= 0) continue;

				dist[xx][yy] = dist[x][y] + 1;
				Q.push(MP(xx, yy));
			}
		}

		int l = 0, r = min(dist[sx][sy], dist[ex][ey]), ret;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (reach(mid)) {
				l = mid + 1;
				ret = mid;
			}
			else r = mid - 1;
		}
		reach(ret);
		printf("%d %d\n", ret, d[ex][ey]);
	}
	return 0;
}
