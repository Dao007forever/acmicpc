/*
 * Author: Yang Zhang
 * Created Time: Mon 27 Aug 2012 02:23:04 PM CST
 * File Name: 5115_SPHIWAY.cpp
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
#define maxn 100000 + 10
#define maxm 400000 + 10
/*const LL inf = 1LL << 60;
struct Nod
{
    int b, nxt;
    int cap;
	LL cst;
    void init(int b, int nxt, int cap, LL cst)
    {
        this->b = b;
        this->nxt = nxt;
        this->cap = cap;
        this->cst = cst;
    }
};
struct MinCost
{
    int E[maxn], n;
    Nod buf[maxm * 2]; int len;

    int p[maxn];
    int pre[maxn], vis[maxn];
	LL d[maxn];
    void init(int n)
    {
        this->n = n;
        memset(E, 255, sizeof(E));
        len = 0;
    }
    void addCap(int a, int b, int cap, LL cst)
    {
        buf[len].init(b, E[a], cap, cst); E[a] = len++;
        buf[len].init(a, E[b], 0, -cst); E[b] = len++;
    }
    bool spfa(int source, int sink)
    {
        static queue<int> Q;
		for (int i = 0; i < n; i++)
			d[i] = inf;
        memset(p, 255, sizeof(p));
        memset(pre, -1, sizeof(pre));

        d[source] = 0;
        pre[source] = source;
        vis[source] = 1;
        Q.push(source);
        int u, v;
        while (!Q.empty())
        {
            u = Q.front();
            Q.pop();
            for (int i = E[u]; i != -1; i = buf[i].nxt)
            {
                v = buf[i].b;
                if (buf[i].cap > 0 && d[u] + buf[i].cst < d[v])
                {
                    d[v] = d[u] + buf[i].cst;
                    p[v] = i;
                    pre[v] = u;
                    if (!vis[v])
                    {
                        vis[v] = 1;
                        Q.push(v);
                    }
                }
            }
            vis[u] = 0;
        }
        return pre[sink] != -1 && d[sink] != inf;
    }
    pair<int, LL> solve(int source, int sink)
    {
        LL minCost = 0;
		int maxFlow = 0;
        while (spfa(source, sink))
        {
            int neck = 1<<29;
            for (int t = p[sink]; t != -1; t = p[buf[t ^ 1].b])
                neck = min(neck, buf[t].cap);
            maxFlow += neck;
            for (int t = p[sink]; t != -1; t = p[buf[t ^ 1].b])
            {
                buf[t].cap -= neck;
                buf[t ^ 1].cap += neck;
                minCost += buf[t].cst * (LL)neck;
            }
        }
		return make_pair(maxFlow, minCost);
    }
} mc;*/
#define th(x) this->x = x
const LL inf = 1ll<<60;
struct Nod {
	int b, cap, flow, next;
	LL cost;
	void init(int b, int cap, LL cost, int next) {
		th(b);	th(cap);	th(cost);	th(next);
	}
};
struct ZKW {
	int E[maxn], n;	//图的所在
	int source,sink,flow;//顶标,源,汇,最大流,最小费
	//int pi[maxn], cost;
	LL pi[maxn], cost;
	bool vis[maxn];	//访问过吗？
	Nod buf[maxm];	int len;//资源
	void init(int n) {
		th(n);
		memset(E, 255, sizeof(E));
		len = 0;
	}
	void addCap(int i, int j, int cap, LL cst) {
		buf[len].init(j, cap, cst, E[i]);
		E[i] = len ++;
		buf[len].init(i, 0, -cst, E[j]);
		E[j] = len ++;
	}
	int aug(int idx, int maxCap) {
		if(idx == sink) {
			cost+=pi[source]*maxCap;
			flow += maxCap;
			return maxCap;
		}
		vis[idx] = true;
		for(int i = E[idx]; i != -1; i = buf[i].next) {
			Nod & nod = buf[i];
			if(nod.cap-nod.flow>0&&!vis[nod.b]&&pi[nod.b]+nod.cost==pi[idx]){
				if(int d = aug(nod.b, min(maxCap, nod.cap-nod.flow))) {
					nod.flow += d;
					buf[i^1].flow -= d;
					return d;
				}
			}
		}
		return 0;
	}
	bool modLabel() {
		LL d = inf;
		for(int i = 0; i < n; i ++)	if(vis[i]) {
			for(int j = E[i]; j != -1; j = buf[j].next) {
				Nod & nod = buf[j];
				if(nod.cap-nod.flow>0 && !vis[nod.b]) {
					d = min(d, nod.cost-pi[i]+pi[nod.b]);
				}
			}
		}
		if(d == inf)	return false;
		for(int i = 0; i < n; i ++)	if(vis[i])	pi[i] += d;
		return true;
	}
	pair<int, int> solve(int source, int sink) {
		th(source);	th(sink);
		flow = cost = 0;
		memset(pi, 0, sizeof(pi));
		for(int i = 0; i < len; i ++)	buf[i].flow = 0;
		do do memset(vis, 0, sizeof(vis));
			while(aug(source, 1<<29));
		while(modLabel());
		return MP(flow, cost);
//		return cost;
	}
}mc;

int main() {
	int n, m, s, t;
	while (~scanf("%d%d%d%d", &n, &m, &s, &t)) {
		mc.init(n + 2);
		int source = 0, sink = n + 1;
		for (int i = 0; i < m; i++) {
			int u, v, w;
			scanf("%d%d%d", &u, &v, &w);
			mc.addCap(u, v, 1, w);
			mc.addCap(v, u, 1, w);
		}
		mc.addCap(source, s, 2, 0);
		mc.addCap(t, sink, 2, 0);
		pair<int, LL> ret = mc.solve(source, sink);
		if (ret.first < 2) puts("-1");
		else cout << ret.second << endl;
	}
	return 0;
}

