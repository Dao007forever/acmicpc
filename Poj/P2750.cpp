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

const int MAXN = 100005;
const int inf = 0x3f3f3f3f;
int n, q;
int val[MAXN];
struct Tnode {
	int l, r, maxv, minv, sum, lmax, rmax, lmin, rmin;
};
struct SegTree {
	Tnode T[MAXN << 2];

	int lson(int rt) {return rt << 1;}
	int rson(int rt) {return rt << 1 | 1;}

	void pushUp(int rt) {
		int left = lson(rt), right = rson(rt);

		T[rt].sum = T[left].sum + T[right].sum;

		T[rt].lmax = max(T[left].lmax, T[left].sum + T[right].lmax);
		T[rt].rmax = max(T[right].rmax, T[right].sum + T[left].rmax);
		T[rt].maxv = max(T[left].rmax + T[right].lmax, max(T[left].maxv, T[right].maxv));

		T[rt].lmin = min(T[left].lmin, T[left].sum + T[right].lmin);
		T[rt].rmin = min(T[right].rmin, T[right].sum + T[left].rmin);
		T[rt].minv = min(T[left].rmin + T[right].lmin, min(T[left].minv, T[right].minv));
	}

	void build(int l, int r, int rt) {
		T[rt].l = l; T[rt].r = r;
		if (l == r) {
			T[rt].sum = T[rt].maxv = T[rt].minv = T[rt].lmax = T[rt].rmax = T[rt].lmin = T[rt].rmin = val[r];
			return;
		}
		int mid = (l + r) >> 1;
		build(l, mid, lson(rt));
		build(mid + 1, r, rson(rt));
		pushUp(rt);
	}

	void update(int p, int c, int rt) {
		if (T[rt].l == T[rt].r) {
			T[rt].sum = T[rt].maxv = T[rt].minv = T[rt].lmax = T[rt].rmax = T[rt].lmin = T[rt].rmin = c;
			return;
		}
		int mid = (T[rt].l + T[rt].r) >> 1;
		if (p <= mid) update(p, c, lson(rt));
		else update(p, c, rson(rt));
		pushUp(rt);
	}
}tree;

int main(int argc, char const *argv[])
{
	freopen("in.txt", "r", stdin);
	while (~scanf("%d", &n)) {
		for (int i = 1; i <= n; i++)
			scanf("%d", val + i);
		tree.build(1, n, 1);
		scanf("%d", &q);
		while (q--) {
			int pos, k;
			scanf("%d%d", &pos, &k);
			tree.update(pos, k, 1);
			int ret;
			if (tree.T[1].sum == tree.T[1].maxv) ret = tree.T[1].sum - tree.T[1].minv;
			else ret = max(tree.T[1].maxv, tree.T[1].sum - tree.T[1].minv);
			printf("%d\n", ret);
		}
	}
	return 0;
}