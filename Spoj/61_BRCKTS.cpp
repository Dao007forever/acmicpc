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

const int MAXN = 33333;
const int inf = 100000000;
int psum[MAXN];
char str[MAXN];
int MIN[MAXN << 2], add[MAXN << 2];

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
	MIN[rt] = min(MIN[lson(rt)], MIN[rson(rt)]);
}

void pushDown(int rt)
{
	if (add[rt])
	{
		add[lson(rt)] += add[rt];
		MIN[lson(rt)] += add[rt];

		add[rson(rt)] += add[rt];
		MIN[rson(rt)] += add[rt];

		add[rt] = 0;
	}
}

void build(int l, int r, int rt)
{
	add[rt] = 0;
	MIN[rt] = inf;
	if (l == r)
	{
		MIN[rt] = psum[l];
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
		MIN[rt] += c;
		return;
	}
	pushDown(rt);
	int mid = (l + r) >> 1;
	if (L <= mid) update(L, R, c, l, mid, lson(rt));
	if (R > mid) update(L, R, c, mid + 1, r, rson(rt));
	pushUp(rt);
}

int main()
{
	freopen("a", "r", stdin);
	int n, m;
	for (int cas = 1; cas <= 10; cas++)
	{
		memset(psum, 0, sizeof(psum));
		printf("Test %d:\n", cas);
		scanf("%d", &n);
		scanf("%s", str + 1);
		for (int i = 1; i <= n; i++)
		if (str[i] == '(')
			psum[i] = psum[i - 1] + 1;
		else psum[i] = psum[i - 1] - 1;
		int Sum = psum[n];
		build(1, n, 1);

		scanf("%d", &m);
		for (int i = 1; i <= m; i++)
		{
			int tmp;
			scanf("%d", &tmp);
			if (tmp == 0)
			{
				if (Sum == 0 && MIN[1] >= 0) printf("YES\n");
				else printf("NO\n");
			}
			else
			{
				if (str[tmp] == '(')
				{
					str[tmp] = ')';
					Sum -= 2;
					update(tmp, n, -2, 1, n, 1);
				}
				else 
				{
					str[tmp] = '(';
					Sum += 2;
					update(tmp, n, 2, 1, n, 1);
				}
			}
		}
	}
	return 0;
}
