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

#define MAXN 20005
struct node {
	int l, r;
}p[MAXN];
int N;
int R[MAXN], L[MAXN];

int Right(int pp, int clp, int crp, int dis) {
	int d, c;
	c = dis + 1;
	if (pp <= clp) c += crp - pp;
	else if (pp >= crp) {
		d = pp - clp;
		d += crp - clp;
		c += d;
	} else {
		c += pp - clp;
		c += crp - clp;
	}
	return c;
}

int Left(int pp, int clp, int crp, int dis ) {
	int d, c;
	c = dis + 1;
	if (pp >= crp) c += pp - clp;
	else if (pp <= clp) {
		d = crp - pp;
		d += crp - clp;
		c += d;
	} else {
		c += crp - pp;
		c += crp - clp;
	}
	return c;
}

void solve() {
	p[N].r = N;
	R[1] = p[1].r - 1;
	L[1] = R[1] + p[1].r - p[1].l;
	for (int i = 2; i <= N; i++) {
		int t1, t2;
		t1 = Right(p[i - 1].l, p[i].l, p[i].r, L[i - 1]);
		t2 = Right(p[i - 1].r, p[i].l, p[i].r, R[i - 1]);
		R[i] = min(t1, t2);
		t1 = Left(p[i - 1].l, p[i].l, p[i].r, L[i - 1]);
		t2 = Left(p[i - 1].r, p[i].l, p[i].r, R[i - 1]);
		L[i] = min(t1, t2);
	}
	cout << R[N] << endl;
}

int main() {
	freopen("in", "r", stdin);
	while (cin >> N && N) {
		for (int i = 1; i <= N; i++)
			cin >> p[i].l >> p[i].r;
		solve();
	}
	return 0;
}
