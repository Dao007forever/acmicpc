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

const int maxn = 100005;
struct Node {
	int l, r, sum;
}T[maxn << 2];

inline int lson(int rt) 
{
	return rt << 1;
}

inline int rson(int rt)
{
	return rt << 1 | 1;
}

void pushUp(int rt)
{
	T[rt].sum = T[lson(rt)].sum + T[rson(rt)].sum;
}

void build(int l, int r, int rt)
{
	T[rt].l = l, T[rt].r = r;
	if (l == r) {
		T[rt].sum = 0;
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, lson(rt));
	build(mid + 1, r, rson(rt));
	pushUp(rt);
}

void update(int p, int rt, int c)
{
	if (T[rt].l == T[rt].r) {
		T[rt].sum += c;
		return;
	}
	int mid = (T[rt].l + T[rt].r) >> 1;
	if (p <= mid) update(p, lson(rt), c);
	else update(p, rson(rt), c);
	pushUp(rt);
}

int query(int k, int rt)
{
	if (T[rt].l == T[rt].r) {
		return T[rt].l;
	}
	int mid = (T[rt].l + T[rt].r) >> 1;
	if (k <= T[lson(rt)].sum) return query(k, lson(rt));
	else return query(k - T[lson(rt)].sum, rson(rt));
}

int get(int L, int R, int rt)
{
	if (L <= T[rt].l && T[rt].r <= R) {
		return T[rt].sum;
	}
	int mid = (T[rt].l + T[rt].r) >> 1;
	int ret = 0;
	if (L <= mid) ret += get(L, R, lson(rt));
	if (mid < R) ret += get(L, R, rson(rt));
	return ret;
}

int M;
int vis[maxn];

int main()
{
	freopen("in", "r", stdin);
	while (scanf("%d", &M) != EOF) {
		memset(vis, 0, sizeof(vis));
		build(1, 100000, 1);
		while (M--) {
			int op;
			scanf("%d", &op);
			if (op == 0) {
				int p;
				scanf("%d", &p);
				vis[p]++;
				update(p, 1, 1);
			} else if (op == 1) {
				int p;
				scanf("%d", &p);
				if (!vis[p]) {
					cout << "No Elment!" << endl;
				} else {
					vis[p]--;
					update(p, 1, -1);
				}
			} else {
				int a, k;
				scanf("%d%d", &a, &k);
				int tmp = get(1, a, 1);
				k += tmp;
				if (k > T[1].sum) {
					cout << "Not Find!" << endl;
				}
				else {
					int ret = query(k, 1);
					cout << ret << endl;
				}
			}
		}
	}
	return 0;
}
