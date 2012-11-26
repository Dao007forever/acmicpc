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

#define MAXN 105
const int inf = 0x3f3f3f3f;
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
int R, C;
char mat[MAXN][MAXN];
int d[55][MAXN][MAXN];
pair<int, int> pos[105];
int posnum;
int cnt;
int px[MAXN * MAXN], py[MAXN * MAXN];

struct BipartiteGraph {
	int nx, ny;
	bool mk[MAXN * MAXN];
	int mate[MAXN * MAXN];
	bool adj[55][10005];

	void init(int nx, int ny) {
		this->nx = nx; this->ny = ny;
		memset(adj, 0, sizeof(adj));
	}

	void addEdge(int u, int v) {
		adj[u][v] = true;
	}

	int dfs(int u) {
		for (int v = 0; v < ny; v++) {
			if (!mk[v] && adj[u][v]) {
				mk[v] = true;
				if (mate[v] == -1 || dfs(mate[v])) {
					mate[v] = u;
					return 1;
				}
			}
		}
		return 0;
	}

	int maxMatch() {
		int ret = 0;
		memset(mate, -1, sizeof(mate));
		for (int i = 0; i < nx; i++) {
			memset(mk, 0, sizeof(mk));
			ret += dfs(i);
		}
		return ret;
	}
}g;

bool check(int x, int y) {
	return (x >= 0 && x < R && y >= 0 && y < C && mat[x][y] != '#');
}

void bfs(int id, pair<int, int> st) {
	memset(d[id], -1, sizeof(d[id]));
	d[id][st.first][st.second] = 0;
	queue<pair<int, int> > q;
	q.push(st);
	while (!q.empty()) {
		pair<int, int> cur = q.front(); q.pop();
		for (int k = 0; k < 4; k++) {
			int x = cur.first + dx[k], y = cur.second + dy[k];
			if (!check(x, y)) continue;
			if (d[id][x][y] == -1) {
				d[id][x][y] = d[id][cur.first][cur.second] + 1;
				q.push(MP(x, y));
			}
		}
	}
}

void findDes() {
	for (int i = 0; i < posnum; i++) {
		bfs(i, pos[i]);
	}
}

int solve() {
	for (int i = 0; i < posnum - 1; i++)
		if (d[i][pos[i+1].first][pos[i+1].second] == -1) return -1;
	if (posnum == 1) return 0;
	g.init(posnum - 1, cnt);
	for (int i = 0; i < posnum - 1; i++) {
		for (int j = 0; j < cnt; j++) {
			if (d[i][px[j]][py[j]] == -1 || d[i+1][px[j]][py[j]] == -1) continue;
			if (d[i][px[j]][py[j]] + d[i + 1][px[j]][py[j]] == d[i][pos[i+1].first][pos[i+1].second])
				g.addEdge(i, j);
		}
	}
	return g.maxMatch();
}

int main(int argc, char const *argv[])
{
	while (~scanf("%d%d", &R, &C)) {
		cnt = 0; posnum = 0;
		for (int i = 0; i < R; i++) {
			scanf("%s", mat[i]);
			for (int j = 0; j < C; j++) {
				if (mat[i][j] == '*') {
					px[cnt] = i; py[cnt] = j;
					cnt++;
				}
				if (mat[i][j] >= 'A' && mat[i][j] <= 'Z') {
					pos[mat[i][j] - 'A'] = MP(i, j);
					posnum++;
				}
				if (mat[i][j] >= 'a' && mat[i][j] <= 'z') {
					pos[mat[i][j] - 'a' + 26] = MP(i, j);
					posnum++;
				}
			}
		}
		findDes();
		int ret = solve();
		printf("%d\n", ret);
	}
	return 0;
}