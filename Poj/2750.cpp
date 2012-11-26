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

const int MAXN = 100000 + 10;
struct TNode
{
	int left, right;
	int sum, minV, maxV;
	int lmin, rmin, lmax, rmax;
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

	T[rt].lmin = min(T[lson(rt)].lmin, T[lson(rt)].sum + T[rson(rt)].lmin);
	T[rt].rmin = min(T[rson(rt)].rmin, T[lson(rt)].rmin + T[rson(rt)].sum);
	T[rt].minV = min(min(T[lson(rt)].minV, T[rson(rt)].minV), T[lson(rt)].rmin + T[rson(rt)].lmin);
}

void build(int l, int r, int rt)
{
	T[rt].left = l;
	T[rt].right = r;
	if (l == r)
	{
		T[rt].sum = T[rt].minV = T[rt].maxV = data[r];
		T[rt].lmin = T[rt].lmax = T[rt].rmin = T[rt].rmax = data[r];
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, lson(rt));
	build(mid + 1, r, rson(rt));
	pushUp(rt);
}

void update(int p, int num, int rt)
{
	if (T[rt].left == T[rt].right)
	{
		T[rt].sum = T[rt].maxV = T[rt].minV = num;
		T[rt].lmin = T[rt].lmax = T[rt].rmin = T[rt].rmax = num;
		return;
	}
	int mid = (T[rt].left + T[rt].right) >> 1;
	if (p <= mid) update(p, num, lson(rt));
	else update(p, num, rson(rt));
	pushUp(rt);
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
		int p, num;
		scanf("%d%d", &p, &num);
		update(p, num, 1);
		int ans;
		if (T[1].sum == T[1].maxV) ans = T[1].sum - T[1].minV;
		else ans = max(T[1].maxV, T[1].sum - T[1].minV);
		cout << ans << endl;
	}
	return 0;
}
