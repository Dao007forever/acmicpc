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

const int MAXN = 55555;
struct TNode
{
	int left, right;
	int sum, maxV;
	int lmax, rmax;
}T[MAXN << 2];
int N, M;
int data[MAXN];

int lson(int rt)
{
	return rt << 1;
}

int rson(int rt)
{
	return (rt << 1) | 1;
}

void pushUp(int rt)
{
	T[rt].sum = T[lson(rt)].sum + T[rson(rt)].sum;

	T[rt].lmax = max(T[lson(rt)].lmax, T[lson(rt)].sum + T[rson(rt)].lmax);
	T[rt].rmax = max(T[rson(rt)].rmax, T[lson(rt)].rmax + T[rson(rt)].sum);
	T[rt].maxV = max(max(T[lson(rt)].maxV, T[rson(rt)].maxV), T[lson(rt)].rmax + T[rson(rt)].lmax);
}

void build(int l, int r, int rt)
{
	T[rt].left = l;
	T[rt].right = r;
	if (l == r)
	{
		T[rt].sum = T[rt].maxV = T[rt].lmax = T[rt].rmax = data[r];
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, lson(rt));
	build(mid + 1, r, rson(rt));
	pushUp(rt);
}

TNode query(int L, int R, int rt)
{
	if (L <= T[rt].left && T[rt].right <= R)
	{
		return T[rt];
	}
	int mid = (T[rt].left + T[rt].right) >> 1;
	if (R <= mid) return query(L, R, lson(rt));
	else if (L > mid) return query(L, R, rson(rt));
	else
	{
		TNode ll = query(L, mid, lson(rt));
		TNode rr = query(mid + 1, R, rson(rt));
		TNode tmp;
		tmp.sum = ll.sum + rr.sum;
		tmp.lmax = max(ll.lmax, ll.sum + rr.lmax);
		tmp.rmax = max(rr.rmax, ll.rmax + rr.sum);
		tmp.maxV = max(max(ll.maxV, rr.maxV), ll.rmax + rr.lmax);
		return tmp;
	}
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		scanf("%d", &data[i]);
	build(1, N, 1);
	scanf("%d", &M);
	for (int i = 1; i <= M; i++)
	{
		int k, a, b;
		scanf("%d%d", &a, &b);
		int ans = query(a, b, 1).maxV;
		cout << ans << endl;
	}
	return 0;
}

