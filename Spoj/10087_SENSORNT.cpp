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

const int maxV = 355;
const int maxE = maxV * maxV;
struct Edge {
	int a, b, c;
	int idx;
	bool operator < (const Edge &pt) const {
		if (c != pt.c) return c < pt.c;
		return idx < pt.idx;
	}
}es[maxE];
int n, m;
pair<int, int> pre[maxV];
bool vis[maxV];
set<pair<int, int> > st;
list<pair<int, int> > lst[maxV];

void dfs(int u) {
	vis[u] = true;
	list<pair<int, int> >::iterator it;
	for (it = lst[u].begin(); it != lst[u].end(); it++) {
		int v = it->first;
		if (!vis[v]) {
			pre[v] = MP(u, it->second);
			dfs(v);
		}
	}
}

bool isConnected(int a, int b) {
	memset(vis, 0, sizeof(vis));
	pre[a] = MP(-1, -1);
	dfs(a);
	return vis[b];
}

void solve() {
	st.clear();
	for (int i = 0; i < n; i++)
		lst[i].clear();
	int ret = 0x3f3f3f3f;
	int cnt = 0;
	for (int i = 0; i < m; i++) {
		int a = es[i].a, b = es[i].b;
		if (isConnected(a, b)) {
			cnt--;
			int now = b, Min = 0x3f3f3f3f, del, da, db;
			do {
				int nxt = pre[now].first, id = pre[now].second;
				if (es[id].c < Min) {
					del = id; da = now; db = nxt;
					Min =  es[id].c;
				}
				now = nxt;
			} while (now != a);
			list<pair<int, int> >::iterator it;
			for (it = lst[da].begin(); it != lst[da].end(); it++) {
				if (it->second == del) {
					lst[da].erase(it);
					break;
				}
			}
			for (it = lst[db].begin(); it != lst[db].end(); it++) {
				if (it->second == del) {
					lst[db].erase(it);
					break;
				}
			}
			st.erase(st.find(MP(Min, del)));
		}
		lst[a].push_back(MP(b, i));
		lst[b].push_back(MP(a, i));
		st.insert(MP(es[i].c, i));
		cnt++;
		if (cnt == n - 1) {
			int lo = st.begin()->first;
			set<pair<int, int> >::iterator it = st.end(); it--;
			int hi = it->first;
			ret = min(ret, hi - lo);
		}
	}
	printf("%d\n", ret);
}

int main(int argc, char const *argv[])
{
	while (~scanf("%d", &n) && n) {
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			scanf("%d%d%d", &es[i].a, &es[i].b, &es[i].c);
			es[i].idx = i;
		}
		sort(es, es + m);
		solve();
	}
	return 0;
}