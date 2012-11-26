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
/*#define th(x) this->x = x
const int MAXN = 100000 + 10;
const int MAXM = 600000 + 10;
const int inf = 0x3f3f3f3f;
struct Nod
{
        int b, next;
        int cap, flow;
        void init(int b, int cap, int next)
        {
                th(b);
                th(cap);
                th(next);
        }
};
struct SAP
{
        int E[MAXN], n;
        int h[MAXN], vh[MAXN], source, sink;
        Nod buf[MAXM * 4]; int len;
        void init(int n)
        {
                this->n = n;
                len = 0;
                memset(E, 255, sizeof(E));
        }
        void addCap(int i, int j, int cap1, int cap2 = 0)
        {
                buf[len].init(j, cap1, E[i]);
                E[i] = len++;
                buf[len].init(i, cap2, E[j]);
                E[j] = len++;
        }
        int sap(const int idx, const int maxCap)
        {
                if (idx == sink)
                        return maxCap;
                int l = maxCap, d, minH = n;
                for (int i = E[idx]; i != -1; i = buf[i].next)
                {
                        Nod & nod = buf[i];
                        if (nod.cap-nod.flow > 0)
                        {
                                if (h[idx] == h[nod.b] + 1)
                                {
                                        d = sap(nod.b, min(l, nod.cap - nod.flow));
                                        nod.flow += d;
                                        buf[i ^ 1].flow -= d;
                                        l -= d;
                                        if (h[source] == n || l == 0) return maxCap - l;
                                }
                                minH = min(minH, h[nod.b] + 1);
                        }
                }
                if (l == maxCap)
                {
                        vh[h[idx]]--;
                        vh[minH]++;
                        if (vh[h[idx]] == 0)
                                h[source] = n;
                        h[idx] = minH;
                }
                return maxCap - l;
        }
        int solve(int source, int sink)
        {
                if (source == sink) return inf;
                th(source); th(sink);
                memset(h, 0, sizeof(h));
                memset(vh, 0, sizeof(vh));
                for (int i = 0; i < len; i++)
                        buf[i].flow = 0;
                int ans = 0;
                while (h[source] != n)
                        ans += sap(source, inf);
                return ans;
        }
}sap;*/
#define maxn1 50010
#define maxn2 50010
#define maxm 300010

struct Nod {
	int b, nxt;
	void init(int b, int nxt) {
		this->b = b;
		this->nxt = nxt;
	}
};
struct HK {
	int E[maxn1], n, m;			//图. n为V1中的点, m为V2中的点
	Nod buf[maxm];	int len;	//资源
	
	int dis1[maxn1], dis2[maxn2], mate1[maxn1], mate2[maxn2];
	//距离(初始0), 伙伴(初始-1)
	
	void init(int n, int m) {
		this->n = n;
		this->m = m;
		memset(E, 255, sizeof(E));
		len = 0;
	}
	void addEdge(int a, int b) {
		buf[len].init(b, E[a]);		E[a] = len ++;
	}
	
	bool bfs() {//bfs不改变mate, 只从新定dis!
		static queue<int> q;
		memset(dis1, 0, sizeof(dis1));
		memset(dis2, 0, sizeof(dis2));
		for(int i = 0; i < n; i ++) {
			if(mate1[i] == -1) {
				q.push(i);
			}
		}
		int a, b;
		bool found = false;
		while(!q.empty()) {
			a = q.front();	q.pop();
			for(int i = E[a]; i != -1; i = buf[i].nxt) {
				b = buf[i].b;
				if(dis2[b] == 0) {
					dis2[b] = dis1[a] + 1;
					if(mate2[b] == -1) {
						found = true;
					} else {
						dis1[mate2[b]] = dis2[b] + 1;
						q.push(mate2[b]);
					}
				}
			}
		}
		return found;
	}
	bool dfs(int a) {
		for(int i = E[a]; i != -1; i = buf[i].nxt) {
			int b = buf[i].b;
			if(dis1[a]+1==dis2[b]) {
				dis2[b] = 0;		//表示b点已经被访问过了!
				if(mate2[b] == -1 || dfs(mate2[b])) {//敲错耻辱
					mate1[a] = b;
					mate2[b] = a;
					return true;
				}
			}
		}
		return false;
	}
	
	int solve() {
		memset(mate1, 255, sizeof(mate1));
		memset(mate2, 255, sizeof(mate2));
		int ans = 0;
		while(bfs()) {
			for(int i = 0; i < n; i ++) {
				if(mate1[i]==-1 && dfs(i)) {
					ans ++;//每次只能加一,增广轨即交错轨,画画图就知道了
				}
			}
		}
		return ans;
	}
} hk;

int n, m, p;

int main()
{
	freopen("in", "r", stdin);
	scanf("%d%d%d", &n, &m, &p);
/*	sap.init(n + m + 2);
	int source = 0, sink = n + m + 1;
	for (int i = 1; i <= n; i++)
		sap.addCap(source, i, 1);
	for (int i = 1; i <= m; i++)
		sap.addCap(i + n, sink, 1);
	for (int i = 0; i < p; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		sap.addCap(u, v + n, 1);
	}
	int ret = sap.solve(source, sink);*/
	hk.init(n, m);
	for (int i = 0; i < p; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		u--; v--;
		hk.addEdge(u, v);
	}
	int ret = hk.solve();
	printf("%d\n", ret);
	return 0;
}

