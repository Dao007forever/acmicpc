/*
 * Author:  Yang Zhang
 * Created Time:  2012/8/12 20:27:30
 * File Name: 1515.cpp
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
/**
 * 求解双连通分支！两点之间可以有重边，这样的话会将两点设为一个连通分支里面，但还是要甚用重边！
 * 所点后的树不会有重边！！
 * 缩点后的树的边也是关于^对偶
 * 判断某边是否为桥的方法是：id[a]!=id[b]并且brg[该边]=壹
 * 并查集+LCA也可以解决双连通分支，而且是动态的！
 */
#define maxn 1010
#define maxm 10100
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
	bool cut[maxn];						///某点是否为割点
	int id[maxn];						///某点所在分支的编号
	
	int EBcc[maxn];		int nBcc;		///缩点后的图
	Nod bufBcc[maxn*2];	int lenBcc;		///缩点后的资源2*maxn足够！
	int tot[maxn];						///某个bcc包含的点数
	//以上变量可能会被solve后使用
	char vis[maxn];	///visited（0未访问，壹在访问，2访问完）
    bool vst[maxn][maxn];
	
	void init(int n) {
		this->n = n;
		memset(E, 255, sizeof(E));
        memset(vst, 0, sizeof(vst));
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
		for(int i=0; i<n; i++)	tot[id[i]] ++;
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
		}
			///所点后的图构建完毕，不含重边！
	}

    void dfs(int u) {
        for (int i = E[u]; i != -1; i = buf[i].nxt) {
            int v = buf[i].b;
            if (vst[u][v]) continue;
            vst[u][v] = vst[v][u] = true;
            if (id[u] == id[v]) {
                printf("%d %d\n", u + 1, v + 1);
            } else {
                printf("%d %d\n", u + 1, v + 1);
                printf("%d %d\n", v + 1, u + 1);
            }
            dfs(v);
        }
    }
} bcc;

int n, m;
int main() {
    freopen("in.txt", "r", stdin);
    int cas = 1;
    while (scanf("%d%d", &n, &m) && n) {
        bcc.init(n);
        for (int i = 1; i <= m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            bcc.addEdge(u - 1, v - 1);
        }
        bcc.solve();
        printf("%d\n\n", cas++);
        bcc.dfs(0);
        puts("#");
    }
    return 0;
}

