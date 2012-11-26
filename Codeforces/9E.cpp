/*
 * Author : Yang Zhang
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

int n, m;
int deg[55], p[55];
vector<int> adj[55];
vector<pair<int, int> > ans;

int Find(int x) {
	if (p[x] == x) return x;
	return p[x] = Find(p[x]);
}

void Union(int x, int y) {
	p[x] = y;
}

int main() {
	freopen("in", "r", stdin);
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		p[i] = i;
	if (m > n) {
		puts("NO");
		return 0;
	}
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		deg[a]++; deg[b]++;
		int fa = Find(a), fb = Find(b);
		if (fa != fb) {
			Union(fa, fb);
		}
		if (deg[a] > 2 || deg[b] > 2) {
			puts("NO");
			return 0;
		}
	}
	for (int i = 0; i < n - m; i++) {
		int a = -1, b = -1;
		for (int j = 0; j < n; j++)
			if (deg[j] < 2) {
				a = j;
				break;
			}
		if (a == -1) {
			puts("NO");
			break;
		}
		deg[a]++;
		for (int j = 0; j < n; j++)
			if (deg[j] < 2 && Find(a) != Find(j)) {
				b = j;
				break;
			}
		if (b == -1) {
			for (int j = 0; j < n; j++)
				if (deg[j] < 2) {
					b = j;
					break;
				}
		}
		if (b == -1) {
			puts("NO");
			return 0;
		}
		deg[b]++;
		ans.PB(MP(a + 1, b + 1));
		int fa = Find(a), fb = Find(b);
		Union(fa, fb);
	}
	for (int i = 0; i < n && m; i++)
		if (Find(i) != Find(0)) {
			puts("NO");
			return 0;
		}
	printf("YES\n%d\n", n - m);
	for (int i = 0; i < n - m; i++)
		printf("%d %d\n", ans[i].first, ans[i].second);
	return 0;
}
