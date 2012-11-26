/*
 * Author: Yang Zhang
 * Created Time: Fri 24 Aug 2012 03:34:06 PM CST
 * File Name: 2435.cpp
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
const int MAXN = 100 + 10;
const int inf = 0x3f3f3f3f;
struct SAP
{
    int cap[MAXN][MAXN], flow[MAXN][MAXN], g[MAXN][MAXN];
    int n;
    int h[MAXN], vh[MAXN], source, sink;
    int mk[MAXN];
    void init(int n)
    {
        this->n = n;
        memset(cap, 0, sizeof(cap));
        memset(g, 0, sizeof(g));
        memset(mk, 0, sizeof(mk));
    }
    void addCap(int i, int j, int val)
    {
        cap[i][j] += val;
        g[i][j] = 1;
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
    void dfs(int u)//dfs找出从S开始的割集，mk[i]=1表示与S在同一个割集中
    {
        mk[u] = 1;
        for (int i = 0; i < n; i++)
        {
            if (!mk[i] && cap[u][i] - flow[u][i] > 0) dfs(i);
        }
    }
}sap;
int n, m;
int cap[MAXN][MAXN];
int f1[MAXN], f2[MAXN];
int src[MAXN], dst[MAXN], n1, n2;
void work() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			cap[i][j] = sap.cap[i][j] - sap.flow[i][j];
		}
	n1 = n2 = 0;
	for (int i = 0; i < n; i++)
		if (sap.mk[i]) {
			if (i != 0) {
				src[n1++] = i;
			}
		}
		else {
			if (i != n - 1) {
				dst[n2++] = i;
			}
		}
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				sap.cap[j][k] = cap[j][k];
		f1[i] = sap.solve(0, src[i]);
	}
	for (int i = 0; i < n2; i++) {
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				sap.cap[j][k] = cap[j][k];
		f2[i] = sap.solve(dst[i], n - 1);
	}
}
int main() {
    int Test;
    scanf("%d", &Test);
    while (Test--) {
		memset(f1, 0, sizeof(f1));
		memset(f2, 0, sizeof(f2));
		memset(cap, 0, sizeof(cap));
        scanf("%d%d", &n, &m);
        sap.init(n);
        for (int i = 0; i < m; i++) {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            a--; b--;
            sap.addCap(a, b, c);
        }
        int min_cut = sap.solve(0, n - 1);
		sap.dfs(0);
		work();
		int ret = min_cut;
		for (int i = 0; i < n1; i++)
			for (int j = 0; j < n2; j++) {
				int tmp = min_cut + min(f1[i], f2[j]);
				ret = max(ret, tmp);
			}
        printf("%d\n", ret);
    }
    return 0;
}

