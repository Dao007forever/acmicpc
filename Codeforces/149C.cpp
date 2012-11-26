#include <vector>
#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 200005;
int n;
struct node {
	int a, id;
}p[maxn];

bool cmp(node A, node B) {
	return A.a < B.a;
}

int main() {
	freopen("in", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &p[i].a), p[i].id = i + 1;
	sort(p, p + n, cmp);
	printf("%d\n", (n + 1) / 2);
	for (int i = 0; i < n; i += 2)
		printf("%d ", p[i].id);
	printf("\n%d\n", n / 2);
	for (int i = 1; i < n; i += 2)
		printf("%d ", p[i].id);
	return 0;
}
