#include <set>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 305;
int map[maxn][maxn], pre[maxn], fir[maxn], sec[maxn], res[maxn], n;

void init() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			scanf("%d", &map[i][j]);
	for (int i = 1, t; i <= n; i++) {
		scanf("%d", &t);
		pre[t] = i;
	}
}
int main() {
	freopen("in.txt", "r", stdin);
	init();
	fir[1] = 1;
	sec[1] = 0;
	for (int i = 2; i <= n; i++) {
		fir[i] = fir[i - 1];
		sec[i] = sec[i - 1];
		if (pre[i] < pre[fir[i - 1]]) {
			fir[i] = i;
			sec[i] = fir[i - 1];
		} else if (sec[i - 1] == 0 || pre[i] < pre[sec[i - 1]]) {
			sec[i] = i;
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) if (map[i][j] != i) {
			int f= 0, s = map[i][j];
			int k = 1;
			for (k = 1; k <= n; k++) 
				if (fir[k] == s || (fir[k] == i && sec[k] == s)) {
					f = 1;
					break;
				}
			if (f == 1) {
				res[i] = k;
				break;
			}
		}
	}
	for (int i = 1; i < n; i++)
		cout << res[i] << " ";
	cout << res[n] << endl;
}
