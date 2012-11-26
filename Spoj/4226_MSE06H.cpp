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
struct SegTree {
	int n;
	LL sum[MAXN << 2];
	void init() {
		memset(sum, 0, sizeof(sum));
	}
	void update(int p, int l, int r, int rt) {
		if (l == r) {
			sum[rt]++;
			return;
		}
		int mid = (l + r) >> 1;
		if (p <= mid) update(p, l, mid, rt << 1);
		else update(p, mid + 1, r, rt << 1 | 1);
		sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
	}
	LL query(int L, int R, int l, int r, int rt) {
		if (L <= l && r <= R) {
			return sum[rt];
		}
		int mid = (l + r) >> 1;
		LL ret = 0;
		if (L <= mid) ret += query(L, R, l, mid, rt << 1);
		if (R > mid) ret += query(L, R, mid + 1, r, rt << 1 | 1);
		return ret;
	}
}tree;

int main(int argc, char const *argv[])
{
	freopen("in.txt", "r", stdin);
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; cas <= Test; cas++) {
		printf("Test case %d: ", cas);
		int n, m, k;
		scanf("%d%d%d", &n, &m, &k);
		vector<pair<int, int> > p;
		for (int i = 0; i < k; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			p.PB(MP(a, b));
		}
		sort(p.begin(), p.end());
		tree.init();
		LL ret = 0;
		for (int i = 0; i < p.size(); i++) {
			int a = p[i].first, b = p[i].second;
			ret += tree.query(b + 1, m, 1, m, 1);
			tree.update(b, 1, m, 1);
		}
		printf("%lld\n", ret);
	}
	return 0;
}