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
#define th(x) this->x = x
const int MAXN = 5555;
const int MAXM = 200000 + 10;
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
}sap;

int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};
int n, m, s;
bool check(int x, int y)
{
	if (x < 1 || x > n || y < 1 || y > m) return false;
	return true;
}
int ID(int i, int j)
{
	return (i - 1) * m + j;
}
int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		scanf("%d%d%d", &n, &m, &s);
		int source = 0, sink = 2 * n * m + 1;
		sap.init(2 * n * m + 2);
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				sap.addCap(ID(i, j), n * m + ID(i, j), 1);
				for (int k = 0; k < 4; k++)
				{
					int x = i + dx[k], y = j + dy[k];
					if (check(x, y)) sap.addCap(n * m + ID(i, j), ID(x, y), 1);
				}
				//cout << ID(i, j) << " " << n * m + ID(i, j) << " 1" << endl;
				if (i == 1 || j == 1 || i == n || j == m)
				{
					sap.addCap(n * m + ID(i, j), sink, 1);
					//cout << n * m + ID(i, j) << " sink 1" << endl;
				}
			}
		}
		for (int i = 1; i <= s; i++)
		{
			int x, y;
			scanf("%d%d", &x, &y);
			sap.addCap(source, ID(x, y), 1);
			//cout << "source " << ID(x, y) << " 1" << endl;
		}
		int res = sap.solve(source, sink);
		if (res == s) puts("possible");
		else puts("not possible");
	}
	return 0;
}
