#include <cstdio>
#include <cstring>
//#include <iostream>
#include <algorithm>
using namespace std;

#define th(x) this->x = x
const int MAXN = 200000;
const int MAXM = 200000;
const int inf = 100000000;
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
			//if (n != 1083) cout << "why!!!!!!!!!" << endl;
			//cout << i << " " << j << cap1 << endl;
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

int D, C, T;
int pos[111];
struct Tower
{
	int pos, cost;
}t[111];
struct Edge
{
	int u, v, w;
}edge[MAXM];
int cnt;

inline bool cmp(const Tower &a, const Tower &b)
{
	if (a.pos == b.pos) return a.cost > b.cost;
	return a.pos < b.pos;
}

inline void solve()
{
	for (int i = 1; i <= C; i++)
		scanf("%d", &pos[i]);
	for (int i = 1; i <= T; i++)
		scanf("%d%d", &t[i].pos, &t[i].cost);
	sort(pos + 1, pos + C + 1);
	sort(t + 1, t + T + 1, cmp);

	//sap.init(12);
	cnt = 0;
	int sum = 0, source = 0, sink, num = T;
	for (int i = 1, j; i <= C; i++)
	{
		for (j = T; j >= 1; j--)
			if (t[j].pos < pos[i]) break;

		int prev = -1;
		while (j >= 1 && pos[i] - t[j].pos < D)
		{
			num++;
			//sap.addCap(source, num, D - pos[i] + t[j].pos);
			edge[cnt].u = source;
			edge[cnt].v = num;
			edge[cnt++].w = D - pos[i] + t[j].pos;
			if (prev != -1)
			{
				//sap.addCap(num, prev, inf);
				edge[cnt].u = num;
				edge[cnt].v = prev;
				edge[cnt++].w = inf;
			}
			//sap.addCap(num, j, inf);
			edge[cnt].u = num;
			edge[cnt].v = j;
			edge[cnt++].w = inf;
			prev = num;
			sum += D - pos[i] + t[j].pos;
			j -= 4;
		}
	}

	sink = ++num;
	sap.init(num + 1);
	for (int k = 0; k < cnt; k++)
	{
		sap.addCap(edge[k].u, edge[k].v, edge[k].w);
		//cout << edge[k].u << " " << edge[k].v << " " << edge[k].w << endl;
	}
	for (int i = 1; i <= T; i++)
	{
		sap.addCap(i, sink, t[i].cost);
		//cout << i << " " << sink << " " << t[i].cost << endl;
	}
	//sap.n = 12;
	//sap.n = sink + 1;
	//cout << source << " " << sap.n << " " << sink <<  endl;
	//cout << sum << endl;
	int tmp = sap.solve(source, sink);
	//cout << tmp << endl;
	printf("%d\n", sum - tmp);
}

int main()
{
	freopen("in", "r", stdin);
	freopen("test1", "w", stdout);
	while (scanf("%d%d%d", &D, &C, &T))
	{
		if (C == -1) break;
		solve();
	}
	return 0;
}
