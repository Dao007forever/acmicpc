/*
 * Author: Yang Zhang
 * Created Time: Fri 17 Aug 2012 08:07:53 PM UTC
 * File Name: 3228.cpp
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
const int MAXN = 400 + 10;
const int inf = 0x3f3f3f3f;
struct SAP
{
    int cap[MAXN][MAXN], flow[MAXN][MAXN], g[MAXN][MAXN];
    int n;
    int h[MAXN], vh[MAXN], source, sink;
    void init(int n)
    {
        this->n = n;
        memset(cap, 0, sizeof(cap));
    }
    void addCap(int i, int j, int val)
    {
        cap[i][j] += val;
    }
    int sap(const int idx, const int maxCap)
    {
        if (idx == sink)
            return maxCap;
        int l = maxCap, d, minH = n;
        for (int i = 0; i < n; i++)
        {
            if (cap[idx][i] - flow[idx][i] > 0)
            {
                if (h[idx] == h[i] + 1)
                {
                    d = sap(i, min(l, cap[idx][i] - flow[idx][i]));
                    flow[idx][i] += d;
                    flow[i][idx] -= d;
                    l -= d;
                    if (h[source] == n || l == 0) return maxCap - l;
                }
                minH = min(minH, h[i] + 1);
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
        this->sink = sink;
        this->source = source;
        memset(flow, 0, sizeof(flow));
        memset(h, 0, sizeof(h));
        memset(vh, 0, sizeof(vh));
        int ans = 0;
        while (h[source] != n)
            ans += sap(source, inf);
        return ans;
    }
}sap;
int n, m, sumGold;
int gold[MAXN], store[MAXN];
struct edge {
	int u, v, d;
}edge[MAXN * MAXN];
bool check(int lim) {
	sap.init(n + 2);
	int source = 0, sink = n + 1;
	for (int i = 1; i <= n; i++) {
		sap.addCap(source, i, gold[i]);
		sap.addCap(i, sink, store[i]);
	}
	for (int i = 0; i < m; i++)
		if (edge[i].d <= lim) {
			int u = edge[i].u, v = edge[i].v;
			sap.addCap(u, v, inf);
			sap.addCap(v, u, inf);
		}
	int flow = sap.solve(source, sink);
	return flow >= sumGold;
}
int main() {
	while (scanf("%d", &n) && n) {
		sumGold = 0;
		for (int i = 1; i <= n; i++)
			scanf("%d", &gold[i]), sumGold += gold[i];
		for (int i = 1; i <= n; i++)
			scanf("%d", &store[i]);
		scanf("%d", &m);
		int sum = 0;
		for (int i = 0; i < m; i++) {
			scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].d);
			sum += edge[i].d;
		}
		int l = 0, r = sum, ret = -1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (check(mid)) {
				r = mid - 1;
				ret = mid;
			} else l = mid + 1;
		}
		if (ret == -1) puts("No Solution");
		else printf("%d\n", ret);
	}
	return 0;
}

