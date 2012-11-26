/*
 * Author: Yang Zhang
 * Created Time: Sun 26 Aug 2012 03:14:26 PM CST
 * File Name: 962_IM.cpp
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
#define th(x) this->x = x
const int MAXN = 60000 + 10;
const int MAXM = 500000 + 10;
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
	//	cout << i << " " << j << " " << cap1 << endl;
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

int main() {
	int Test, n, m;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d%d", &n, &m);
		sap.init(2 * n + 2);
		int source = 0, sink = 2 * n + 1;
		for (int i = 1; i <= n; i++) {
			sap.addCap(i, i + n, 1);
		}
		while (m--) {
			int a, b;
			scanf("%d%d", &a, &b);
			if (a > n || b > n) continue;
			sap.addCap(a + n, b, 1);
			sap.addCap(b + n, a, 1);
		}
		sap.addCap(source, 2 + n, 2);
		sap.addCap(1 + n, sink, 1);
		sap.addCap(3 + n, sink, 1);
		int maxflow = sap.solve(source, sink);
		if (n < 3) {
			puts("NO");
			continue;
		}
		printf("%s\n", maxflow == 2 ? "YES" : "NO");
	}
	return 0;
}

