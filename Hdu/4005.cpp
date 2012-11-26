/*
 * Author: Yang Zhang
 * Created Time: Mon 17 Sep 2012 08:25:47 PM CST
 * File Name: 4005.cpp
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

#define maxn 10100
#define maxm 101000
const int inf = 0x3f3f3f3f;
struct Tree {
	int n;
	int Min, Min2;
	int dp[maxn];
	bool vis[maxn];
	vector<pair<int, int> > adj[maxn];

	void init(int n) {
		this->n = n;
		for (int i = 0; i < n; i++) adj[i].clear();
	}

	void addEdge(int a, int b, int c) {
		adj[a].PB(MP(b, c));
		adj[b].PB(MP(a, c));
	}

	void treeDp(int u) {
		vis[u] = true;
		for (vector<pair<int, int> >::iterator it = adj[u].begin(); it != adj[u].end(); it++) {
			int v = it->first, w = it->second;
			if (!vis[v]) {
				treeDp(v);
				dp[v] = min(dp[v], w);
				if (dp[v] < dp[u]) {
					Min2 = min(Min2, dp[u]);
					dp[u] = dp[v];
				} else {
					Min2 = min(Min2, dp[v]);
				}
			}
		}
	}

	void solve() {
		if (n == 1) {
			puts("-1");
			return;
		}
		int mini = inf, ki, kj;
		for (int u = 0; u < n; u++)
			for (vector<pair<int, int> >::iterator it = adj[u].begin(); it != adj[u].end(); it++) {
				if (it->second < mini) {
					mini = it->second;
					ki = u; kj = it->first;
				}
			}
		for (int i = 0; i < n; i++) vis[i] = false, dp[i] = inf;
		vis[ki] = vis[kj] = true;
		Min = inf; Min2 = inf;
		treeDp(ki);
		treeDp(kj);
		if (Min2 == inf) puts("-1");
		else printf("%d\n", Min2);
	}
	
}tree;
struct Nod {
	int b, c, nxt;
	void init(int b, int nxt, int c) {
		this->b = b;
		this->nxt = nxt;
		this->c = c;
	}
};
struct BCC {
	int E[maxn];		int n;			///原始图[0, n)
	Nod buf[maxm*2];	int len;		///资源
	
	bool brg[maxm*2];					///某边是否是桥
	bool cut[maxn];						///某点是否为割点
	int id[maxn];						///某点所在分支的编号
	
	int EBcc[maxn];		int nBcc;		///缩点后的图
	Nod bufBcc[maxn*2];	int lenBcc;		///缩点后的资源2*maxn足够！
	int tot[maxn];						///某个bcc包含的点数
	//以上变量可能会被solve后使用
	char vis[maxn];	///visited（0未访问，壹在访问，2访问完）
	
	void init(int n) {
		this->n = n;
		memset(E, 255, sizeof(E));
		len = 0;
	}
	void addEdge(int a, int b, int c) {
		buf[len].init(b, E[a], c);		E[a] = len ++;
		buf[len].init(a, E[b], c);		E[b] = len ++;
	}
	void dfs(int idx, int father, int deep) {
		static int D[maxn];		///某点的深度
		static int anc[maxn];	///祖先
		
		vis[idx] = 1;
		D[idx] = anc[idx] = deep;
		int tot = 0;
		for(int i = E[idx]; i != -1; i = buf[i].nxt) {
			int b = buf[i].b;
			if(vis[b]==1 && father!=b)
				anc[idx] = min(anc[idx], D[b]);
			if(vis[b] == 0) {
				dfs(b, idx, deep+1);
				tot ++;
				anc[idx] = min(anc[idx], anc[b]);
				if((deep==0&&tot>1) || (deep!=0 && anc[b]>=D[idx]))
					cut[idx] = true;
				if(anc[b]>D[idx])
					brg[i] = brg[i^1] = true;	//i^1 is the partner edge!
			}
		}
		vis[idx] = 2;
	}
	void floodFill(int idx) {//用id是否为-1，隐式表示有没有访问过
		id[idx] = nBcc;
		for(int i = E[idx]; i != -1; i = buf[i].nxt) {
			if(id[buf[i].b]==-1 && false==brg[i]) {
				floodFill(buf[i].b);
			}
		}
	}
	void solve() {
		memset(vis, 0, sizeof(vis));
		memset(cut, 0, sizeof(cut));
		memset(brg, 0, sizeof(brg));
		memset(id, 255, sizeof(id));
		memset(tot, 0, sizeof(tot));
		memset(EBcc, 255, sizeof(EBcc));
		nBcc = lenBcc = 0;
			//init over!
		for(int i=0; i<n; i++)	if(vis[i]==0)	dfs(i,i,0);
			///dfs结束，找出割点和桥
		for(int i=0; i<n; i++)	if(id[i]==-1)	floodFill(i), nBcc++;
			///找出双连通分支
		/*for(int i=0; i<n; i++)	tot[id[i]] ++;
			///统计出每个双连通分支包含点的个数
		for(int j = 0; j < n; j ++) {
			int a = id[j];
			for(int i = E[j]; i != -1; i = buf[i].nxt) {
				int b = id[buf[i].b];
				if(brg[i] && a<b) {
					bufBcc[lenBcc].init(b, EBcc[a]);	EBcc[a] = lenBcc ++;
					bufBcc[lenBcc].init(a, EBcc[b]);	EBcc[b] = lenBcc ++;
				}
			}
		}*/
			///所点后的图构建完毕，不含重边！
	}

} bcc;

int main() {
	int n, m;
	while (~scanf("%d%d", &n, &m)) {
		bcc.init(n);
		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			a--; b--;
			bcc.addEdge(a, b, c);
		}
		bcc.solve();

		tree.init(bcc.nBcc);
		for (int j = 0; j < n; j++) {
			int a = bcc.id[j];
			for (int i = bcc.E[j]; i != -1; i = bcc.buf[i].nxt) {
				int b = bcc.id[bcc.buf[i].b];
				if (bcc.brg[i] && a < b) {
					tree.addEdge(a, b, bcc.buf[i].c);
				}
			}
		}
		tree.solve();
	}
	return 0;
}

