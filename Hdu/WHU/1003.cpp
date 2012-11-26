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

const int maxn = 270005;
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
		T[rt].sum = 1;
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

int N, K;
int main() {
	freopen("in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; cas <= Test; cas++) {
		printf("Case %d: ", cas);
		scanf("%d%d", &N, &K);
		build(1, N, 1);
		LL ret = 0;
		for (int i = 0; i < K; i++) {
			int x;
			scanf("%d", &x);
			int tmp = query(x, 1);
			ret += (long long)tmp;
			update(tmp, 1, -1);
		}
		cout << ret << endl;
	}
	return 0;
}
