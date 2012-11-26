/*
 * Author:  Yang Zhang
 * Created Time:  2012/8/9 23:36:17
 * File Name: 3947.cpp
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
#define maxm 800 * maxn
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
    pair<int, int> solve(int source, int sink)
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
        return MP(minCost, maxFlow);
    }
} mc;

int w[205], sumw[205];
int parent[205];
int n, m;

void work() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        parent[u] = v;
        scanf("%d", &w[u]);
    }
    mc.init(n + 2);
    int source = 0, sink = n + 1;
    int sum = 0;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int u, v, l, c;
        scanf("%d%d%d%d", &u, &v, &l, &c);
        mc.addCap(u, v, l, c);
    }
    for (int i = 2; i <= n; i++)
        mc.addCap(parent[i], i, inf, 0);

    memset(sumw, 0, sizeof(sumw));
    for (int i = 2; i <= n; i++)
        sumw[parent[i]] += w[i];
    //for (int i = 1; i <= n; i++)
        //cout << sumw[i] << " ";
    //cout << endl;
    w[1] = 0;
    for (int i = 1; i <= n; i++) {
        int cap = w[i] - sumw[i];
        if (cap > 0) {
            mc.addCap(source, i, cap, 0);
            sum += cap;
        } else if (cap < 0) {
            mc.addCap(i, sink, -cap, 0);
        }
    }
    pair<int, int> ret = mc.solve(source, sink);
    if (ret.second < sum) puts("-1");
    else printf("%d\n", ret.first);
}

int main() {
    freopen("in.txt", "r", stdin);
    int Test;
    scanf("%d", &Test);
    for (int cas = 1; cas <= Test; cas++) {
        printf("Case #%d: ", cas);
        work();
    }
    return 0;
}
