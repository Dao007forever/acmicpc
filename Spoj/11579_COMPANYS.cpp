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

#define maxV 50005
#define maxE 100005
struct Edge {
	int a, b, c, d;
	Edge() {}
	Edge(int a, int b, int c, int d) : a(a), b(b), c(c), d(d) {}
	bool operator < (const Edge &pt) const {
		if (c != pt.c) return c < pt.c;
		else return d < pt.d;
	}
}edge[maxE];
int N, M, K;
int p[maxV];

int find(int x) {
	return p[x] == x ? x : p[x] = find(p[x]);
}

int check(int add) {
	for (int i = 0; i < M; i++) {
		if (edge[i].d) continue;
		edge[i].c += add;
	}
	sort(edge, edge + M);
	for (int i = 0; i < N; i++) p[i] = i;
	int sum = 0, cnt = 0;
	for (int i = 0; i < M; i++) {
		int a = edge[i].a, b = edge[i].b;
		int pa = find(a), pb = find(b);
		if (pa != pb) {
			p[pa] = pb;
			sum += edge[i].c;
			cnt += (edge[i].d == 0);
		}
	}
	for (int i = 0; i < M; i++) {
		if (edge[i].d) continue;
		edge[i].c -= add;
	}
	if (cnt < K) return -1;
	return sum;
}

void solve() {
	int lo = -400, hi = 400, ret = 0;
	while (lo <= hi) {
		int mid = (lo + hi) >> 1;
		if (check(mid) != -1) {
			ret = mid;
			lo = mid + 1;
		} else hi = mid - 1;
	}
	int ans = check(ret) - ret * K;
	printf("%d\n", ans);
}

int main(int argc, char const *argv[])
{
	int cas = 1;
	while (~scanf("%d%d%d", &N, &M, &K)) {
		printf("Case %d: ", cas++);
		for (int i = 0; i < M; i++) {
			int a, b, c, d;
			scanf("%d%d%d%d", &a, &b, &c, &d);
			edge[i] = Edge(a, b, c, d);
		}
		solve();
	}
	return 0;
}