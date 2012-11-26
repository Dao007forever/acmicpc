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
#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

#define MAXN 100005
struct SegTree {

	LL sum[MAXN << 2], flag[MAXN << 2];

	void build() {
		memset(flag, 0, sizeof(flag));
		memset(sum, 0, sizeof(sum));
	}

	void pushUp(int rt) {
		sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
	}

	void pushDown1(int rt, int m) {
		if (flag[rt]) {
			flag[rt << 1] += flag[rt];
			flag[rt << 1 | 1] += flag[rt];
			sum[rt << 1] += flag[rt] * (m - (m >> 1));
			sum[rt << 1 | 1] += flag[rt] * (m >> 1);
			flag[rt] = 0;
		}
	}

	void pushDown2(int rt, int l, int r) {
		if (flag[rt]) {
			flag[rt << 1] += flag[rt];
			flag[rt << 1 | 1] += flag[rt];
			int mid = (l + r) / 2;
			sum[rt << 1] += flag[rt] * (mid - l + 1) * (l + mid) / 2;
			sum[rt << 1 | 1] += flag[rt] * (r - mid) * (mid + 1 + r) / 2;
			flag[rt] = 0;
		}
	}	

	void update2(int L, int R, LL c, int l, int r, int rt) {
		if (L <= l && r <= R) {
			flag[rt] += c;
			sum[rt] += c * (r - l + 1) * (l + r) / 2;
			return;
		}
		pushDown2(rt, l, r);
		int mid = (l + r) >> 1;
		if (L <= mid) update2(L, R, c, l, mid, rt << 1);
		if (R > mid) update2(L, R, c, mid + 1, r, rt << 1 | 1);
		pushUp(rt);
	}

	void update1(int L, int R, LL c, int l, int r, int rt) {
		if (L <= l && r <= R) {
			flag[rt] += c;
			sum[rt] += c * (r - l + 1);
			return;
		}
		pushDown1(rt, r - l + 1);
		int mid = (l + r) >> 1;
		if (L <= mid) update1(L, R, c, l, mid, rt << 1);
		if (R > mid) update1(L, R, c, mid + 1, r, rt << 1 | 1);
		pushUp(rt);
	}

	LL query1(int L, int R, int l, int r, int rt) {
		if (L <= l & r <= R) {
			return sum[rt];
		}
		pushDown1(rt, r - l + 1);
		int mid = (l + r) >> 1;
		LL ret = 0;
		if (L <= mid) ret += query1(L, R, l, mid, rt << 1);
		if (R > mid) ret += query1(L, R, mid + 1, r, rt << 1 | 1);
		return ret;
	}

	LL query2(int L, int R, int l, int r, int rt) {
		if (L <= l & r <= R) {
			return sum[rt];
		}
		pushDown2(rt, l, r);
		int mid = (l + r) >> 1;
		LL ret = 0;
		if (L <= mid) ret += query2(L, R, l, mid, rt << 1);
		if (R > mid) ret += query2(L, R, mid + 1, r, rt << 1 | 1);
		return ret;
	}
}t1, t2;

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; Test--; cas++) {
		printf("Case %d:\n", cas);
		int n, q;
		scanf("%d%d", &n, &q);
		t1.build(); t2.build();
		for (int i = 1; i <= n; i++) {
			t1.update1(i, i, 100, 1, n, 1);
			t2.update2(i, i, 100, 1, n, 1);
		}
		while (q--) {
			char op[32];
			scanf("%s", op);
			if (*op == 'q') {
				int l, r;
				scanf("%d%d", &l, &r);
				LL ret = t2.query2(l, r, 1, n, 1) - t1.query1(l, r, 1, n, 1) * (l - 1);
				printf("%lld\n", ret);
			} else {
				int l, r, u;
				scanf("%d%d%d", &l, &r, &u);
				t1.update1(l, r, u, 1, n, 1);
				t2.update2(l, r, u, 1, n, 1);
			}
		}
	}
	return 0;
}