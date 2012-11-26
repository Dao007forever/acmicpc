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

#define maxn 100 + 10
#define maxm 80 * maxn
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
        if (maxFlow < 2) minCost = -1;
        return minCost;
    }
} mc;

int n, m;
int main() {
	freopen("in", "r", stdin);
	int cas = 1;
	while (scanf("%d%d", &n, &m) && n + m) {
		printf("Instance #%d: ", cas++);
		mc.init(2 * n + 2);
		mc.addCap(1, 1 + n, 2, 0);
		mc.addCap(n, n + n, 2, 0);
		for (int i = 2; i <= n - 1; i++) {
			mc.addCap(i, i + n, 1, 0);
		}
		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			a++; b++;
			mc.addCap(a + n, b, 1, c);
		}
		int source = 0, sink = 2 * n + 1;
		mc.addCap(source, 1, 2, 0);
		mc.addCap(2 * n, sink, 2, 0);
		int ret = mc.solve(source, sink);
		if (ret == -1) printf("Not possible\n");
		else printf("%d\n", ret);
	}
	return 0;
}
