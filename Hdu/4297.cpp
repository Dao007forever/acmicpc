/*
 * Author: Yang Zhang
 * Created Time: Sun 16 Sep 2012 07:43:07 PM CST
 * File Name: 4297.cpp
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

#define maxn 500005
#define th(x) this->x = x
int cir[maxn], adj[maxn], pos[maxn], len[maxn], rep[maxn];
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
struct LCA2RMQ {
	int n;							//节点个数
	Nod buf[2*maxn]; int len; int E[maxn];	//Tree	资源
	int V[2*maxn], route[maxn];				//路径的权，根到某点的路径和
	bool vis[maxn];						//0没有访问，1正在访问
	
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
	
	//1.【递归版】
	/*void dfs(int a, int lev) {
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
	}*/
	
	//2.【非递归版】
	void solve(int root) {
		static Nod stk[maxn];
		memset(vis, 0, sizeof(vis));
		
		stk[0].init(root, E[root]);
		int len = 1;
		int lev = 0;
		cnt = 0;
		route[root] = 0;										//update route!
		
		while(1) {
			Nod & cur = stk[len-1];
//here, b means current Nod, nxt means nxt's pointer(as buf.nxt)!
			if(false == vis[cur.b]) {
				vis[cur.b] = 1;
				F[++ cnt] = cur.b;
				rmq[cnt] = lev;
				P[cur.b] = cnt;
			} else if(cur.nxt == -1) {
				if(--len == 0)	break;
				F[++ cnt] = stk[len-1].b;
				rmq[cnt] = -- lev;
			} else {
				int & i = cur.nxt;
				if(!vis[buf[i].b]) {
					route[buf[i].b] = route[cur.b] + V[i];		
//update route!
					lev ++;
					stk[len ++].init(buf[i].b, E[buf[i].b]);
				}
				i = buf[i].nxt;
			}
		}
		st.init(2 * n - 1);
	}
	queue<int> q;
	void bfs(int st) {
		q.push(st);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			rep[u] = st;
			for (int i = E[u]; i != -1; i = buf[i].nxt) {
				int v = buf[i].b;
				if (!rep[v]) q.push(v);
			}
		}
	}

} lca;
struct DisJointSet{
	int rank[maxn], parent[maxn];

	void init(int n) {
		for (int i = 0; i <= n; i++) {
			rank[i] = 0;
			parent[i] = i;
		} 
	}

	/*int Find(int x) {
		if (parent[x] == x) return x;
		return parent[x] = Find(parent[x]);
	}*/
	int Find(int x) {
		int px, i;
		for (px = x; parent[px] != px; px = parent[px]);
		while (x != px) {
			i = parent[x];
			parent[x] = px;
			x = i;
		}
		return px;
	}

	void Union(int x, int y) {
		if (rank[x] >= rank[y]) {
			parent[y] = x;
			if (rank[x] == rank[y])
				rank[x]++;
		}
		else {
			parent[x] = y;
		}
	}
}dsu;

void output(int a, int b, int c, int d) {
	if (max(a, b) < max(c, d)) {
		printf("%d %d\n", a, b);
		return;
	}
	if (max(c, d) < max(a, b)) {
		printf("%d %d\n", c, d);
		return;
	}
	if (min(a, b) < min(c, d)) {
		printf("%d %d\n", a, b);
		return;
	}
	if (min(c, d) < min(a, b)) {
		printf("%d %d\n", c, d);
		return;
	}
	if (a >= b) printf("%d %d\n", a, b);
	else printf("%d %d\n", c, d);
}

int main() {
	int n, m;
	while (~scanf("%d%d", &n, &m)) {
		for (int i = 1; i <= n; i++) {
			scanf("%d", &adj[i]);
			cir[i] = len[i] = rep[i] = 0;
		}

		dsu.init(n);
		for (int i = 1; i <= n; i++) {
			int pa = dsu.Find(i), pb = dsu.Find(adj[i]);
			if (pa != pb) {
				dsu.Union(pa, pb);
			} else {
				for (int j = i; !cir[j]; j = adj[j]) {
					cir[j] = i;
					len[i]++;
					pos[j] = len[i];
				}
			}
		}

		lca.init(n + 1);
		int root = 0;
		for (int i = 1; i <= n; i++) {
			if (!cir[i]) {
				lca.addEdge(adj[i], i, 1);
			}
		}
		for (int i = 1; i <= n; i++) {
			if (cir[i]) {
				lca.bfs(i);
				lca.addEdge(root, i, 0);
			}
		}
		lca.solve(root);

		while (m--) {
			int a, b;
			scanf("%d%d", &a, &b);
			int anc = lca.query(a, b);
			if (anc != root) {
				printf("%d %d\n", lca.route[a] - lca.route[anc], lca.route[b] - lca.route[anc]);
			} else {
				if (dsu.Find(a) != dsu.Find(b)) {
					printf("-1 -1\n");
					continue;
				}
				int pa = rep[a], pb = rep[b];
				int disa = lca.route[a], disb = lca.route[b];
				int sum = len[cir[pa]];
				
				int t1 = disa + (pos[pa] < pos[pb] ? pos[pb] - pos[pa] : sum - pos[pa] + pos[pb]);
				int t2 = disb;
				int t3 = disa;
				int t4 = disb + (pos[pb] < pos[pa] ? pos[pa] - pos[pb] : sum - pos[pb] + pos[pa]);
				output(t1, t2, t3, t4);
			}
		}
	}
	return 0;
}

