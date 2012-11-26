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

#define maxn 100005
#define maxm 400005
#define maxq 400005
#define th(x) this->x = x
//【迷你并查集】
int p[maxn];
void make() {
	memset(p, 255, sizeof(p));
}
int find(int x) {
	int px, i;
	for(px = x; p[px] != -1; px = p[px]);
	while(x != px) {
		i = p[x];
		p[x] = px;
		x = i;
	}
	return px;
}
void unio(int x, int y) {	//让x成为y的父亲, 断言不会出现冲突情况
	p[find(y)] = find(x);
}
//下面是Tarjan开始
struct Nod {
	int b, nxt;
	void init(int b, int nxt) {
		th(b);	th(nxt);
	}
};
struct Tarjan {
	int n;
	Nod bufT[2*maxn];	int lenT;	int ET[maxn];	//Tree	资源
	Nod bufQ[2*maxq];	int lenQ;	int EQ[maxn];	//Query	询问
	
	int V[2*maxn], route[maxn];					//路径的权，根到某点的路径和
	
	int ans[maxq];							//保存最后的结果，按照输入顺序保存
	char vis[maxn];							//0没有访问，1正在访问，2访问过

	int val[maxn], sum[maxn];
	
	void init(int n) {
		th(n);
		lenT = 0;	memset(ET, 255, sizeof(ET));
		lenQ = 0;	memset(EQ, 255, sizeof(EQ));
	}
	void addEdge(int a, int b, int v) {
		bufT[lenT].init(b, ET[a]);	V[lenT]=v;	ET[a] = lenT ++;
		bufT[lenT].init(a, ET[b]);	V[lenT]=v;	ET[b] = lenT ++;
	}
	void addQuery(int a, int b) {
		bufQ[lenQ].init(b, EQ[a]);				EQ[a] = lenQ ++;
		bufQ[lenQ].init(a, EQ[b]);				EQ[b] = lenQ ++;
	}
	//1.【递归版】
	void dfs(int a) {
		vis[a] = 1;
		
		for(int i = ET[a]; i != -1; i = bufT[i].nxt) {
			if(vis[bufT[i].b])	continue;
			route[bufT[i].b] = route[a] + V[i];	//update route!
			dfs(bufT[i].b);
			unio(a, bufT[i].b);
		}
		vis[a] = 2;
		for(int i = EQ[a]; i != -1; i = bufQ[i].nxt) {
			if(vis[bufQ[i].b] == 2) {
				ans[i/2] = find(bufQ[i].b);		// i/2 is the real order!
			}
		}
	}
	void bfs(int st) {
		memset(vis, 0, sizeof(vis));
		queue<int> q;
		q.push(st);
		sum[st] = val[st];
		while (!q.empty()) {
			int u = q.front(); q.pop();
			vis[u] = true;
			for (int i = ET[u]; i != -1; i = bufT[i].nxt) {
				int b = bufT[i].b;
				if (!vis[b]) {
					q.push(b);
					sum[b] = sum[u] + val[b];
				}
			}
		}
	}
	void solve(int root) {
		route[root] = 0;						//update route!
		make();
		memset(vis, 0, sizeof(vis));
		dfs(root);
	}
} tar;

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
/*		for(int j = 0; j < n; j ++) {
			int a = id[j];
			for(int i = E[j]; i != -1; i = buf[i].nxt) {
				int b = id[buf[i].b];
				if(brg[i] && a<b) {
					bufBcc[lenBcc].init(b, EBcc[a]);	EBcc[a] = lenBcc ++;
					bufBcc[lenBcc].init(a, EBcc[b]);	EBcc[b] = lenBcc ++;
				}
			}
		}
*/			///所点后的图构建完毕，不含重边！
	}

} bcc;

const LL mod = 1000000007;
LL quickPow(LL p, int x) {
	LL ret = 1;
	for (; x; x >>= 1) {
		if (x & 1) ret = ret * p % mod;
		p = p * p % mod;
	}
	return ret;
}

vector<pair<int, int> > query;
int main(int argc, char const *argv[])
{
	freopen("input.txt", "r", stdin);
	int n, m, q;
	scanf("%d%d", &n, &m);
	bcc.init(n);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d%d", &a, &b);
		a--; b--;
		bcc.addEdge(a, b);
	}
	bcc.solve();
	tar.init(bcc.nBcc);
	for (int j = 0; j < n; j++) {
		int a = bcc.id[j];
		for (int i = bcc.E[j]; i != -1; i = bcc.buf[i].nxt) {
			int b = bcc.id[bcc.buf[i].b];
			if (bcc.brg[i] && a < b) {
				tar.addEdge(a, b, 0);
				//cout << a << " " << b << endl;
			}
		}
	}
	for (int i = 0; i < bcc.nBcc; i++)
		tar.val[i] = (bcc.tot[i] > 2);
	scanf("%d", &q);
	for (int i = 0; i < q; i++) {
		int a, b;
		scanf("%d%d", &a, &b);
		a--; b--;
		query.PB(MP(a, b));
		tar.addQuery(bcc.id[a], bcc.id[b]);
	}
	tar.solve(0);
	tar.bfs(0);
	for (int i = 0; i < q; i++) {
		int anc = tar.ans[i];
		int a = bcc.id[query[i].first], b = bcc.id[query[i].second];
		if (a == b) {
			cout << 2 << endl;
		} else {
			int cnt = tar.sum[a] + tar.sum[b] - 2 * tar.sum[anc] + tar.val[anc];
			LL ret = quickPow(2, cnt);
			cout << ret << endl;
			//cout << cnt << " " << ret << endl;
		}
	}
	return 0;
}