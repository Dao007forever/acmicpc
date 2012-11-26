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
#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

#define maxn 300 + 10
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
    }
} mc;

int d[maxn][maxn];
int n, m, K;
const int temp = 1000000;
int prime(int x) {
	return x + n + 2;
}
int main(int argc, char const *argv[])
{
	while (~scanf("%d%d%d", &n, &m, &K)) {
		if (n == 0 && m == 0 && K == 0) break;
		memset(d, 63, sizeof(d));
		for (int i = 0; i <= n; i++) d[i][i] = 0;
		while (m--) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			if (c < d[a][b]) {
				d[a][b] = d[b][a] = c;
			}
		}
		for (int k = 0; k <= n; k++)
			for (int i = 0; i <= n; i++)
				for (int j = 0; j <= n; j++)
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
		mc.init(2*(n+2));
		mc.addCap(0, prime(0), K, 0);
		mc.addCap(n + 1, prime(n + 1), K, 0);
		mc.addCap(prime(0), n + 1, K, 0);
		for (int i = 1; i <= n; i++) {
			mc.addCap(i, prime(i), 1, -temp);
			mc.addCap(prime(0), i, 1, d[0][i]);
			mc.addCap(prime(i), n + 1, 1, d[i][0]);
			for (int j = i + 1; j <= n; j++)
				mc.addCap(prime(i), j, 1, d[i][j]);
		}
		int ret = mc.solve(0, 2*(n+2)-1);
		printf("%d\n", ret + temp * n);
	}
	return 0;
}