#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int vis[11111];

int main() {
	freopen("in.txt", "r", stdin);
	int A, a, b, r, M, k;
	cin >> A >> a >> b >> r >> M >> k;
	int x = A;
	memset(vis, -1, sizeof(vis));

	for (int i = 0; ; i++) {
		if (i == k) {
			cout << x << endl;
			return 0;
		}
		if (vis[x] == -1) vis[x] = i;
		else {
			k -= vis[x];
			k %= (i - vis[x]);
			k += vis[x];
			for (int j = 0; j < 11111; j++)
				if (vis[j] == k) {
					cout << j << endl;
					return 0;
				}
		}
		x %= M;
		x = a * x * x + b * x + r;
		x %= M;
	}
	return 0;
}
