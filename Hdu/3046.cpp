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

#define th(x) this->x = x;
const int MAXN = 40000 + 10;
const int MAXM = 400000 + 10;
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
int dx[4] = {0, 0, -1, 1};
int dy[4] = {1, -1, 0, 0};
int N, M;
int a[255][255];

int ID(int i, int j)
{
	return (i - 1) * M + j;
}

int main()
{
	freopen("a", "r", stdin);
	int cas = 0;
	while (scanf("%d%d", &N, &M) != EOF)
	{
		cas++;
		printf("Case %d:\n", cas);
		for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
		{
			scanf("%d", &a[i][j]);
		}
		sap.init(N * M + 2);
		int source = 0, sink = N * M + 1;
		for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				int x = i + dx[k], y = j + dy[k];
				if (x >= 1 && x <= N && y >= 1 && y <= M)
				{
					sap.addCap(ID(i, j), ID(x, y), 1);
				}
			}
			if (a[i][j] == 1)
			{
				sap.addCap(ID(i, j), sink, inf);
			}
			else if (a[i][j] == 2)
			{
				sap.addCap(source, ID(i, j), inf);
			}else if (a[i][j] == 0) continue;
		}
		cout << sap.solve(source, sink) << endl;
	}
	return 0;
}
