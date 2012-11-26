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
		//cout << i << " " << j << " " << val << endl;
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

int a[10005], b[10005], c[10005];
bool in[105], out[105];
int n, m, g;

bool check(int lim) {
	sap.init(n + 2);
	int source = 0, sink = n + 1;
	for (int i = 1; i <= n; i++) {
		if (in[i]) sap.addCap(source, i, inf);
		if (out[i]) sap.addCap(i, sink, inf);
	}
	for (int i = 0; i < m; i++) {
		if (c[i] <= lim) {
			sap.addCap(a[i], b[i], c[i]);
			sap.addCap(b[i], a[i], c[i]);
		}
	}
	int ret = sap.solve(source, sink);
	return ret >= g;
}

int main() {
	freopen("in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		int K, L;
		memset(in, 0, sizeof(in));
		memset(out, 0, sizeof(out));
		scanf("%d%d%d%d%d", &n, &m, &K, &L, &g);
		for (int i = 0; i < m; i++)
			scanf("%d%d%d", &a[i], &b[i], &c[i]);
		for (int i = 0, x; i < K; i++) {
			scanf("%d", &x);
			in[x] = true;
		}
		for (int i = 0, x; i < L; i++) {
			scanf("%d", &x);
			out[x] = true;
		}

		int l = 0, r = 1000000, ret = -1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (check(mid)) {
				ret = mid;
				r = mid - 1;
			} else l = mid + 1;
		}
		printf("%d\n", ret * 100);
	}
	return 0;
}
