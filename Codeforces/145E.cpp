#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int maxn = 1000000 + 10;
struct Treenode {
	int l, r, n4, n7, ndec, ninc, flag;
}T[maxn << 2];

int n, m;
char str[maxn], op[10];

inline int lson(int rt) {
	return rt << 1;
}

inline int rson(int rt) {
	return (rt << 1) | 1;
}

inline int getMax(int a, int b, int c) {
	int ret = a;
	if (b > ret) ret = b;
	if (c > ret) ret = c;
	return ret;
}

void pushUp(int rt) {
	T[rt].n4 = T[lson(rt)].n4 + T[rson(rt)].n4;
	T[rt].n7 = T[lson(rt)].n7 + T[rson(rt)].n7;
	T[rt].ndec = getMax(T[lson(rt)].ndec + T[rson(rt)].n7, T[lson(rt)].n4 + T[rson(rt)].ndec, T[lson(rt)].n4 + T[rson(rt)].n7);
	T[rt].ninc = getMax(T[lson(rt)].ninc + T[rson(rt)].n4, T[lson(rt)].n7 + T[rson(rt)].ninc, T[lson(rt)].n7 + T[rson(rt)].n4);
}

void pushDown(int rt) {
	if (T[rt].flag) {
		T[lson(rt)].flag = !T[lson(rt)].flag;
		T[rson(rt)].flag = !T[rson(rt)].flag;
		swap(T[lson(rt)].n4, T[lson(rt)].n7);
		swap(T[lson(rt)].ndec, T[lson(rt)].ninc);
		swap(T[rson(rt)].n4, T[rson(rt)].n7);
		swap(T[rson(rt)].ndec, T[rson(rt)].ninc);
		T[rt].flag = 0;
	}
}

void build(int l, int r, int rt) {
	T[rt].l = l; T[rt].r = r;
	if (l == r) {
		T[rt].n4 = (str[r] == '4');
		T[rt].n7 = (str[r] == '7');
		T[rt].ndec = T[rt].ninc = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, lson(rt));
	build(mid + 1, r, rson(rt));
	pushUp(rt);
}

void update(int L, int R, int rt) {
	if (L <= T[rt].l && T[rt].r <= R) {
		T[rt].flag = !T[rt].flag;
		swap(T[rt].n4, T[rt].n7);
		swap(T[rt].ninc, T[rt].ndec);
		return;
	}
	pushDown(rt);
	int mid = (T[rt].l + T[rt].r) >> 1;
	if (L <= mid) update(L, R, lson(rt));
	if (R > mid) update(L, R, rson(rt));
	pushUp(rt);
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	scanf("%s", str + 1);
	build(1, n, 1);
	while (m--) {
		scanf("%s", op);
		if (*op == 's') {
			int a, b;
			scanf("%d%d", &a, &b);
			update(a, b, 1);
		}else {
			printf("%d\n", T[1].ndec);
		}
	}
	return 0;
}
