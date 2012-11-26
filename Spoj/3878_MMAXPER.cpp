/*
 * DP
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

const int maxn = 1005;
int n;
int a[maxn], b[maxn];
int f[maxn], g[maxn];

int main()
{
	cin >> n;
	for (int i = 1; i <= n; i++)
		cin >> a[i] >> b[i];
	f[1] = b[1], g[1] = a[1];
	for (int i = 1; i < n; i++) {
		f[i + 1] = max(f[i + 1], f[i] + b[i + 1] + abs(a[i] - a[i + 1]));
		f[i + 1] = max(f[i + 1], g[i] + b[i + 1] + abs(b[i] - a[i + 1]));
		g[i + 1] = max(g[i + 1], f[i] + a[i + 1] + abs(a[i] - b[i + 1]));
		g[i + 1] = max(g[i + 1], g[i] + a[i + 1] + abs(b[i] - b[i + 1]));
	}
	cout << max(f[n], g[n]) << endl;
	return 0;
}
