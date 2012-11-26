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
#define abs(x) ((x) > 0 ? (x) : -(x))
const int MAXN = 222;
const int MAXM = 10 * MAXN;
const int inf = 0x3f3f3f3f;
int N, M;
int outdeg[MAXN], indeg[MAXN];
int ex[MAXM], ey[MAXM], ed[MAXM];
struct Edge
{
	int v, next, vis;
}edge[MAXM];
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
	int ans[555], tot;
	int num, Head[MAXN];
	void addEdge(int u, int v)
	{
		edge[num].v = v;
		edge[num].next = Head[u];
		Head[u] = num++;
	}
	void dfs(int u)
	{
		for (int i = Head[u]; i != -1; i = edge[i].next)
		if (!edge[i].vis)
		{
			int v = edge[i].v;
			edge[i].vis = 1;
			dfs(v);
		}
		ans[++tot] = u;
	}
	void output()
	{
		num = 0;
		memset(Head, -1, sizeof(Head));
		memset(edge, 0, sizeof(edge));
		memset(ans, 0, sizeof(ans));
		for (int i = 1; i <= M; i++)
		if (ed[i])
		{
			addEdge(ex[i], ey[i]);
			//cout << ex[i] << " " << ey[i] << endl;
		}
		for (int u = 1; u <= N; u++)
			for (int i = E[u]; i != -1; i = buf[i].next)
			if (buf[i].cap != 0)
			{
				int b = buf[i].b;
				if (buf[i].flow != 0)
				{
					addEdge(b, u);
					//cout << b << " " << u << endl;
				}
				else 
				{
					addEdge(u, b);
					//cout << u << " " << b << endl;
				}
			}
		tot = 0;
		dfs(1);
		for (int i = tot; i >= 1; i--)
		if (i == tot) printf("%d", ans[i]);
		else printf(" %d", ans[i]);
		printf("\n");
	}
}sap;
int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	int blank = 0;
	while (Test--)
	{
		if (blank) puts("");
		blank = true;
		memset(outdeg, 0, sizeof(outdeg));
		memset(indeg, 0, sizeof(indeg));
		scanf("%d%d", &N, &M);
		int source = 0, sink = N + 1;
		sap.init(N + 2);
		for (int i = 1; i <= M; i++)
		{
			int u, v;
			char op[5];
			scanf("%d%d%s", &u, &v, op);
			ex[i] = u; ey[i] = v;
			if (op[0] == 'U') ed[i] = 0;
			else ed[i] = 1;
			outdeg[u]++;
			indeg[v]++;
			if (!ed[i]) sap.addCap(u, v, 1);
		}
		bool flag = false;
		for (int i = 1; i <= N; i++)
		{
			if (abs(outdeg[i] - indeg[i]) & 1)
			{
				flag = true;
				break;
			}
		}
		if (flag)
		{
			puts("No euler circuit exist");
			continue;
		}
		int sum = 0;
		for (int i = 1; i <= N; i++)
		{
			int x = (outdeg[i] - indeg[i]) / 2;
			if (x > 0)
			{
				sap.addCap(source, i, x);
				sum += x;
			}
			else sap.addCap(i, sink, -x);
		}
		int res = sap.solve(source, sink);
		if (res == sum) sap.output();
		else puts("No euler circuit exist");
	}
	return 0;
}
