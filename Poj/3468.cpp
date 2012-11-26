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

typedef long long LL;
const int MAXN = 111111;
LL sum[MAXN << 2], add[MAXN << 2];

int lson(int rt)
{
	return rt << 1;
}

int rson(int rt)
{
	return rt << 1 | 1;
}

void pushUp(int rt)
{
	sum[rt] = sum[lson(rt)] + sum[rson(rt)];
}

void pushDown(int rt, int m)
{
	if (add[rt])
	{
		add[lson(rt)] += add[rt];
		add[rson(rt)] += add[rt];
		sum[lson(rt)] += add[rt] * (m - (m >> 1));
		sum[rson(rt)] += add[rt] * (m >> 1);
		add[rt] = 0;
	}
}

void build(int l, int r, int rt)
{
	add[rt] = 0;
	if (l == r)
	{
		cin >> sum[rt];
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, lson(rt));
	build(mid + 1, r, rson(rt));
	pushUp(rt);
}

void update(int L, int R, int c, int l, int r, int rt)
{
	if (L <= l && r <= R)
	{
		add[rt] += c;
		sum[rt] += (LL)c * (r - l + 1);
		return;
	}
	pushDown(rt, r - l + 1);
	int mid = (l + r) >> 1;
	if (L <= mid) update(L, R, c, l, mid, lson(rt));
	if (R > mid) update(L, R, c, mid + 1, r, rson(rt));
	pushUp(rt);
}

LL query(int L, int R, int l, int r, int rt)
{
	if (L <= l && r <= R)
	{
		return sum[rt];
	}
	pushDown(rt, r - l + 1);
	int mid = (l + r) >> 1;
	LL res = 0;
	if (L <= mid) res += query(L, R, l, mid, lson(rt));
	if (mid < R) res += query(L, R, mid + 1, r, rson(rt));
	return res;
}

int main()
{
	freopen("a", "r", stdin);
	int N, Q;
	while (scanf("%d%d", &N, &Q) != EOF)
	{
		build(1, N, 1);
		for (int i = 1; i <= Q; i++)
		{
			char op[5];
			int a, b, c;
			scanf("%s", op);
			if (op[0] == 'Q')
			{
				scanf("%d%d", &a, &b);
				cout << query(a, b, 1, N, 1) << endl;
			}
			else 
			{
				scanf("%d%d%d", &a, &b, &c);
				update(a, b, c, 1, N, 1);
			}
		}
	}
	return 0;
}
