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

long long n, m, v;

int main() {
	cin >> n >> m >> v;
	if (m < n - 1 || m > n - 1 + (n - 2) * (n - 3) / 2) {
		puts("-1");
		return 0;
	}
	int w = v % n + 1;
	m -= n - 1;
	for (int i = 1; i <= n; i++)
		if (i != v) {
			cout << i << " " << v << endl;
		}
	for (int i = 1; i <= n && m; i++)
		for (int j = i + 1; j <= n && m; j++)
			if (i != v && i != w && j != v && j != w) {
				printf("%d %d\n", i, j);
				m--;
			}
	return 0;
}
