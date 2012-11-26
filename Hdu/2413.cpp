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

#define MAXN 255
const int inf = 0x3f3f3f3f;
struct BipartiteGraph {
	int nx, ny;
	bool adj[MAXN][MAXN], mk[MAXN];
	int mate[MAXN];

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

int H, A;
pair<int, int> human[MAXN], alien[MAXN];
int dist[MAXN][MAXN];
bool beat(pair<int, int> a, pair<int, int> b, int d, int year) {
	if (year - d < 0) return false;
	if (a.second <= b.second) {
		return a.first >= b.first + (LL)d * b.second;
	} else {
		return a.first + (LL)(year - d) * a.second >= b.first + (LL)year * b.second;
	}
}
bool check(int year) {
	g.init(H, A);
	for (int i = 0; i < H; i++)
		for (int j = 0; j < A; j++) {
			if (beat(human[i], alien[j], dist[i][j], year)) {
				g.addEdge(i, j);
			}
		}
	return g.maxMatch() == A;
}
int main(int argc, char const *argv[])
{
	while (~scanf("%d%d", &H, &A) && H + A) {
		for (int i = 0; i < H; i++)
			scanf("%d%d", &human[i].first, &human[i].second);
		for (int i = 0; i < A; i++)
			scanf("%d%d", &alien[i].first, &alien[i].second);
		for (int i = 0; i < H; i++)
			for (int j = 0; j < A; j++) {
				scanf("%d", &dist[i][j]);
			}
		int l = 0, r = inf, ret = -1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (check(mid)) {
				r = mid - 1;
				ret = mid;
			} else l = mid + 1;
		}
		if (ret == -1) puts("IMPOSSIBLE");
		else printf("%d\n", ret);
	}
	return 0;
}