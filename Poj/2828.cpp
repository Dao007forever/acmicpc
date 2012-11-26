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

const int MAXN = 222222;
int remain[MAXN << 2];
int pos[MAXN], val[MAXN], newpos[MAXN];

int lson(int rt)
{
	return rt << 1;
}

int rson(int rt)
{
	return rt << 1 | 1;
}

void build(int l, int r, int rt)
{
	remain[rt] = r - l + 1;
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(l, mid, lson(rt));
	build(mid + 1, r, rson(rt));
}

int query(int id, int l, int r, int rt)
{
	remain[rt]--;
	if (l == r) return l;
	int mid = (l + r) >> 1;
	if (remain[lson(rt)] >= id) return query(id, l, mid, lson(rt));
	else return query(id - remain[lson(rt)], mid + 1, r, rson(rt));
}

int main()
{
	freopen("a", "r", stdin);
	int n;
	while (scanf("%d", &n) != EOF)
	{
		build(1, n, 1);
		for (int i = 1; i <= n; i++)
			scanf("%d%d", &pos[i], &val[i]);
		for (int i = n; i >= 1; i--)
			newpos[query(pos[i] + 1, 1, n, 1)] = i;
		for (int i = 1; i <= n; i++)
			printf("%d ", val[newpos[i]]);
		puts("");
	}
	return 0;
}
