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

#define maxV 20005
#define maxE 200005
#define th(x) this->x = x
int rmq[2*maxV];
struct ST {
	int mm[2*maxV];
	int best[20][2*maxV];
	void init(int n) {
		int i,j,a,b;
		mm[0]=-1;
		for(i=1; i<=n; i++) {
			mm[i]=((i&(i-1))==0)?mm[i-1]+1:mm[i-1];
			best[0][i]=i;
		}
		for(i=1; i<=mm[n]; i++) {
			for(j=1; j<=n+1-(1<<i); j++) {
				a=best[i-1][j];
				b=best[i-1][j+(1<<(i-1))];
				best[i][j]=rmq[a] < rmq[b]?a:b;
			}
		}
	}
	int query(int a, int b) {
		if(a > b)	swap(a, b);
		int t;
		t=mm[b-a+1];
		a=best[t][a];
		b=best[t][b-(1<<t)+1];
		return rmq[a] < rmq[b] ? a : b;
	}
};
//下面是LCA2RMQ开始
struct Nod {
	int b, nxt;
	void init(int b, int nxt) {
		th(b);	th(nxt);
	}
};
/**
	lca转化为rmq问题
	注意: 
		1.maxV为最大节点数, ST的数组和F、buf要设置为2*maxV!!!!!
		2.ST类为1开始，此类依然为0开始!
		3.F是欧拉序列,rmq是深度序列,P某点在欧拉序列中第一次出现的位置
*/
struct LCA2RMQ {
	int n;							//节点个数
	Nod buf[2*maxV];	int len;	int E[maxV];	//Tree	资源
	int V[2*maxV], route[maxV];				//路径的权，根到某点的路径和
	char vis[maxV];						//0没有访问，1正在访问
	
	ST st;							//Spare-Table...
	int F[2*maxV], P[maxV], cnt;	//介绍如上,cnt为计数器,lev为dfs时层数(减少递归栈大小)
	
	void init(int n) {
		th(n);
		len = 0;
		memset(E, 255, sizeof(E));
	}
	void addEdge(int a, int b, int v) {
		//cout << a << " " << b << " " << v << endl;
		buf[len].init(b, E[a]);		V[len] = v;		E[a] = len ++;
		buf[len].init(a, E[b]);		V[len] = v;		E[b] = len ++;
	}
	int query(int a, int b) {				//传入两个节点，返回他们lca节点编号
		return F[st.query(P[a], P[b])];
	}
	//1.【递归版】
	void dfs(int a, int lev) {
		vis[a] = 1;
		
		++ cnt;
		F[cnt] = a;
		rmq[cnt] = lev;
		P[a] = cnt;
		for(int i = E[a]; i != -1; i = buf[i].nxt) {
			if(vis[buf[i].b])	continue;
			route[buf[i].b] = route[a] + V[i];
			dfs(buf[i].b, lev+1);
			++ cnt;
			F[cnt] = a;
			rmq[cnt] = lev;
		}
	}
	void solve(int root) {
		memset(vis, 0, sizeof(vis));
		route[root] = cnt = 0;
		dfs(root, 0);
		st.init(2*n-1);
	}
	
	//2.【非递归版】
/*	void solve(int root) {
		static Nod stk[maxV];
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
		st.init(2*n-1);
	}*/
} lca;

struct Graph {
	vector<pair<int, int> > adj[maxV];
	int dfn[maxV], low[maxV];
	int edgeA[maxE], edgeB[maxE];
	bool vst[maxV];
	bool visit[maxE];
	int N, M, size, depth;
	int ret1, ret2;
	int idx[maxE];
	stack<int> S;
	vector<int> block;
	vector<int> vertex_bcc[maxV];
	vector<int> Bcc[maxV];

	void init(int n) {
		N = n;
		memset(vst, 0, sizeof(vst));
		memset(visit, 0, sizeof(visit));
		for (int i = 0; i < n; i++)
			adj[i].clear();
		for (int i = 0; i < n; i++)
			vertex_bcc[i].clear();
	}

	void addEdge(int u, int v, int id) {
		edgeA[id] = u; edgeB[id] = v;
		adj[u].PB(MP(v, id));
		adj[v].PB(MP(u, id));
	}

	void Tarjan(int u) {
	    dfn[u] = low[u] = depth++;
		//S.push(u);
		for (int i = 0; i < adj[u].size(); i++) {
			int v = adj[u][i].first;
			int id = adj[u][i].second;
			if (dfn[v] == -1) {
				S.push(id);
				visit[id] = true;//It's an undirected graph
				Tarjan(v);
				low[u] = min(low[u], low[v]);
				if (low[v] >= dfn[u]) {
					size++;
					Bcc[size].clear();
					int x;
					do {
						x = S.top(); S.pop();
						Bcc[size].PB(x); idx[x] = size;
						vertex_bcc[edgeA[x]].PB(size);
						vertex_bcc[edgeB[x]].PB(size);
					}while (x != id);
				}
	        } else if (!visit[id]) {
	        	if (dfn[v] < dfn[u]) S.push(id);
	            low[u] = min(low[u], dfn[v]);
	        }
	    }
	}

	void BCC() {
		depth = 0; size = 0;
		ret1 = ret2 = 0;
		while (!S.empty()) S.pop();
		for (int i = 0; i < N; i++)
			dfn[i] = -1;
	    for (int i = 0; i < N; i++)
		    if (dfn[i] == -1) Tarjan(i);
	}

	void build() {
		lca.init(N + 1);
		int root = 0;
		for (int i = 0; i < N; i++) {
			sort(vertex_bcc[i].begin(), vertex_bcc[i].end());
			vertex_bcc[i].resize(unique(vertex_bcc[i].begin(), vertex_bcc[i].end()) - vertex_bcc[i].begin());
			if (vertex_bcc[i].size() > 1) {
				size++;
				for (int j = 0; j < vertex_bcc[i].size(); j++) {
					int v = vertex_bcc[i][j];
					lca.addEdge(v, size, 1);
				}
				lca.addEdge(0, size, 0);
			}
		}
		lca.n = size + 1;
	}

}g;

//hdu3686
int n, m, q;
int main(int argc, char const *argv[])
{
	while (~scanf("%d%d", &n, &m) && n + m) {
		g.init(n);
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			g.addEdge(a - 1, b - 1, i);
		}
		g.BCC();
		g.build();
		lca.solve(0);
		scanf("%d", &q);
		while (q--) {
			int a, b;
			scanf("%d%d", &a, &b);
			a--; b--;
			a = g.idx[a]; b = g.idx[b];
			if (a == b) {
				printf("0\n");
			} else {
				int anc = lca.query(a, b);
				if (anc == 0) puts("0");
				else {
					int ret = lca.route[a] + lca.route[b] - 2 * lca.route[anc];
					printf("%d\n", ret / 2);
				}
			}
		}
	}
	return 0;
}