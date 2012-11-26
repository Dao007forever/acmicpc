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
typedef unsigned long long LL;

LL x, y, l, r;

LL calc(LL d) {
	if (d <= y) {
		if (d < x) return 0;
		else return d + 1 - x;
	}
	if (x != y) {
		LL k = (y - 1) / (y - x);
		if (x * k <= d) return calc(x * k - 1) + d + 1 - x * k;
	}
	LL a = d / x;
	if (a * y != d) {
		if (a * y >= d) return calc(a * y) - (a * y - d);
		else return calc(a * y);
	}
	return a * (a + 1) / 2 * (y - x) + a;
}

int main() {
	freopen("in", "r", stdin);
	cin >> x >> y >> l >> r;
	LL R = calc(r);
	LL L = calc(l - 1);
	cout << R - L << endl;
	return 0;
}
