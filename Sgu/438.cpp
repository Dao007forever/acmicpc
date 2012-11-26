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
const int MAXN = 300000 + 10;
const int MAXM = 4000000 + 10;
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
};
SAP sap;
int N, M, D, W;
struct Point
{
	int x, y, c;
}P[55];
int w[55][55];

int dist(Point a, Point b)
{
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

void Build(int mid)
{
	int source = 2 * N * mid + 1, sink = 2 * N * mid + 2;
	sap.init(2 * N * mid + 3);
	sap.addCap(0, source, M);
	if (D >= W) sap.addCap(source, sink, M);
	for (int k = 0; k < mid; k++)
	for (int i = 0; i < N; i++)
	{
		sap.addCap(2 * k * N + i + 1, 2 * k * N + N + i + 1, P[i].c);
		if (P[i].y <= D) sap.addCap(source, 2 * k * N + i + 1, inf);
		if (P[i].y + D >= W) sap.addCap(2 * k * N + N + i + 1, sink, inf);
	}
	for (int i = 1; i <= N; i++)
	for (int j = 1; j <= N; j++)
	if (w[i][j] <= D * D)
	{
		for (int k = 0; k < mid - 1; k++)
			sap.addCap(2 * k * N + N + i, 2 * (k + 1) * N + j, inf);
	}
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d%d%d", &N, &M, &D, &W);
	for (int i = 0; i < N; i++)
	{
		scanf("%d%d%d", &P[i].x, &P[i].y, &P[i].c);
	}
	for (int i = 0; i < N; i++)
	for (int j = 0; j < N; j++)
	{
		w[i + 1][j + 1] = dist(P[i], P[j]);
	}
	int Left = 1, Right = N + M + 1;
	while (Left < Right)
	{
		int Mid = (Left + Right) / 2;
		Build(Mid - 1);
		int source = 0, sink = 2 * N * (Mid - 1) + 2;
		int tmp = sap.solve(source, sink);
		if (tmp == M) Right = Mid;
		else Left = Mid + 1;
	}
	if (Left <= M + N) printf("%d\n", Left);
	else puts("IMPOSSIBLE");
	return 0;
}
