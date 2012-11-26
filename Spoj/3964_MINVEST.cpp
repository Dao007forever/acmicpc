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

const int maxn = 100000;
int a[11], b[11];
int s, n, m;
int f[111111];

int main() {
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	while (Test--) {
		cin >> s >> m >> n;
		for (int i = 0; i < maxn; i++)
			f[i] = i * 1000;
		for (int i = 0; i < n; i++) {
			cin >> a[i] >> b[i];
			a[i] /= 1000;
		}
		for (int i = 0; i < n; i++)
			for (int j = a[i]; j <= maxn; j++)
				f[j] = max(f[j], f[j - a[i]] + a[i] * 1000 + b[i]);
		for (int i = 0; i < m; i++)
			s = f[s / 1000] + s % 1000;
		cout << s << endl;
	}
	return 0;
}
