/*
 * 已知一个矩阵每行和每列的和，求这个矩阵是否存在，存在输出一种解
 * 最大流，行列分别为点，每行每每列连一条容量为100的边，源点向每行连一条容量为该行的和的边，每列向汇点连一条容量为该列的和的边，最后判断最大流是否等于总和
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 200 + 10;
const int inf = 0x3f3f3f3f;
int N;
int R[maxn], C[maxn];
struct SAP
{
    int cap[maxn][maxn], flow[maxn][maxn], g[maxn][maxn];
    int n;
    int h[maxn], vh[maxn], source, sink;
    int mk[maxn];
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
	void output() {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j < N; j++)
				printf("%d ", flow[i][N + j]);
			printf("%d\n", flow[i][N + N]);
		}		
	}
}sap;

int main()
{
	freopen("in.txt", "r", stdin);
	cin >> N;
	int Sum = 0;
	for (int i = 1; i <= N; i++)
		cin >> R[i], Sum += R[i];
	for (int i = 1; i <= N; i++)
		cin >> C[i];
	int source = 0, sink = N + N + 1;
	sap.init(N + N + 2);
	for (int i = 1; i <= N; i++) {
		sap.addCap(source, i, R[i]);
		sap.addCap(N + i, sink, C[i]);
	}
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++) {
			sap.addCap(i, N + j, 100);
		}
	int ret = sap.solve(source, sink);
	if (ret == Sum) {
		puts("YES");
		sap.output();
	} else {
		puts("NO");
	}
	return 0;
}
