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

const int MAXN = 200 + 10;
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

int x[111], y[111];
bool inter(int a, int b, int d) {
	int dx = abs(x[a] - x[b]), dy = abs(y[a] - y[b]);
	if (dx * dx + dy * dy <= d * d) return true;
	return false;
}

int main() {
	freopen("in", "r", stdin);
	int L, W, N, d;
	int cas = 1;
	while (scanf("%d%d%d%d", &L, &W, &N, &d) && L + W + N + d) {
		printf("Case %d: ", cas++);
		for (int i = 1; i <= N; i++) {
			scanf("%d%d", &x[i], &y[i]);
		}

		int source = 0, sink = 2 * N + 1;
		sap.init(2 * N + 2);
		for (int i = 1; i <= N; i++) {
			sap.addCap(i, i + N, 1);
			if (y[i] - d <= 0) sap.addCap(source, i, inf);
			if (y[i] + d >= W) sap.addCap(i + N, sink, inf);
		}
		for (int i = 1; i <= N; i++)
			for (int j = i + 1; j <= N; j++) {
				if (inter(i, j, 2 * d)) {
					sap.addCap(i + N, j, inf);
					sap.addCap(j + N, i, inf);
				}
			}
		int ret = sap.solve(source, sink);
		printf("%d\n", ret);
	}
	return 0;
}
