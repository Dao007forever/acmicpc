/*
 * Author : Yang Zhang
 */
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

const int maxn = 10005;
#define th(x) this->x = x
int rmq[2 * maxn];
struct ST {
	int mm[2 * maxn];
	int best[20][2 * maxn];

	void init(int n) {
		int i, j, a, b;
		mm[0] = -1;
		for (i = 1; i <= n; i++) {
			mm[i] = ((i & (i - 1)) == 0 ? mm[i - 1] + 1 : mm[i - 1]);
			best[0][i] = i;
		}
		for (i = 1; i <= mm[n]; i++) {
			for (j = 1; j <= n + 1 - (1 << i); j++) {
				a = best[i - 1][j];
				b = best[i - 1][j + (1 << (i - 1))];
				best[i][j] = rmq[a] < rmq[b] ? a : b;
			}
		}
	}

	int query(int a, int b) {
		if (a >  b) swap(a, b);
		int t;
		t = mm[b - a + 1];
		a = best[t][a];
		b = best[t][b - (1 << t) + 1];
		return rmq[a] < rmq[b] ? a : b;
	}
};
struct Nod {
	int b, nxt;
	void init(int b, int nxt) {
		th(b); th(nxt);
	}
};
/**
	lca转化为rmq问题
	注意: 
		1.maxn为最大节点数, ST的数组和F、buf要设置为2*maxn!!!!!
		2.ST类为1开始，此类依然为0开始!
		3.F是欧拉序列,rmq是深度序列,P某点在欧拉序列中第一次出现的位置
*/
struct LCA2RMQ {
	int n;							//节点个数
	Nod buf[2*maxn]; int len; int E[maxn];	//Tree	资源
	int V[2*maxn], route[maxn];				//路径的权，根到某点的路径和
	bool vis[maxn];						//0没有访问，壹正在访问
	
	ST st;							//Spare-Table...
	int F[2*maxn], P[maxn], cnt;	//介绍如上,cnt为计数器,lev为dfs时层数(减少递归栈大小)
	
	void init(int n) {
		th(n);
		len = 0;
		memset(E, 255, sizeof(E));
	}
	
	void addEdge(int a, int b, int v) {
		buf[len].init(b, E[a]); V[len] = v; E[a] = len ++;
		buf[len].init(a, E[b]);	V[len] = v;	E[b] = len ++;
	}
	
	int query(int a, int b) {				//传入两个节点，返回他们lca节点编号
		return F[st.query(P[a], P[b])];
	}
	
	void dfs(int a, int lev) {
		vis[a] = 1;		
		++cnt;
		F[cnt] = a;
		rmq[cnt] = lev;
		P[a] = cnt;
		for(int i = E[a]; i != -1; i = buf[i].nxt) {
			if(vis[buf[i].b]) continue;
			route[buf[i].b] = route[a] + V[i];
			dfs(buf[i].b, lev + 1);
			++cnt;
			F[cnt] = a;
			rmq[cnt] = lev;
		}
	}
	void solve(int root) {
		memset(vis, 0, sizeof(vis));
		route[root] = cnt = 0;
		dfs(root, 0);
		st.init(2 * n - 1);
	}
	
} lca;

struct djs {
	int n;
	int p[maxn];

	void init(int n) {
		this->n = n;
		for (int i = 1; i <= n; i++)
			p[i] = i;
	}

	int find(int x) {
		return p[x] == x ? x : p[x] = find(p[x]);
	}

	void Union(int x, int y) {
		p[find(x)] = p[find(y)];
	}
}uf;

int main() {
	int n, m, q;
	while (~scanf("%d%d%d", &n, &m, &q)) {
		lca.init(n + 1);
		uf.init(n);
		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			lca.addEdge(a, b, c);
			if (uf.find(a) != uf.find(b))
				uf.Union(a, b);
		}
		for (int i = 1; i <= n; i++)
			if (uf.p[i] == i) {
				lca.addEdge(0, i, 0);
			}
		lca.solve(0);
		while (q--) {
			int a, b;
			scanf("%d%d", &a, &b);
			int anc = lca.query(a, b);
			if (anc == 0) puts("Not connected");
			else printf("%d\n", lca.route[a] + lca.route[b] - 2 * lca.route[anc]);
		}
	}
	return 0;
}
