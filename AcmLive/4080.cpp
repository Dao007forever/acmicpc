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

#define maxV 105
#define maxE 1005
const LL inf = 0x3f3f3f3f3f3f3f3f;
struct Edge {
	int v, next, idx;
	LL w;
}edge[maxE << 1];
int num, Head[maxV];
int n, m, L;
LL dis[maxV], f[maxV];
bool use[maxE], vis[maxV], cut[maxV][maxE];

void addEdge(int a, int b, LL c, int idx) {
	edge[num].v = b; edge[num].w = c; edge[num].idx = idx; edge[num].next = Head[a]; Head[a] = num++;
}

LL spfa(int st) {
	for (int i = 0; i < n; i++) {
		dis[i] = inf; vis[i] = false;
	}
	dis[st] = 0;
	queue<int> q;
	q.push(st);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		vis[u] = false;
		for (int i = Head[u]; ~i; i = edge[i].next) {
			int v = edge[i].v, w = edge[i].w, idx = edge[i].idx;
			if (!use[idx]) {
				if (dis[u] + w < dis[v]) {
					dis[v] = dis[u] + w;
					if (!vis[v]) {
						vis[v] = true;
						q.push(v);
					}
				}
			}
		}
	}

	LL ret = 0;
	for (int i = 0; i < n; i++) {
		if (dis[i] < inf) ret += dis[i];
		else ret += L;
	}
	return ret;
}

int main(int argc, char const *argv[])
{
	while (~scanf("%d%d%d", &n, &m, &L)) {
		num = 0;
		memset(Head, -1, sizeof(Head));

		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			a--; b--;
			addEdge(a, b, c, i);
			addEdge(b, a, c, i);
		}
		memset(cut, 0, sizeof(cut));
		memset(use, 0, sizeof(use));
		LL ret1 = 0, ret2 = 0;
		for (int i = 0; i < n; i++) {
			f[i] = spfa(i);
			ret1 += f[i];
			for (int u = 0; u < n; u++) {
				for (int j = Head[u]; ~j; j = edge[j].next) {
					int v = edge[j].v, w = edge[j].w, idx = edge[j].idx;
					if (dis[u] + w == dis[v]) {
						cut[i][idx] = true;
					}
				}
			}
		}
		for (int j = 0; j < m; j++) {
			LL tmp = 0;
			for (int i = 0; i < n; i++) {
				if (!cut[i][j]) tmp += f[i];
				else {
					use[j] = true;
					tmp += spfa(i);
					use[j] = false;
				}
			}
			ret2 = max(ret2, tmp);
		}
		cout << ret1 << " " << ret2 << endl;
	}
	return 0;
}