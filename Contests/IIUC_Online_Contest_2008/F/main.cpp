/*
 * Author: Yang Zhang
 * Created Time: Fri 01 Jun 2012 07:23:25 PM UTC
 * File Name: main.cpp
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
}sap;
int main() {
	int Test;
	scanf("%d", &Test);
	int n;
	for (int cas = 1; cas <= Test; cas++) {
		printf("Case #%d: ", cas);
		scanf("%d", &n);
		sap.init(n + 2);
		int source = 0, sink = n + 1, sum = 0;
		for (int i = 1; i <= n; i++) {
			int x, k;
			scanf("%d", &x);
			if (x > 0) {
				sap.addCap(source, i, x);
				sum += x;
			}
			else sap.addCap(i, sink, -x);
			scanf("%d", &k);
			while (k--) {
				int j;
				scanf("%d", &j);
				sap.addCap(i, j, inf);
				//sap.addCap(j, i, inf);
			}
		}
		int ret = sap.solve(source, sink);
		if (sum - ret <= 0) puts("Alas, sultan can't invite anyone!");
		else printf("%d\n", sum - ret);
	}
	return 0;
}
