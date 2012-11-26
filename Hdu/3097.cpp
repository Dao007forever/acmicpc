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

#define MAXN 1005
struct djs {
	int n;
	int p[MAXN], cnt[MAXN];

	void init(int n) {
		this->n = n;
		memset(cnt, 0, sizeof(cnt));
		for (int i = 1; i <= n; i++)
			p[i] = i;
	}

	int find(int x) {
		return p[x] == x ? x : p[x] = find(p[x]);
	}

	void Union(int x, int y) {
		int px = find(x), py = find(y);
		if (cnt[px] > cnt[py]) {
			p[py] = px;
			cnt[px] += cnt[py];
		} else {
			p[px] = py;
			cnt[py] += cnt[px];
		}
	}

	bool check(int i) {
		return (cnt[i] % 2 == 0);
	}
}uf;

int main() {
	int n, m;
	while (scanf("%d%d", &n, &m) && n + m) {
		uf.init(n);
		while (m--) {
			int a, b;
			scanf("%d%d", &a, &b);
			if (uf.find(a) != uf.find(b))
				uf.Union(a, b);
			uf.cnt[uf.find(a)]++;
		}
		bool flag = true;
		for (int i = 1; i <= n; i++)
			if (uf.p[i] == i) {
				flag &= uf.check(i);
			}
		printf("%s\n", flag ? "Yes" : "No");
	}
	return 0;
}
