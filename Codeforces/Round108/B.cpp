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

typedef long long LL;
LL n, m, cx, cy;
int K;
LL x[11111], y[11111];

int main() {
	cin >> n >> m;
	cin >> cx >> cy;
	cin >> K;
	for (int i = 0; i < K; i++) {
		cin >> x[i] >> y[i];
	}

	LL ret = 0;
	for (int i = 0; i < K; i++) {
		LL dx, dy;
		if (x[i] != 0) {
			if (x[i] > 0)
				dx = (n - cx) / x[i];
			else dx = (cx - 1) / (-x[i]);
		}
		else dx = 1LL << 30;
		if (y[i] != 0) {
			if (y[i] > 0)
				dy = (m - cy) / y[i];
			else dy = (cy - 1) / (-y[i]);
		}
		else dy = 1LL << 30;
		LL tmp = min(dx, dy);
		ret += tmp;
		cx = cx + tmp * x[i];
		cy = cy + tmp * y[i];
	}
	cout << ret << endl;
}
