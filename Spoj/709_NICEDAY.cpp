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
const int inf = 0x3f3f3f3f;
struct SegTree {
	struct node {
		int l, r, Min;
	}T[MAXN << 2];
	int n;

	int lson(int rt) {return rt << 1;}
	int rson(int rt) {return rt << 1 | 1;}

	void pushUp(int rt) {
		T[rt].Min = min(T[lson(rt)].Min, T[rson(rt)].Min);
	}

	void build(int l, int r, int rt) {
		T[rt].l = l; T[rt].r = r; T[rt].Min = inf;
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(l, mid, lson(rt));
		build(mid + 1, r, rson(rt));
	}

	void update(int p, int c, int rt) {
		if (T[rt].l == T[rt].r) {
			T[rt].Min = c;
			return;
		}
		int mid = (T[rt].l + T[rt].r) >> 1;
		if (p <= mid) update(p, c, lson(rt));
		else update(p, c, rson(rt));
		pushUp(rt);
	}

	int query(int L, int R, int rt) {
		if (L <= T[rt].l && T[rt].r <= R) {
			return T[rt].Min;
		}
		int mid = (T[rt].l + T[rt].r) >> 1;
		int ret = inf;
		if (L <= mid) ret = min(ret, query(L, R, lson(rt)));
		if (R > mid) ret = min(ret, query(L, R, rson(rt)));
		return ret;
	}
}tree;

int n;
struct node {
	int a, b, c;
}p[MAXN];
bool better[MAXN];
bool cmp(const node &A, const node &B) {
	return A.c < B.c;
}
int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d", &n);
		memset(better, 0, sizeof(better));
		vector<pair<int, int> > x;
		for (int i = 0; i < n; i++) {
			scanf("%d%d%d", &p[i].a, &p[i].b, &p[i].c);
			x.PB(MP(p[i].a, i));
		}
		sort(x.begin(), x.end());
		int r = 1;
		p[x[0].second].a = r;
		for (int i = 1; i < n; i++) {
			if (x[i].first != x[i - 1].first) {
				r++;
			}
			p[x[i].second].a = r;
		}

		tree.build(0, n, 1);
		sort(p, p + n, cmp);
		for (int i = 0; i < n; i++) {
			int tmp = tree.query(0, p[i].a - 1, 1);
			if (tmp >= p[i].b) {
				better[i] = true;
			}
			tree.update(p[i].a, p[i].b, 1);
		}
		int ret = 0;
		for (int i = 0; i < n; i++)
			ret += better[i];
		printf("%d\n", ret);
	}
	return 0;
}