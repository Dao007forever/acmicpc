#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

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

int K, N, M, S, F;

int main()
{
	freopen("in.txt", "r", stdin);
	cin >> K;
	cin >> N >> M >> S >> F;
	S--; F--;
	sap.init(2 * N);
	for (int i = 0; i < N; i++) {
		int x;
		cin >> x;
		sap.addCap(2 * i, 2 * i + 1, x);
		sap.addCap(2 * i + 1, 2 * i, x);
	}
	while (M--) {
		int u, v;
		cin >> u >> v;
		u--; v--;
		sap.addCap(2 * u + 1, 2 * v, inf);
		sap.addCap(2 * v + 1, 2 * u, inf);
	}
	int source = 2 * S + 1, sink = 2 * F;
	int ret = sap.solve(source, sink);
	if (ret > K || S == F)
		puts("NO");
	else puts("YES");
	return 0;
}
