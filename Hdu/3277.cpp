/*
 * Author: Yang Zhang
 * Created Time: Wed 22 Aug 2012 07:41:19 PM CST
 * File Name: 3277.cpp
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
/*const int MAXN = 1000 + 10;
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
        cap[i][j] += val;
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

}sap;*/
#define th(x) this->x = x
const int MAXN = 750 + 10;
const int MAXM = 100000 + 10;
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

struct DisJointSet{
	int rank[MAXN], parent[MAXN];

	void init() {
		for (int i = 0; i < MAXN; i++) {
			rank[i] = 0;
			parent[i] = i;
		} 
	}

	int Find(int x) {
		if (parent[x] == x) return x;
		return parent[x] = Find(parent[x]);
	}

	void Union(int x, int y) {
		x = Find(x);
		y = Find(y);

		if (x == y) return;
		
		if (rank[x] >= rank[y]) {
			parent[y] = x;
			if (rank[x] == rank[y])
				rank[x]++;
		}
		else {
			parent[x] = y;
		}
	}
}dsu;

int n, m, f, K;
int source, sink;
int like[MAXN][MAXN];
inline bool check(int lim) {
	/*for (int i = 1; i <= n; i++) {
		sap.cap[source][i] = lim;
		sap.cap[n + i][sink] = lim;
	}*/
	for (int i = 0; i < 4 * n; i += 2) {
		sap.buf[i].cap = lim;
		sap.buf[i ^ 1].cap = 0;
	}
//	for (int i = 4 * n; i < sap.len; i++)
//		sap.buf[i] = E[i];
	int flow = sap.solve(source, sink);
	return n * lim == flow;
}
int main() {
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		memset(like, 0, sizeof(like));
		dsu.init();
		scanf("%d%d%d%d", &n, &m, &K, &f);
		while (m--) {
			int a, b;
			scanf("%d%d", &a, &b);
			like[a][b] = 1;
		}
		while (f--) {
			int a, b;
			scanf("%d%d", &a, &b);
			dsu.Union(a, b);
		}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (like[i][j]) {
					int pi = dsu.Find(i);
					like[pi][j] = 1;
				}
		sap.init(3 * n + 2);
		source = 0, sink = 3 * n + 1;
		for (int i = 1; i <= n; i++) {
			sap.addCap(source, i, 0);
			sap.addCap(n + i, sink, 0);
		}
		for (int i = 1; i <= n; i++) {
			sap.addCap(i, 2 * n + i, K);
			for (int j = 1; j <= n; j++) {
				if (like[i][j]) {
					sap.addCap(i, n + j, 1);
					continue;
				}
				if (like[dsu.Find(i)][j]) {
					sap.addCap(i, n + j, 1);
					continue;
				}
				sap.addCap(2 * n + i, n + j, 1);
			}
		}
//		for (int i = 0; i < sap.len; i++)
//			E[i] = sap.buf[i];
		int l = 0, r = n, ans = -1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (check(mid)) {
				l = mid + 1;
				ans = mid;
			} else r = mid - 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}

