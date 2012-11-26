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
#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

const int maxn = 50005;
struct SegTree {
	int n;
	int sum[maxn << 2];
	int lson(int rt) {
		return rt << 1;
	}
	int rson(int rt) {
		return rt << 1 | 1;
	}
	void build(int l, int r, int rt) {
		sum[rt] = 0;
		if (l == r) return;
		int mid = (l + r) >> 1;
		build(l, mid, lson(rt));
		build(mid + 1, r, rson(rt));
	}
	int query(int L, int R, int l, int r, int rt) {
		if (L <= l && r <= R) {
			return sum[rt];
		}
		int mid = (l + r) >> 1;
		int ret = 0;
		if (L <= mid) ret += query(L, R, l, mid, lson(rt));
		if (R > mid) ret += query(L, R, mid + 1, r, rson(rt));
		return ret;
	}
	void update(int p, int l, int r, int rt) {
		if (l == r) {
			sum[rt]++;
			return;
		}
		int mid = (l + r) >> 1;
		if (p <= mid) update(p, l, mid, lson(rt));
		else update(p, mid + 1, r, rson(rt));
		sum[rt] = sum[lson(rt)] + sum[rson(rt)];
	}
}tree;

int n;
int x[maxn], y[maxn];
vector<pair<pair<int, int>, int> > p;
int a1[maxn], a2[maxn], a3[maxn], a4[maxn];
int l1[maxn], l2[maxn], l3[maxn], l4[maxn];

/*
 *   1   |   4   
 *---------------
 *   2   |   3   
 */
void solve() {
	//Count #points in Area 1
	p.clear(); tree.build(1, n, 1);
	for (int i = 0; i < n; i++) {
		p.PB(MP(MP(-y[i], x[i]), i));
	}
	sort(p.begin(), p.end());
	for (int i = 0; i < n; i++) {
		int pos = p[i].first.second, idx = p[i].second;
		a1[idx] = tree.query(1, pos, 1, n, 1);
		l1[idx] = tree.query(pos, pos, 1, n, 1);
		tree.update(pos, 1, n, 1);
	}

	//Count #points in Area2
	p.clear(); tree.build(1, n, 1);
	for (int i = 0; i < n; i++) {
		p.PB(MP(MP(x[i], y[i]), i));
	}
	sort(p.begin(), p.end());
	for (int i = 0; i < n; i++) {
		int pos = p[i].first.second, idx = p[i].second;
		a2[idx] = tree.query(1, pos, 1, n, 1);
		l2[idx] = tree.query(pos, pos, 1, n, 1);
		tree.update(pos, 1, n, 1);
	}

	//Count #points in Area3
	p.clear(); tree.build(1, n, 1);
	for (int i = 0; i < n; i++) {
		p.PB(MP(MP(y[i], -x[i]), i));
	}
	sort(p.begin(), p.end());
	for (int i = 0; i < n; i++) {
		int pos = -p[i].first.second, idx = p[i].second;
		a3[idx] = tree.query(pos, n, 1, n, 1);
		l3[idx] = tree.query(pos, pos, 1, n, 1);
		tree.update(pos, 1, n, 1);
	}

	//Count #points in Area4
	p.clear(); tree.build(1, n, 1);
	for (int i = 0; i < n; i++) {
		p.PB(MP(MP(-x[i], -y[i]), i));
	}
	sort(p.begin(), p.end());
	for (int i = 0; i < n; i++) {
		int pos = -p[i].first.second, idx = p[i].second;
		a4[idx] = tree.query(pos, n, 1, n, 1);
		l4[idx] = tree.query(pos, pos, 1, n, 1);
		tree.update(pos, 1, n, 1);
	}
}

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d%d", x + i, y + i);
		std::vector<pair<int, int> > v(n);
		for (int i = 0; i < n; i++) {
			v[i] = MP(x[i], i);
		}
		sort(v.begin(), v.end());
		x[v[0].second] = 1;
		for (int i = 1, r = 1; i < n; i++) {
			if (v[i].first != v[i - 1].first) {
				r++;
			}
			x[v[i].second] = r;
		}

		for (int i = 0; i < n; i++) {
			v[i] = MP(y[i], i);
		}
		sort(v.begin(), v.end());
		y[v[0].second] = 1;
		for (int i = 1, r = 1; i < n; i++) {
			if (v[i].first != v[i - 1].first) {
				r++;
			}
			y[v[i].second] = r;
		}
/*		std::vector<int> v;
		std::map<int, int> mp;
		for (int i = 0; i < n; i++) {
			v.PB(x[i]);
		}
		sort(v.begin(), v.end());
		v.resize(unique(v.begin(), v.end()) - v.begin());
		for (int i = 0; i < v.size(); i++)
			mp[v[i]] = i + 1;
		for (int i = 0; i < n; i++)
			x[i] = mp[x[i]];

		v.clear(); mp.clear();
		for (int i = 0; i < n; i++) {
			v.PB(y[i]);
		}
		sort(v.begin(), v.end());
		v.resize(unique(v.begin(), v.end()) - v.begin());
		for (int i = 0; i < v.size(); i++)
			mp[v[i]] = i + 1;
		for (int i = 0; i < n; i++)
			y[i] = mp[y[i]];*/

		memset(a1, 0, sizeof(a1));
		memset(a2, 0, sizeof(a2));
		memset(a3, 0, sizeof(a3));
		memset(a4, 0, sizeof(a4));
		memset(l1, 0, sizeof(l1));
		memset(l2, 0, sizeof(l2));
		memset(l3, 0, sizeof(l3));
		memset(l4, 0, sizeof(l4));
		solve();
		LL ret = 0;
		for (int i = 0; i < n; i++)
			ret += 2ll*a1[i]*a3[i] + 2ll*a2[i]*a4[i] - 2ll*l1[i]*l3[i] - 2ll*l2[i]*l4[i];
		cout << ret << endl;
	}
	return 0;
}