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

#define maxn 100 + 10
#define maxm 800 * maxn
const long long inf = (long long)1e16;
struct Path
{
	int a, b, c;
}p[55555];
int N, M;
long long amount, cap;
struct Nod
{
    int b, nxt;
    long long cap, cst;
    void init(int b, int nxt, long long cap, long long cst)
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
    void addCap(int a, int b, long long cap, long long cst)
    {
        buf[len].init(b, E[a], cap, cst); E[a] = len++;
        buf[len].init(a, E[b], 0, -cst); E[b] = len++;
    }
    bool spfa(int source, int sink)
    {
        static queue<int> Q;
        static long long d[maxn];
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
    long long solve(int source, int sink)
    {
        long long minCost = 0, maxFlow = 0;
        while (spfa(source, sink))
        {
            long long neck = inf;
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
        if (maxFlow != amount) minCost = -1;
        return minCost;
    }
} mc;

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d%d", &N, &M) != EOF)
	{
		int source = 0, sink = N + 1;
		mc.init(N + 2);
		for (int i = 1; i <= M; i++)
			scanf("%d%d%d", &p[i].a, &p[i].b, &p[i].c);
		cin >> amount >> cap;

		mc.addCap(source, 1, amount, 0);
		mc.addCap(N, sink, amount, 0);
		for (int i = 1; i <= M; i++)
		{
			mc.addCap(p[i].a, p[i].b, cap, p[i].c);
			mc.addCap(p[i].b, p[i].a, cap, p[i].c);
			//cout << p[i].a << " " << p[i].b << " " << cap << " " << p[i].c << endl;
			//cout << p[i].b << " " << p[i].a << " " << cap << " " << p[i].c << endl;
		}
		long long ans = mc.solve(source, sink);
		if (ans == -1) printf("Impossible.\n");
		else cout << ans << endl;
	}
	return 0;
}
