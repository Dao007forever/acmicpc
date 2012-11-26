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
const int MAXN = 500 + 10;
const int MAXM = 100000 + 10;
const int inf = 0x3f3f3f3f;
int N, M;
int res[MAXN][3];
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
        Nod buf[MAXM]; int len;
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
		void dfs()
		{
			for (int i = 1; i <= N; i++)
			{
				for (int j = E[i]; j != -1; j = buf[j].next)
				{
					if (buf[j].cap - buf[j].flow == 0)
					{
						int v = buf[j].b - N;
						if (res[v][0] < 2)
						{
							res[v][0]++;
							res[v][res[v][0]] = i;
						}
					}
				}
			}
		}
};
SAP sap;

int main()
{
	freopen("a", "r", stdin);
	cin >> N >> M;
	sap.init(N + M + 2);
	int source = 0, sink = N + M + 1;
	for (int i = 1; i <= N; i++)
	{
		int t;
		cin >> t;
		for (int j = 1; j <= t; j++)
		{
			int x;
			cin >> x;
			sap.addCap(i, N + x, 1);
		}
		sap.addCap(source, i, 1);
	}
	for (int i = 1; i <= M; i++)
		sap.addCap(N + i, sink, 2);
	int tmp = sap.solve(source, sink);
	if (tmp < 2 * M)
	{
		cout << "NO" << endl;
		return 0;
	}
	cout << "YES" << endl;
	sap.dfs();
	for (int i = 1; i <= M; i++)
	{
		printf("2 %d %d\n", res[i][1], res[i][2]);
	}
	return 0;
}
