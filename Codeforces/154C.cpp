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

const int base = 31;
const int maxn = 1000005;
long long h[maxn], p[maxn];
int edge[maxn][2];
int n, m;

int main()
{
	cin >> n >> m;
	p[0] = 1;
	for (int i = 1; i < n; i++)
		p[i] = p[i - 1] * base;
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		a--; b--;
		edge[i][0] = a; edge[i][1] = b;
		h[a] += p[b];
		h[b] += p[a];
	}

	long long ret = 0;
	for (int i = 0; i < m; i++) {
		int a = edge[i][0], b = edge[i][1];
		if (h[a] + p[a] == h[b] + p[b])
			ret++;
	}
	sort(h, h + n);
	for (int i = 0; i < n; i++) {
		int now = i;
		for (; i + 1 < n && h[now] == h[i + 1]; i++);
		long long cnt = i - now + 1;
		ret += cnt * (cnt - 1) / 2;
	}
	cout << ret << endl;
	return 0;
}
