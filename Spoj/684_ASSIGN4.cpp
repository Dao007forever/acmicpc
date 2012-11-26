/*
 * Author: Yang Zhang
 * Created Time: Thu 30 Aug 2012 09:20:41 PM CST
 * File Name: 684_ASSIGN4.cpp
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
/*#define maxn 400 + 10
#define maxm 800 * maxn
const int inf = 0x3f3f3f3f;
struct Nod
{
    int b, nxt;
    int cap, cst;
    void init(int b, int nxt, int cap, int cst)
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
    void init(int n)
    {
        this->n = n;
        memset(E, 255, sizeof(E));
        len = 0;
    }
    void addCap(int a, int b, int cap, int cst)
    {
		//cout << a << " " << b << " " << cap << " " << cst << endl;
        buf[len].init(b, E[a], cap, cst); E[a] = len++;
        buf[len].init(a, E[b], 0, -cst); E[b] = len++;
    }
    bool spfa(int source, int sink)
    {
        static queue<int> Q;
        static int d[maxn];
        memset(d, 63, sizeof(d));
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
    int solve(int source, int sink)
    {
        int minCost = 0, maxFlow = 0;
        while (spfa(source, sink))
        {
            int neck = inf;
            for (int t = p[sink]; t != -1; t = p[buf[t ^ 1].b])
                neck = min(neck, buf[t].cap);
            maxFlow += neck;
            for (int t = p[sink]; t != -1; t = p[buf[t ^ 1].b])
            {
                buf[t].cap -= neck;
                buf[t ^ 1].cap += neck;
                minCost += buf[t].cst * neck;
            }
        }
		return minCost;
		//return make_pair(maxFlow, minCost);
    }
} mc;*/

#define maxn 405
#define maxm 200005
const int inf = 0x3f3f3f3f;
#define th(x) this->x = x
struct Nod {
	int b, cap, flow, cost, next;
	void init(int b, int cap, int cost, int next) {
		th(b);	th(cap);	th(cost);	th(next);
	}
};
struct ZKW {
	int E[maxn], n;	//图的所在
	int pi[maxn],source,sink,flow,cost;//顶标,源,汇,最大流,最小费
	bool vis[maxn];	//访问过吗？
	Nod buf[maxm];	int len;//资源
	void init(int n) {
		th(n);
		memset(E, 255, sizeof(E));
		len = 0;
	}
	void addCap(int i, int j, int cap, int cst) {
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
		int d = inf;
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
	int solve(int source, int sink) {
		th(source);	th(sink);
		flow = cost = 0;
		memset(pi, 0, sizeof(pi));
		for(int i = 0; i < len; i ++)	buf[i].flow = 0;
		do do memset(vis, 0, sizeof(vis));
			while(aug(source, inf));
		while(modLabel());
		return cost;
	}
}mc;

int main() {
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; Test--; cas++) {
		int n, m;
		scanf("%d%d", &n, &m);
		mc.init(n + m + 2);
		int source = 0, sink = n + m + 1;
		for (int i = 1; i <= n; i++) {
			int x;
			scanf("%d", &x);
			mc.addCap(source, i, x, 0);
		}
		for (int i = 1; i <= m; i++) {
			int x;
			scanf("%d", &x);
			mc.addCap(i + n, sink, x, 0);
		}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				int x;
				scanf("%d", &x);
				mc.addCap(i, j + n, inf, x);
			}
		int ret = mc.solve(source, sink);
		printf("%d\n", ret);
	}
	return 0;
}

