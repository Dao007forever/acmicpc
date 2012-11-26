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
struct node {
	int x, y, radius, id, f, g;
}p[maxn];
struct TNode {
	int l, r, Max;
}T[maxn << 2];
int N;
int f[maxn], g[maxn];

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
	T[rt].Max = max(T[lson(rt)].Max, T[rson(rt)].Max);
}

void build(int l, int r, int rt)
{
	T[rt].l = l; T[rt].r = r;
	if (l == r) {
		T[rt].Max = -1000000;
		return;
	}
	int mid = (l + r) >> 1;
	build(l, mid, lson(rt));
	build(mid + 1, r, rson(rt));
	pushUp(rt);
}

int query(int L, int R, int rt)
{
	if (L <= T[rt].l && T[rt].r <= R) {
		return T[rt].Max;
	}
	int mid = (T[rt].l + T[rt].r) >> 1;
	int ret = -1000000;
	if (L <= mid) ret = max(ret, query(L, R, lson(rt)));
	if (R > mid) ret = max(ret, query(L, R, rson(rt)));
	return ret;
}

void update(int p, int c, int rt)
{
	if (T[rt].l == T[rt].r) {
		T[rt].Max = max(T[rt].Max, c);
		return;
	}
	int mid = (T[rt].l + T[rt].r) >> 1;
	if (p <= mid) update(p, c, lson(rt));
	else update(p, c, rson(rt));
	pushUp(rt);
}

bool cmpX(node A, node B)
{
	return A.x - A.radius < B.x - B.radius;
}

bool cmpY(node A, node B)
{
	return A.y + A.radius > B.y + B.radius;
}

void solveF()
{
	build(1, N, 1);
	for (int i = 1; i <= N; i++) {
		int dest = p[i].x - p[i].radius;
		int l = 1, r = i, ans;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (p[mid].x >= dest) {
				ans = mid;
				r = mid - 1;
			} else l = mid + 1;
		}
		p[i].f = 1 - i;
		for (int j = ans; j < i; j++)
			p[i].f = max(p[i].f, p[j].f - j);
		/*if (ans < i) {
			int tmp = query(ans, i - 1, 1);
			p[i].f = max(p[i].f, tmp);
		}*/
		p[i].f += i;
		//update(i, p[i].f - i, 1);
	}
}

void solveG()
{
	build(1, N, 1);
	for (int i = 1; i <= N; i++) {
		int dest = p[i].y + p[i].radius;
		int l = 1, r = i, ans;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (p[mid].y <= dest) {
				ans = mid;
				r = mid - 1;
			} else l = mid + 1;
		}
		p[i].g = 1 - i;
		for (int j = ans; j < i; j++)
			p[i].g = max(p[i].g, p[j].g - j);
		/*if (ans < i) {
			int tmp = query(ans, i - 1, 1);
			p[i].g = max(p[i].g, tmp);
		}*/
		p[i].g += i;
		//update(i, p[i].g - i, 1);
	}
}

int main()
{
	freopen("in", "r", stdin);
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> p[i].x;
		p[i].y = p[i].x;
		p[i].id = i;
	}
	for (int i = 1; i <= N; i++) {
		cin >> p[i].radius;
	}
	sort(p + 1, p + N + 1, cmpX);
	solveF();
	sort(p + 1, p + N + 1, cmpY);
	solveG();

	for (int i = 1; i <= N; i++)
		f[p[i].id] = p[i].f, g[p[i].id] = p[i].g;
	int ret = 0, retk;
	for (int i = 1; i <= N; i++) {
		if (f[i] + g[i] - 1 > ret) {
			ret = f[i] + g[i] - 1;
			retk = i;
		}
	}
	cout << retk << " " << ret << endl;
	return 0;
}
