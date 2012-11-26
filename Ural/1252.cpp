#include <cstdio>
#include <algorithm>
using namespace std;
#define abs(x) ((x) > 0 ? x : -(x))
const int maxn = 130000;
int n;
struct node {
	int p1, p2, val;
}p[maxn + 5];

int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

bool cmp1(node A, node B) {
	return A.val < B.val;
}

bool cmp2(node A, node B) {
	return A.val > B.val;
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &p[i].val);
		p[i].p1 = i;
	}
	
	sort(p, p + n, cmp1);
	for (int i = 0; i < n; i++)
		p[i].p2 = i;
	int ret1 = 0;
	for (int i = 0; i < n; i++) {
		int tmp = abs(p[i].p1 - p[i].p2);
		if (!ret1) ret1 = tmp;
		else ret1 = gcd(ret1, tmp);
	}

	int ret2 = 0;
	sort(p, p + n, cmp2);
	for (int i = 0; i < n; i++)
		p[i].p2 = i;
	for (int i = 0; i < n; i++) {
		int tmp = abs(p[i].p1 - p[i].p2);
		if (!ret2) ret2 = tmp;
		else ret2 = gcd(ret2, tmp);
	}

	if (!ret1 || !ret2) {
		printf("%d\n", n - 1);
		return 0;
	}
	printf("%d\n", max(ret1, ret2) - 1);
	return 0;
}
