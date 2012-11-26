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
#define maxn 2000 + 10
#define maxm 10 * maxn
const int inf = 0x3f3f3f3f;
int N, M, K;
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
        if (maxFlow < K) minCost = -1;
        return minCost;
    }
} mc;
int main() {
	freopen("in", "r", stdin);
	int n, m, k;
	while (scanf("%d%d%d", &n, &m, &k) != EOF) {
		int source = 0, sink = 2 * n + 1;
		int sum = 0;
		mc.init(2 * n + 2);
		for (int i = 1; i <= n; i++) {
			int w;
			scanf("%d", &w);
			sum += w;
			mc.addCap(i, i + n, 1, -w);
			mc.addCap(i + n, sink, inf, 0);
			if (i + 1 <= n)
				mc.addCap(i, i + 1, inf, 0);
			if (i + m <= n)
				mc.addCap(i + n, i + m, inf, 0);
		}
		if (m <= k) {
			printf("%d\n", sum);
			continue;
		}
		mc.addCap(source, 1, k, 0);
		/*int tot = n - m + 2;
		int source = 0, sink = tot + 1;
		mc.init(tot + 2);
		for (int i = 1; i < tot; i++) {
			mc.addCap(i, i + 1, inf, 0);
		}
		mc.addCap(source, 1, k, 0);
		mc.addCap(tot, sink, k, 0);
		for (int i = 1; i <= n; i++) {
			int w;
			scanf("%d", &w);
			int from = max(1, i - m + 1), to = min(i, tot - 1) + 1;
			mc.addCap(from, to, 1, -w);
		}*/
		int ret = mc.solve(source, sink);
		printf("%d\n", -ret);
	}
	return 0;
}
