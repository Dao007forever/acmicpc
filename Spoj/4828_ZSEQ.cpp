#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 5005;
int l[maxn], r[maxn], sum[maxn];
int res[maxn];
int n, m;

bool check(int p) {
	if (p == 1) {
		int tmp = sum[res[p + 1] - 1] - sum[res[p] - 1];
		return (l[p] <= tmp && tmp <= r[p]);
	}
	for (; sum[res[p + 1] - 1] - sum[res[p] - 1] >= l[p]; res[p]++)
		if (sum[res[p + 1] - 1] - sum[res[p] - 1] <= r[p] && check(p - 1)) return true;
	return false;
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &sum[i]);
		sum[i] += sum[i - 1];
	}
	for (int i = 1; i <= m; i++)
		scanf("%d%d", &l[i], &r[i]);
	for (int i = 1; i <= m; i++)
		res[i] = i;
	res[m + 1] = n + 1;
	if (!check(m)) printf("-1\n");
	else {
		for (int i = 2; i < m; i++)
			printf("%d ", res[i] - 1);
		printf("%d\n", res[m] - 1);
	}
	return 0;
}
