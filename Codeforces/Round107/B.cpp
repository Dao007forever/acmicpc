#include <cstdio>
#include <iostream>
using namespace std;

#define mod 1000000007
int f[2222];

int getfather(int x) {
	return f[x] == x ? x : f[x] = getfather(f[x]);
}

void Union(int x, int y) {
	f[getfather(x)] = getfather(y);
}

int main() {
	freopen("B.in", "r", stdin);
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++)
		f[i] = i;
	for (int l = 1; l + k - 1 <= n; l++) {
		int r = l + k - 1;
		for (int i = 0; i < k; i++)
			Union(l + i, r - i);
	}
	long long ret = 1;
	for (int i = 1; i <= n; i++)
		if (f[i] == i) ret = (ret * m) % mod;
	cout << ret << endl;
	return 0;
}
