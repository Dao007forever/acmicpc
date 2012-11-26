/*
 * Author: Yang Zhang
 * Created Time: Sat 25 Aug 2012 12:23:36 PM CST
 * File Name: main.cpp
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

#define maxn 1005
int n, m, k;
struct Edge {
	int a, b, c;
}edge[maxn * maxn];
struct DisJointSet{
	int rank[maxn], parent[maxn];

	void init() {
		for (int i = 0; i < maxn; i++) {
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

int mst() {
	dsu.init();
	int ret = 0;
	for (int i = 0; i < m; i++) {
		int a = edge[i].a, b = edge[i].b;
		if (dsu.Find(a) != dsu.Find(b)) {
			ret += edge[i].c;
			dsu.Union(a, b);
		}
	}
	return ret;
}

bool cmp1(const Edge &p, const Edge &q) {
	return p.c < q.c;
}

bool cmp2(const Edge &p, const Edge &q) {
	return p.c > q.c;
}

int main() {
	while (scanf("%d%d%d", &n, &m, &k)) {
		if (n == 0 && m == 0 && k == 0) break;
		for (int i = 0; i < m; i++) {
			int a, b;
			char op[3];
			scanf("%s%d%d", op, &a, &b);
			edge[i].a = a; edge[i].b = b;
			if (*op == 'B') {
				edge[i].c = 1;
			} else {
				edge[i].c = 0;
			}
		}
		sort(edge, edge + m, cmp1);
		int Min = mst();
		sort(edge, edge + m, cmp2);
		int Max = mst();
		printf("%d\n", (Min <= k && k <= Max) ? 1 : 0);
	}
	return 0;
}

