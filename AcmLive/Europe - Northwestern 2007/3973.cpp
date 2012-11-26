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

#define abs(x) ((x) > 0 ? (x) : -(x))
const long long inf = 1LL << 60;
long long n;

int main() {
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	while (Test--) {
		cin >> n;
		n = (n + 4) / 5;
		long long mid = sqrt(n * 40 / 88);

		long long ans = -1, ansx = 0, ansy = 0;
		for (long long y = mid - 10000; y <= mid + 10000; y++)
			if (y >= 1) {
				long long x = n / y;
				while (x * y < n) x++;

				long long nowx = x * 10 + 2, nowy = 44 * y + 4;
				if (nowx > nowy) swap(nowx, nowy);
				long long now = nowx * nowy;

				if (ans < 0 || now < ans || (now == ans && nowy - nowx < ansy - ansx)) {
					ans = now;
					ansx = nowx;
					ansy = nowy;
				}
			}
		cout << ansy << " X " << ansx << " = " << ans << endl;
	}
	return 0;
}
