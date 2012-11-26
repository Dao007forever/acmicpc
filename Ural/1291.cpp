#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

#define abs(x) ((x) > 0 ? (x) : -(x))
const int maxn = 1005;
int n;
int cogs[maxn], vis[maxn], numer[maxn], denom[maxn];
bool adj[maxn][maxn];

int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

void calc(int x, int y) {
	numer[y] = -numer[x] * cogs[x];
	denom[y] = denom[x] * cogs[y];
	int g = gcd(abs(numer[y]), denom[y]);
	numer[y] /= g;
	denom[y] /= g;
}

void search(int u) {
	for (int i = 1; i <= n; i++)
		if (adj[u][i] && !vis[i]) {
			calc(u, i);
			vis[i] = true;
			search(i);
		}
}

int main() {
	freopen("in.txt", "r", stdin);
	memset(adj, 0, sizeof(adj));
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &cogs[i]);
		int x;
		while (scanf("%d", &x) && x) {
			adj[i][x] = 1;
		}
	}
	for (int i = 1; i <= n; i++)
		denom[i] = 1;
	int x;
	scanf("%d", &x);
	scanf("%d", &numer[x]);
	vis[x] = true;
	search(x);
	for (int i = 1; i <= n; i++)
		printf("%d/%d\n", numer[i], denom[i]);
	return 0;
}
