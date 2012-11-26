/*
 * Author: Yang Zhang
 * Created Time: Tue 18 Sep 2012 05:30:15 PM CST
 * File Name: 2117.cpp
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
#define maxm 1010000
struct Nod {
	int b, nxt;
	void init(int b, int nxt) {
		this->b = b;
		this->nxt = nxt;
	}
};
struct BCC {
	int E[maxn];		int n;			///原始图[0, n)
	Nod buf[maxm*2];	int len;		///资源
	
	bool brg[maxm*2];					///某边是否是桥
	int cut[maxn];						///某点是否为割点
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
	void addEdge(int a, int b) {
		buf[len].init(b, E[a]);		E[a] = len ++;
		buf[len].init(a, E[b]);		E[b] = len ++;
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
					cut[idx]++;
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
	int solve() {
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
		
		int ret = 0;
		for (int i = 0; i < n; i++)
			ret = max(ret, cut[i]);
		return ret;
			///找出双连通分支
/*		for(int i=0; i<n; i++)	tot[id[i]] ++;
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

struct DisJointSet{
	int rank[maxn], parent[maxn];

	void init(int n) {
		for (int i = 0; i < n; i++) {
			rank[i] = 0;
			parent[i] = i;
		} 
	}

	int Find(int x) {
		if (parent[x] == x) return x;
		return parent[x] = Find(parent[x]);
	}

	void Union(int x, int y) {
		x = Find(x);
		y = Find(y);

		if (x == y) return;
		
		if (rank[x] >= rank[y]) {
			parent[y] = x;
			if (rank[x] == rank[y])
				rank[x]++;
		}
		else {
			parent[x] = y;
		}
	}

	int count(int n) {
		int ret = 0;
		for (int i = 0; i < n; i++)
			ret += parent[i] == i;
		return ret;
	}
}dsu;

int main() {
	int n, m;
	while (~scanf("%d%d", &n, &m)) {
		if (n == 0 && m == 0) break;
		if (m == 0) {
			printf("%d\n", n - 1);
			continue;
		}
		bcc.init(n);
		dsu.init(n);
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			bcc.addEdge(a, b);
			dsu.Union(a, b);
		}
		int ret = bcc.solve();
		ret += dsu.count(n);
		printf("%d\n", ret);
	}
	return 0;
}

