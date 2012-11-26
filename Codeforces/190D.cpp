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
/*------------#include omitted-----------*/
#define MAXN 400005
struct SegTree {
	struct node {
		int l, r, max;
	}T[MAXN << 2];

	int lson(int rt) {return rt << 1; }

	int rson(int rt) {return rt << 1 | 1; }

	void build(int l, int r, int rt) {
		T[rt].l = l; T[rt].r = r; T[rt].max = 0;
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(l, mid, lson(rt));
		build(mid + 1, r, rson(rt));
	}

	void update(int p, int c, int rt) {
		if (T[rt].l == T[rt].r) {
			T[rt].max += c;
			return;
		}
		int mid = (T[rt].l + T[rt].r) >> 1;
		if (p <= mid) update(p, c, lson(rt));
		else update(p, c, rson(rt));
		pushUp(rt);
	}

	void pushUp(int rt) {
		T[rt].max = max(T[lson(rt)].max, T[rson(rt)].max);
	}

	int getMax() {
		return T[1].max;
	}
}tree;

map<int, int> mp;
int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	vector<int> a(n);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	vector<int> b(n);
	b = a;
	sort(b.begin(), b.end());
	b.resize(unique(b.begin(), b.end()) - b.begin());
	for (int i = 0; i < b.size(); i++)
		mp[b[i]] = i + 1;
	tree.build(1, b.size(), 1);
	LL ret = 0;
	int r = 0;
	for (int l = 0; l < n; l++) {
		while (tree.getMax() < k && r < n) {
			tree.update(mp[a[r++]], 1, 1);
		}
		if (tree.getMax() >= k)
			ret += n - r + 1;
		tree.update(mp[a[l]], -1, 1);
	}
	cout << ret << endl;
	return 0;

}
