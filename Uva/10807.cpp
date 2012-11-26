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

const int maxn = 55;
struct Edge {
	int u, v, w;
}edge[55];
int n, m;
struct DisJointSet{
	int rank[maxn], parent[maxn];

	void init(int n) {
		for (int i = 0; i <= n; i++) {
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

	int count(int n) {
		int ret = 0;
		for (int i = 1; i <= n; i++)
			if (parent[i] == i) ret++;
		return ret;
	}
}s1, s2;

bool cmp(Edge A, Edge B) {
	return A.w < B.w;
}

int main() {
	freopen("in", "r", stdin);
	while (cin >> n && n) {
		cin >> m;
		for (int i = 0; i < m; i++) {
			int u, v, w;
			cin >> edge[i].u >> edge[i].v >> edge[i].w;
		}
		sort(edge, edge + m, cmp);
		int ret = 0;
		s1.init(n);
		s2.init(n);

		for (int i = 0; i < m; i++) {
			int u = edge[i].u, v = edge[i].v;
			if (s1.Find(u) != s1.Find(v)) {
				s1.Union(u, v);
				ret += edge[i].w;
			} else if (s2.Find(u) != s2.Find(v)) {
				s2.Union(u, v);
				ret += edge[i].w;
			}
		}
		int t1 = s1.count(n), t2 = s2.count(n);
		if (t1 != 1 || t2 != 1) {
			cout << "No way!" << endl;
		} else {
			cout << ret << endl;
		}
	}
	return 0;
}
