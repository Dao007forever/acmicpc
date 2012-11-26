/*
 * Author: Yang Zhang
 * Created Time: Sat 25 Aug 2012 02:41:16 PM CST
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

#define maxn 88
int n;
char mat[maxn][maxn];
bool adj[maxn][maxn];
int mk[maxn], cx[maxn], cy[maxn];

int dfs(int u) {
	for (int v = 0; v < n; v++)
		if (adj[u][v] && !mk[v]) {
			mk[v] = 1;
			if (cy[v] == -1 || dfs(cy[v])) {
				cx[u] = v;
				cy[v] = u;
				return 1;
			}
		}
	return 0;
}

int maxMatch() {
	int ret = 0;
	memset(cx, -1, sizeof(cx));
	memset(cy, -1, sizeof(cy));
	for (int i = 0; i < n; i++)
		if (cx[i] == -1) {
			memset(mk, 0, sizeof(mk));
			ret += dfs(i);
		}
	return ret;
}

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
    }
    void addCap(int i, int j, int val)
    {
        cap[i][j] = val;
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

bool check(int k) {
	int source = n + n, sink = n + n + 1;
	for (int i = 0; i < n; i++) {
		sap.cap[source][i] = k;
		sap.cap[n + i][sink] = k;
	}
	int maxflow = sap.solve(source, sink);
	return maxflow == n * k;
}

int ans[88];
int main() {
	while (scanf("%d", &n) && n) {
		sap.init(n + n + 2);
		for (int i = 0; i < n; i++) {
			scanf("%s", mat[i]);
			for (int j = 0; j < n; j++) {
				if (mat[i][j] == 'Y') {
					sap.cap[i][j + n] = 1;
				} else {
					sap.cap[i][j + n] = 0;
				}
			}
		}
		int ret = 0;
		int l = 0, r = n;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (check(mid)) {
				ret = mid;
				l = mid + 1;
			} else r = mid - 1;
		}
		check(ret);
		memset(adj, 0, sizeof(adj));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				adj[i][j] = (sap.cap[i][j + n] == 1 && sap.flow[i][j + n] == 1);
		printf("%d\n", ret);
		for (int i = 0; i < ret; i++) {
			memset(ans, 0, sizeof(ans));
			maxMatch();
			for (int i = 0; i < n; i++) {
				ans[cx[i]] = i + 1;
				adj[i][cx[i]] = false;
			}
			for (int i = 0; i < n; i++)
				printf("%d%c", ans[i], i == n - 1 ? '\n' : ' ');
		}
	}
	return 0;
}

