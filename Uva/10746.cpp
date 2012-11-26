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

const int maxn = 55;
const int maxm = 2222;
const double inf = 1e50;
const double eps =1e-8;
int N, M, K;
int sig(double d) {
	return (d > eps) - (d < -eps);
}
struct Nod
{
    int b, nxt;
    int cap;
	double cst;
    void init(int b, int nxt, int cap, double cst)
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
    void addCap(int a, int b, int cap, double cst)
    {
        buf[len].init(b, E[a], cap, cst); E[a] = len++;
        buf[len].init(a, E[b], 0, -cst); E[b] = len++;
    }
    bool spfa(int source, int sink)
    {
        static queue<int> Q;
        static double d[maxn];
		for (int i = 0; i <= n; i++)
			d[i] = inf;
        memset(p, 255, sizeof(p));
        memset(pre, -1, sizeof(pre));

        d[source] = 0.0;
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
        return pre[sink] != -1 && sig(d[sink] - inf) != 0;
    }
    double solve(int source, int sink)
    {
        double minCost = 0;
		int maxFlow = 0;
        while (spfa(source, sink))
        {
            int neck = 1 << 30;
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
    }
} mc;

int n, m;
int main() {
	freopen("in", "r", stdin);
	while (cin >> n >> m) {
		if (n == 0 && m == 0) break;
		mc.init(n + m + 2);
		int source = 0, sink = n + m + 1;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				double x;
				cin >> x;
				mc.addCap(i, n + j, 1, x);
			}
		for (int i = 1; i <= n; i++)
			mc.addCap(source, i, 1, 0.0);
		for (int i = 1; i <= m; i++)
			mc.addCap(n + i, sink, 1, 0.0);
		double ret = mc.solve(source, sink);
		printf("%.2f\n", ret / (double)n + 0.000005);
	}
	return 0;
}
