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

const int MAXN = 111111;
struct TNode
{
	int left, right;
	int lmax, rmax, max;
	int lval, rval, len;
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

int MAX(int a, int b, int c, int d, int e)
{
	int ans = a;
	ans = max(ans, b);
	ans = max(ans, c);
	ans = max(ans, d);
	ans=  max(ans, e);
	return ans;
}

void pushUp(int rt)
{
	T[rt].lval = T[lson(rt)].lval;
	T[rt].rval = T[rson(rt)].rval;
	if (T[lson(rt)].rval < T[rson(rt)].lval)
	{
		if (T[lson(rt)].len == T[lson(rt)].lmax)
		{
			T[rt].lmax = T[lson(rt)].len + T[rson(rt)].lmax;
		}
		else T[rt].lmax = T[lson(rt)].lmax;
		if (T[rson(rt)].len == T[rson(rt)].rmax)
		{
			T[rt].rmax = T[rson(rt)].len + T[lson(rt)].rmax;
		}
		else T[rt].rmax = T[rson(rt)].rmax;
		T[rt].max = MAX(T[lson(rt)].rmax + T[rson(rt)].lmax, T[lson(rt)].max, T[rson(rt)].max, T[rt].lmax, T[rt].rmax);
	}
	else
	{
		T[rt].lmax = T[lson(rt)].lmax;
		T[rt].rmax = T[rson(rt)].rmax;
		T[rt].max = max(max(T[lson(rt)].max, T[rson(rt)].max), max(T[rt].lmax, T[rt].rmax));
	}
}

void build(int l, int r, int rt)
{
	T[rt].left = l;
	T[rt].right = r;
	T[rt].len = r - l + 1;
	if (l == r)
	{
		T[rt].max = T[rt].lmax = T[rt].rmax = 1;
		T[rt].lval = T[rt].rval = data[r];
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
		tmp.lval = ll.lval;
		tmp.rval = rr.rval;
		tmp.len = ll.len + rr.len;
		if (ll.rval < rr.lval)
		{
			if (ll.len == ll.lmax)
			{
				tmp.lmax = ll.len + rr.lmax;
			}
			else tmp.lmax = ll.lmax;
			if (rr.len == rr.rmax)
			{
				tmp.rmax = rr.len + ll.rmax;
			}
			else tmp.rmax = rr.rmax;
			tmp.max = MAX(ll.rmax + rr.lmax, ll.max, rr.max, tmp.lmax, tmp.rmax);
		}
		else
		{
			tmp.lmax = ll.lmax;
			tmp.rmax = rr.rmax;
			tmp.max = max(max(ll.max, rr.max), max(tmp.lmax, tmp.rmax));
		}
		return tmp;
	}
}

void update(int p, int c, int rt)
{
	if (T[rt].left == T[rt].right)
	{
		T[rt].lval = T[rt].rval = c;
		return;
	}
	int mid = (T[rt].left + T[rt].right) >> 1;
	if (p <= mid) update(p, c, lson(rt));
	else update(p, c, rson(rt));
	pushUp(rt);
}

int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		scanf("%d%d", &N, &M);
		for (int i = 1; i <= N; i++)
			scanf("%d", &data[i]);
		build(1, N, 1);
		char op[5];
		int a, b;
		for (int i = 1; i <= M; i++)
		{
			scanf("%s%d%d", op, &a, &b);
			if (op[0] == 'Q')
			{
				a++; b++;
				int res = query(a, b, 1).max;
				cout << res << endl;
			}
			else
			{
				a++;
				update(a, b, 1);
			}
		}
	}
	return 0;
}
