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

const int MAXN = 405;
const int inf = 0x3f3f3f3f;
struct KM {
	int E[MAXN][MAXN], n;		//图的所在，需传入
	bool map[MAXN][MAXN];		//每次二分匹配时的图
	int lx[MAXN], ly[MAXN];
	
	bool visx[MAXN], visy[MAXN];//判断二分匹配时,某点是否在交错树上
	int mate[MAXN];				//V2中某点的伙伴，-1为空
	
	bool dfs(int idx) {
		visx[idx] = true;
		for(int i = 0; i < n; i ++) {
			if(map[idx][i] && !visy[i]) {
				visy[i] = true;
				if(mate[i]==-1 || dfs(mate[i])) {
					mate[i] = idx;
					return true;
				}
			}
		}
		return false;
	}
	int solve() {
		// static int lx[MAXN], ly[MAXN];//V1和V2中点的标号
		int i, j;
		for(i = 0; i < n; i ++) {
			ly[i] = 0;
			lx[i] = -inf;
			for(j = 0; j < n; j ++) {
				lx[i] = max(lx[i], E[i][j]);
			}
		}
		while(true) {
			for(i = 0; i < n; i ++) {
				for(j = 0; j < n; j ++) {
					map[i][j] = lx[i]+ly[j]==E[i][j];
				}
			}
			//构图完毕，开始二分匹配
			memset(mate, 255, sizeof(mate));
			for(i = 0; i < n; i ++) {
				memset(visx, 0, sizeof(visx));
				memset(visy, 0, sizeof(visy));
				if(false == dfs(i))	break;
			}
			if(i == n) {	//找到完备匹配
				break;
			} else {		//未找到完备匹配，修改标号
				int ex = inf;
				for(i = 0; i < n; i ++) {
					if(false == visx[i])	continue;
					for(j = 0; j < n; j ++) {
						if(false == visy[j])
							ex = min(ex, lx[i]+ly[j]-E[i][j]);
					}
				}
				for(i = 0; i < n; i ++) {
					if(visx[i])	lx[i] -= ex;
					if(visy[i])	ly[i] += ex;
				}
			}
		}
		int ans = 0;
		for(int i = 0; i < n; i ++) {
			ans += E[mate[i]][i];
		}
		return ans;
	}
};

const int maxV = 65;
struct Edge {
	int a, b, c;
	void input() {
		scanf("%d%d%d", &a, &b, &c);
	}
}es[MAXN];
int compute(int n, Edge *tree, int m, Edge *e) {
	static int g[maxV][maxV];
	static int prev[maxV];
	static int idx[maxV];
	static bool vis[maxV];
	static KM km;

	memset(g, -1, sizeof(g));

	for (int i = 0; i < n - 1; i++) {
		int a = tree[i].a, b = tree[i].b, c = tree[i].c;
		g[a][b] = g[b][a] = i;
	}

	memset(km.E, 0, sizeof(km.E));
	km.n = max(n - 1, m);

	queue<int> q;
	for (int j = 0; j < m; j++) {
		int a = e[j].a, b = e[j].b, c = e[j].c;
		memset(prev, -1, sizeof(prev));
		memset(vis, 0, sizeof(vis));
		while (!q.empty()) q.pop();
		q.push(a); vis[a] = true;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			if (u == b) break;
			for (int v = 0; v < n; v++) {
				if (g[u][v] != -1 && !vis[v]) {
					vis[v] = true;
					prev[v] = u;
					idx[v] = g[u][v];
					q.push(v);
				}
			}
		}
		for (int k = b; prev[k] != -1; k = prev[k]) {
			int i = idx[k];
			int trc = tree[i].c;
			km.E[i][j] = trc - c;
		}
	}
	int val = km.solve();

	for (int i = 0; i < n - 1; i++) {
		printf("%d\n", tree[i].c - km.lx[i]);
	}
	for (int i = 0; i < m; i++) {
		printf("%d\n", e[i].c + km.ly[i]);
	}
}

int main(int argc, char const *argv[])
{
	int n, m;
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 0; i < m; i++) {
			es[i].input();
			es[i].a--; es[i].b--;
		}
		compute(n, es, m - (n - 1), es + n - 1);
	}
	return 0;
}