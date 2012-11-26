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

const int MAXN = 500 + 10;
const int MAXM = 2000 + 10;
const double eps = 1e-8;
const double inf = 1e7;
double dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

struct Nod
{
	int b, next;
	double cap, flow;
	void init(int b, double cap, int next)
	{
		th(b); th(cap); th(next);
	}
};
struct SAP
{
	int E[MAXN], n;
	int h[MAXN], vh[MAXN], source, sink;
	int V[MAXN];
	Nod buf[MAXM]; int len;

	void init(int n)
    {
		this->n = n;
		len = 0;
        memset(E, 255, sizeof(E));
    }
    void addCap(int i, int j, double cap1, double cap2 = 0)
    {
		buf[len].init(j, cap1, E[i]);
        E[i] = len++;
        buf[len].init(i, cap2, E[j]);
        E[j] = len++;
    }
    double sap(const int idx, const double maxCap)
    {
		if (idx == sink) return maxCap;
        double l = maxCap, d;
		int minH = n;
        for (int i = E[idx]; i != -1; i = buf[i].next)
        {
			Nod & nod = buf[i];
            if (dblcmp(nod.cap-nod.flow) > 0)
            {
				if (h[idx] == h[nod.b] + 1)
                {
					d = sap(nod.b, min(l, nod.cap - nod.flow));
                    nod.flow += d;
                    buf[i ^ 1].flow -= d;
                    l -= d;
                    if (h[source] == n || dblcmp(l) == 0) return maxCap - l;
                }
                minH = min(minH, h[nod.b] + 1);
            }
        }
        if (dblcmp(l - maxCap) == 0)
        {
			vh[h[idx]]--;
            vh[minH]++;
            if (vh[h[idx]] == 0)
				h[source] = n;
            h[idx] = minH;
        }
        return maxCap - l;
    }
	double solve(int source, int sink)
    {
		if (source == sink) return inf;
        th(source); th(sink);
        memset(h, 0, sizeof(h));
        memset(vh, 0, sizeof(vh));
        for (int i = 0; i < len; i++)
			buf[i].flow = 0;
		double ans = 0;
        while (h[source] != n)
			ans += sap(source, inf);
		return ans;
    }

	void initV()
	{
		memset(V, 0, sizeof(V));
	}

	void DFS(int idx)
	{
		V[idx] = true;
		for (int i = E[idx]; i != -1; i = buf[i].next)
		{
			if (buf[i].cap - buf[i].flow > 0 && !V[buf[i].b])
				DFS(buf[i].b);
		}
	}
};

SAP sap;
int N, M;
int edge[MAXM][3];
bool ok[MAXM];

double Calc(double lim)
{
	double res = 0;
	sap.init(N);
	for (int i = 0; i < M; i++)
	if (dblcmp(edge[i][2] - lim) <= 0) res += edge[i][2] - lim;
	else 
	{
		int u = edge[i][0] - 1, v = edge[i][1] - 1;
		double w = edge[i][2] - lim;
		sap.addCap(u, v, w, w);
	}
	return res += sap.solve(0, N - 1);
}

int main()
{
	freopen("a", "r", stdin);
	while (cin >> N >> M)
	{
		double Left = 1e30, Right = 0;
		for (int i = 0; i < M; i++)
		{
			cin >> edge[i][0] >> edge[i][1] >> edge[i][2];
			if (edge[i][2] < Left) Left = edge[i][2];
			if (edge[i][2] > Right) Right = edge[i][2];
		}

		double Mid;
		while (1)
		{
			Mid = (Left + Right) / 2;
			double tmp = Calc(Mid);
			if (dblcmp(tmp) == 0) break;
			if (dblcmp(tmp) > 0) Left = Mid;
			else Right = Mid;
		}

		Calc(Mid);
		sap.initV();
		sap.DFS(0);
		memset(ok, 0, sizeof(ok));
		int ans = 0, last;
		for (int i = 0; i < M; i++)
		if (edge[i][2] <= Mid || sap.V[edge[i][0] - 1] != sap.V[edge[i][1] - 1])
		{
			ok[i] = true;
			++ans;
			last = i;
		}
		printf("%d\n", ans);
		for (int i = 0; i < last; i++)
		if (ok[i]) printf("%d ", i + 1);
		printf("%d\n", last + 1);
		printf("\n");
	}
	return 0;
}
