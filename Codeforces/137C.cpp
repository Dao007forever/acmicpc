#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 100005;
pair<int, int> p[maxn];
int n;

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &p[i].first, &p[i].second);
	}
	sort(p, p + n);
	int Max = 0, ret = 0;
	for (int i = 0; i < n; i++) {
		if (p[i].second < Max) ret++;
		else Max = p[i].second;
	}
	printf("%d\n", ret);
	return 0;
}
