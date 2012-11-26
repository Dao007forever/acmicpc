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
#define th(x) this->x = x

const int MAXN = 400 + 10;
const int MAXM = 100000 + 10;
const int inf = 0x3f3f3f3f;
const long long Inf = 200000000000LL;
int N, M, tot;
int a[MAXN], b[MAXN];
long long dis[MAXN][MAXN];

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
};

SAP sap;

bool Check(long long lim)
{
	sap.init(2 * N + 2);
	int source = 0, sink = 2 * N + 1;
	for (int i = 1; i <= N; i++)
	{
		sap.addCap(source, i, a[i]);
		sap.addCap(N + i, sink, b[i]);
	}
	for (int i = 1; i <= N; i++)
	for (int j = 1; j <= N; j++)
	if (dis[i][j] <= lim)
	{
		sap.addCap(i, N + j, inf);
		sap.addCap(j, N + i, inf);
	}
	int maxflow = sap.solve(source, sink);
	return maxflow == tot;
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d", &N, &M);
	tot = 0;
	for (int i = 1; i <= N; i++)
	{
		scanf("%d%d", &a[i], &b[i]);
		tot += a[i];
	}
	for (int i = 1; i <= N; i++)
	for (int j = 1; j <= N; j++)
	if (i != j)
	{
		dis[i][j] = Inf;
	}
	for (int i = 1; i <= M; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		if (w < dis[u][v] || dis[u][v] == -1)
			dis[u][v] = dis[v][u] = w;
	}
	for (int k = 1; k <= N; k++)
	for (int i = 1; i <= N; i++)
	for (int j = 1; j <= N; j++)
	if (dis[i][k] + dis[k][j] < dis[i][j])
		dis[i][j] = dis[i][k] + dis[k][j];
	long long Left = 0, Right = Inf + 5LL;
	while (Left <= Right)
	{
		long long Mid = (Left + Right) / 2;
		if (!Check(Mid)) Left = Mid + 1;
		else Right = Mid - 1;
	}
	if (Left < Inf) cout << Left << endl;
	else cout << -1 << endl;
	return 0;
}
