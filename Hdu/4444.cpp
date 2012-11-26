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

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
struct Point {
	int x, y;
}st, ed;
struct Rect {
	int x1, y1, x2, y2;
	void input() {
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		if (x1 > x2) swap(x1, x2);
		if (y1 > y2) swap(y1, y2);
	}
}rec[55];
int n;
vector<int> vx, vy;
map<int, int> mpx, mpy;
int dis[305][305];
int mk[305][305];

void build() {
	memset(mk, 0, sizeof(mk));
	for (int i = 0; i < n; i++) {
		int x1 = mpx[3 * rec[i].x1], y1 = mpy[3 * rec[i].y1];
		int x2 = mpx[3 * rec[i].x2], y2 = mpy[3 * rec[i].y2];
		for (int j = x1; j <= x2; j++) {
			for (int k = y1; k <= y2; k++) {
				if (j == x1 || j == x2 || k == y1 || k == y2) mk[j][k]++;
				else mk[j][k] += 2;
			}
		}
	}
}

int bfs() {
	memset(dis, -1, sizeof(dis));
	queue<pair<int, int> > q;
	st.x = mpx[3 * st.x]; st.y = mpy[3 * st.y];
	ed.x = mpx[3 * ed.x]; ed.y = mpy[3 * ed.y];
	q.push(MP(st.x, st.y));
	dis[st.x][st.y] = 0;
	while (!q.empty()) {
		pair<int, int> cur = q.front(); q.pop();
		int x = cur.first, y = cur.second;
		if (x == ed.x && y == ed.y) break;
		for (int k = 0; k < 4; k++) {
			int xx = x + dx[k], yy = y + dy[k];
			while (xx >= 0 && xx < vx.size() && yy >= 0 && yy < vy.size()) {
				if (mk[xx][yy] >= 2) break;
				if (dis[xx][yy] == -1) {
					dis[xx][yy] = dis[x][y] + 1;
					q.push(MP(xx, yy));
				}
				xx = xx + dx[k]; yy = yy + dy[k];
			}
		}
	}
	if (dis[ed.x][ed.y] == -1) return -1;
	return dis[ed.x][ed.y] - 1;
}

int main(int argc, char const *argv[])
{
	while (~scanf("%d%d%d%d", &st.x, &st.y, &ed.x, &ed.y)) {
		if (!st.x && !st.y && !ed.x && !ed.y) break;
		vx.clear(); vy.clear();
		mpx.clear(); mpy.clear();
		for (int k = -1; k <= 1; k++) {
			vx.PB(3 * st.x + k); vx.PB(3 * ed.x + k);
			vy.PB(3 * st.y + k); vy.PB(3 * ed.y + k);
		}
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			rec[i].input();
			for (int k = -1; k <= 1; k++) {
				vx.PB(3 * rec[i].x1 + k); vx.PB(3 * rec[i].x2 + k);
				vy.PB(3 * rec[i].y1 + k); vy.PB(3 * rec[i].y2 + k);
			}
		}
		sort(vx.begin(), vx.end()); vx.resize(unique(vx.begin(), vx.end()) - vx.begin());
		sort(vy.begin(), vy.end()); vy.resize(unique(vy.begin(), vy.end()) - vy.begin());
		for (int i = 0; i < vx.size(); i++) mpx[vx[i]] = i;
		for (int i = 0; i < vy.size(); i++) mpy[vy[i]] = i;
		build();
		int ret = bfs();
		printf("%d\n", ret);
	}
	return 0;
}