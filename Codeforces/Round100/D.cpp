#include <cstdio>
#include <algorithm>
using namespace std;

int n, a[105];

void solve() {
	int now = 0;
	int ret = 0;
	for (int i = 0; i < n; i++) {
		now += a[i];
		if (now > 350) ret += (now - 350);
	}
	printf("%d %d\n", n, ret);
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	sort(a, a + n);
	int s = 710, tn = 0, now = 0;
	for (tn = 0; tn < n; tn++) {
		now += a[tn];
		if (now > s) break;
	}
	n = tn;
	solve();
}
