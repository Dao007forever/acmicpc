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

#define MAXN 100005
struct SegTree {
	int n;
	LL sum[MAXN << 2];

	void build() {
		memset(sum, 0, sizeof(sum));
	}

	void update(int p, int c, int l, int r, int rt) {
		if (l == r) {
			sum[rt] += c;
			return;
		}
		int mid = (l + r) >> 1;
		if (p <= mid) update(p, c, l, mid, rt << 1);
		else update(p, c, mid + 1, r, rt << 1 | 1);
		sum[rt] = sum[rt << 1] + sum[rt << 1 | 1];
	}

	LL Sum(int L, int R, int l, int r, int rt) {
		if (L <= l && r <= R) {
			return sum[rt];
		}
		int mid = (l + r) >> 1;
		LL ret = 0;
		if (L <= mid) ret += Sum(L, R, l, mid, rt << 1);
		if (R > mid) ret += Sum(L, R, mid + 1, r, rt << 1 | 1);
		return ret;
	}

	LL query(int n, int L, int R, int mod, int tmp) {
		while (R >= 0 && R % mod != tmp) {
			R--;
		}
		while (L < n && L % mod != tmp) {
			L++;
		}
		if (L > R) return 0;
		return Sum(L / mod, R / mod, 0, n / mod + 1, 1);
	}
}tree[5][13];

int base = 2;
LL coeffient[7][13];
int n, m;
LL a[MAXN];
int main(int argc, char const *argv[])
{
	for (int z = 2; z <= 6; z++) {
		int mod = 2 * (z - 1);
		for (int i = 1; i <= mod; i++) {
			if (i % mod == 0) {
				coeffient[z][i - 1] = 2;
			} else if (i % mod <= z) {
				coeffient[z][i - 1] = i % mod;
			} else {
				coeffient[z][i - 1] = 2 * z - (i % mod);
			}
		}
	}
	cin >> n;
	for (int z = 2; z <= 6; z++) {
		int mod = 2 * (z - 1);
		for (int i = 0; i < mod; i++)
			tree[z - base][i].build();
	}
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		for (int z = 2; z <= 6; z++) {
			int mod = 2 * (z - 1);
			tree[z - base][i % mod].update(i / mod, a[i], 0, n / mod + 1, 1);
		}
	}
	cin >> m;
	while (m--) {
		int type;
		cin >> type;
		if (type == 1) {
			int p; LL v;
			cin >> p >> v;
			p--;
			for (int z = 2; z <= 6; z++) {
				int mod = 2 * (z - 1);
				tree[z - base][p % mod].update(p / mod, v - a[p], 0, n / mod + 1, 1);
			}
			a[p] = v;
		} else {
			int l, r, z;
			cin >> l >> r >> z;
			l--; r--;
			int mod = 2 * (z - 1);
			LL ret = 0;
			for (int d = 0; d < mod; d++) {
				int tmp = (l + d) % mod;
				ret += tree[z - base][tmp].query(n, l, r, mod, tmp) * coeffient[z][d];
			}
			cout << ret << endl;
		}
	}
	return 0;
}