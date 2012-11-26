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
LL a[MAXN];
const LL inf = 0x3f3f3f3f3f3f3f3fLL;
struct SegTree {
	struct Node {
		int l, r;
		LL Min, Max, sum, sqr, add, len, change;
	}T[MAXN << 2];

	int lson(int rt) {return rt << 1;}
	int rson(int rt) {return rt << 1 | 1;}

	void pushUp(int rt) {
		T[rt].Max = max(T[lson(rt)].Max, T[rson(rt)].Max);
		T[rt].Min = min(T[lson(rt)].Min, T[rson(rt)].Min);
		T[rt].sum = T[lson(rt)].sum + T[rson(rt)].sum;
		T[rt].sqr = T[lson(rt)].sqr + T[rson(rt)].sqr;
	}

	void pushDown(int rt) {
		if (T[rt].change != inf) {
			LL change = T[rt].change;
			T[rt].change = inf;
			T[lson(rt)].change = T[rson(rt)].change = change;
			T[lson(rt)].Min = T[lson(rt)].Max = change;
			T[rson(rt)].Min = T[rson(rt)].Max = change;
			T[lson(rt)].sum = T[lson(rt)].len * change;
			T[rson(rt)].sum = T[rson(rt)].len * change;
			T[lson(rt)].sqr = T[lson(rt)].len * change * change;
			T[rson(rt)].sqr = T[rson(rt)].len * change * change;
			T[lson(rt)].add = T[rson(rt)].add = 0;
		}
		if (T[rt].add) {
			LL add = T[rt].add;
			T[rt].add = 0;
			T[lson(rt)].Min += add;
			T[rson(rt)].Min += add;
			T[lson(rt)].Max += add;
			T[rson(rt)].Max += add;
			T[lson(rt)].sqr += T[lson(rt)].sum * add * 2ll + T[lson(rt)].len * add * add;
			T[rson(rt)].sqr += T[rson(rt)].sum * add * 2ll + T[rson(rt)].len * add * add;
			T[lson(rt)].sum += add * T[lson(rt)].len;
			T[rson(rt)].sum += add * T[rson(rt)].len;
			if (T[lson(rt)].change != inf) T[lson(rt)].change += add;
			else T[lson(rt)].add += add;
			if (T[rson(rt)].change != inf) T[rson(rt)].change += add;
			else T[rson(rt)].add += add;
		}
	}

	void build(int l, int r, int rt) {
		T[rt].l = l; T[rt].r = r; T[rt].len = r - l + 1;
		T[rt].Min = inf; T[rt].Max = -inf;
		T[rt].sum = T[rt].sqr = T[rt].add = 0;
		T[rt].change = inf;
		if (l == r) {
			T[rt].Min = T[rt].Max = T[rt].sum = a[l];
			T[rt].sqr = a[l] * a[l];
			return;
		}
		int mid = (l + r) >> 1;
		build(l, mid, lson(rt));
		build(mid + 1, r, rson(rt));
		pushUp(rt);
	}

	void updateAdd(int L, int R, LL c, int rt) {
		if (L <= T[rt].l && T[rt].r <= R) {
			if (T[rt].change != inf) {
				T[rt].change += c;
			} else {
				T[rt].add += c;
			}
			T[rt].Min += c;
			T[rt].Max += c;
			T[rt].sqr += T[rt].sum * c * 2ll + T[rt].len * c * c;
			T[rt].sum += c * T[rt].len;
			return;
		}
		pushDown(rt);
		int mid = (T[rt].l + T[rt].r) >> 1;
		if (L <= mid) updateAdd(L ,R, c, lson(rt));
		if (R > mid) updateAdd(L, R, c, rson(rt));
		pushUp(rt);
	}

	void updateChange(int L, int R, LL c, int rt) {
		if (L <= T[rt].l && T[rt].r <= R) {
			T[rt].change = c;
			T[rt].add = 0;
			T[rt].Min = c;
			T[rt].Max = c;
			T[rt].sum = T[rt].len * c;
			T[rt].sqr = T[rt].len * c * c;
			return;
		}
		pushDown(rt);
		int mid = (T[rt].l + T[rt].r) >> 1;
		if (L <= mid) updateChange(L, R, c, lson(rt));
		if (R > mid) updateChange(L, R, c, rson(rt));
		pushUp(rt);
	}

	LL querySum(int L, int R, int rt) {
		if (L <= T[rt].l && T[rt].r <= R) {
			return T[rt].sum;
		}
		pushDown(rt);
		int mid = (T[rt].l + T[rt].r) >> 1;
		LL ret = 0;
		if (L <= mid) ret += querySum(L, R, lson(rt));
		if (R > mid) ret += querySum(L, R, rson(rt));
		return ret;
	}

	LL querySqr(int L, int R, int rt) {
		if (L <= T[rt].l && T[rt].r <= R) {
			return T[rt].sqr;
		}
		pushDown(rt);
		int mid = (T[rt].l + T[rt].r) >> 1;
		LL ret = 0;
		if (L <= mid) ret += querySqr(L, R, lson(rt));
		if (R > mid) ret += querySqr(L, R, rson(rt));
		return ret;
	}

	LL queryMin(int L, int R, int rt) {
		if (L <= T[rt].l && T[rt].r <= R) {
			return T[rt].Min;
		}
		pushDown(rt);
		int mid = (T[rt].l + T[rt].r) >> 1;
		LL ret = inf;
		if (L <= mid) ret = min(ret, queryMin(L, R, lson(rt)));
		if (R > mid) ret = min(ret, queryMin(L, R, rson(rt)));
		return ret;
	}

	LL queryMax(int L, int R, int rt) {
		if (L <= T[rt].l && T[rt].r <= R) {
			return T[rt].Max;
		}
		pushDown(rt);
		int mid = (T[rt].l + T[rt].r) >> 1;
		LL ret = -inf;
		if (L <= mid) ret = max(ret, queryMax(L, R, lson(rt)));
		if (R > mid) ret = max(ret, queryMax(L, R, rson(rt)));
		return ret;
	}
}tree;

LL gcd(LL a, LL b) {
	return b ? gcd(b, a % b) : a;
}

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; Test--; cas++) {
		printf("Case %d:\n", cas);
		int n, q;
		scanf("%d%d", &n, &q);
		for (int i = 1; i <= n; i++)
			scanf("%lld", &a[i]);
		tree.build(1, n, 1);
		while (q--) {
			int type;
			scanf("%d", &type);
			if (type == 0) {
				int l, r;
				LL x;
				scanf("%d%d%lld", &l, &r, &x);
				tree.updateChange(l, r, x, 1);
			} else if (type == 1) {
				int l, r;
				LL x;
				scanf("%d%d%lld", &l, &r, &x);
				tree.updateAdd(l, r, x, 1);
			} else {
				int l, r;
				scanf("%d%d", &l, &r);
				LL range = tree.queryMax(l, r, 1) - tree.queryMin(l, r, 1);
				LL sum = tree.querySum(l, r, 1);
				LL len = r - l + 1;
				LL ret = len * tree.querySqr(l, r, 1) - sum * sum;
				LL tmp = len * len;
				LL g = gcd(ret, tmp);
				ret /= g; tmp /= g;
				printf("%lld/%lld %lld\n", ret, tmp, range);
			}
		}
	}
	return 0;
}