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

const int maxn = 1000005;
struct BinaryIndexTree {
	int N;
	int C[maxn];
	
	void init(int N) {
		this->N = N;
		memset(C, 0, sizeof(C));
	}
	
	int lowbit(int x) {
		return x & (-x);
	}
	
	void add(int x, int num) {
		for (int i = x; i <= N; i += lowbit(i))
			C[i] += num;
	}
	
	int sum(int x) {
		int ret = 0;
		for (int i = x; i > 0; i -= lowbit(i))
			ret += C[i];
		return ret;
	}
}T;

int n;
int a[maxn], b[maxn];
int l[maxn], r[maxn];

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		b[i] = a[i];
	}
	sort(b, b + n);
	for (int i = 0; i < n; i++)
		a[i] = lower_bound(b, b + n, a[i]) - b + 1;
	T.init(n);
	for (int i = 0; i < n; i++) {
		l[i] = i - T.sum(a[i]);
		T.add(a[i], 1);
	}
	T.init(n);
	for (int i = n - 1; i >= 0; i--) {
		r[i] = T.sum(a[i]);
		T.add(a[i], 1);
	}
	LL ret = 0;
	for (int i = 0; i < n; i++)
		ret += (LL)l[i] * r[i];
	cout << ret << endl;
	return 0;
}
