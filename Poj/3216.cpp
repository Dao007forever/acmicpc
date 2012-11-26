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

const int inf = 0x3f3f3f3f;
int q, n;
int d[22][22];
int mk[222], mate[222];
bool adj[222][222];
struct Task {
	int p, t, d;
	void input() {
		scanf("%d%d%d", &p, &t, &d);
		p--;
	}
}task[222];

bool cmp(const Task &a, const Task &b) {
	if (a.t != b.t) return a.t < b.t;
	return a.d < b.d;
}

int dfs(int u) {
	for (int v = 0; v < n; v++) {
		if (adj[u][v] && !mk[v]) {
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
	memset(mate, -1, sizeof(mate));
	int ret = 0;
	for (int i = 0; i < n; i++) {
		memset(mk, 0, sizeof(mk));
		ret += dfs(i);
	}
	return ret;
}

bool check(int a, int b) {
	int u = task[a].p, v = task[b].p;
	return task[a].t + task[a].d + d[u][v] <= task[b].t;
}

int main(int argc, char const *argv[])
{
	while (~scanf("%d%d", &q, &n)) {
		if (q == 0 && n == 0) break;
		for (int i = 0; i < q; i++) {
			for (int j = 0; j < q; j++) {
				scanf("%d", &d[i][j]);
				if (d[i][j] == -1) d[i][j] = inf;
			}
		}
		for (int k = 0; k < q; k++) {
			for (int i = 0; i < q; i++) {
				for (int j = 0; j < q; j++) {
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
				}
			}
		}
		for (int i = 0; i < n; i++) {
			task[i].input();
		}
		sort(task, task + n, cmp);
		memset(adj, 0, sizeof(adj));
		for (int i = 0; i < n; i++) {
			for (int j = i + 1; j < n; j++) {
				adj[i][j] = check(i, j);
			}
		}
		int ret = n - maxMatch();
		printf("%d\n", ret);
	}
	return 0;
}