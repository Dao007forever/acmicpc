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
#define MAXN 100005
const int mod = 9901;
struct BinaryIndexTree {
	int n;
	int C[MAXN];

	void init(int n) {
		this->n = n;
		memset(C, 0, sizeof(C));
	}

	int lowbit(int x) {
		return x & (-x);
	}

	void add(int p, int num) {
		for (int i = p; i <= n; i += lowbit(i))
			C[i] = (C[i] + num) % mod;
	}

	int sum(int p) {
		int ret = 0;
		for (int i = p; i > 0; i -= lowbit(i))
			ret = (ret + C[i]) % mod;
		return ret;
	}
}tree;

int n, d;
int a[MAXN];
vector<int> v;

int Bin(int x) {
	int l = 0, r = v.size() - 1;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (x == v[mid]) return mid;
		if (x > v[mid]) l = mid + 1;
		else r = mid - 1;
	}
}

//>=x
int Bin1(int x) {
	int l = 0, r = v.size() - 1, ret = 0;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (v[mid] >= x) {
			r = mid - 1;
			ret = mid;
		} else l = mid + 1;
	}
	return ret;
}

//<=x
int Bin2(int x) {
	int l = 0, r = v.size() - 1, ret = 0;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (v[mid] <= x) {
			l = mid + 1;
			ret = mid;
		} else r = mid - 1;
	}
	return ret;
}

int main() {
	freopen("in.txt", "r", stdin);
	while (~scanf("%d%d", &n, &d)) {
		v.clear();
		for (int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			v.push_back(a[i]);
		}
		sort(v.begin(), v.end());
		v.resize(unique(v.begin(), v.end()) - v.begin());

		//dp
		int ret = 0;
		tree.init(n);
		for (int i = 0; i < n; i++) {
			int idx = Bin(a[i]);
			int l = Bin1(a[i] - d), r = Bin2(a[i] + d);
			int tmp = (tree.sum(r + 1) - tree.sum(l)) % mod;
			if (tmp < 0) tmp += mod;
			ret += tmp + 1;
			ret %= mod;
			tree.add(idx + 1, tmp + 1);
		}
		ret = ((ret - n) % mod + mod) % mod;
		printf("%d\n", ret);
	}
	return 0;
}
