#include <cstdio>
#include <cstring>
#define abs(x) ((x) > 0 ? x : -(x))
const int maxn = 5005;
char s1[maxn], s2[maxn];

int main() {
	freopen("in.txt", "r", stdin);
	int a = 0, b = 0, c = 0, d = 0, n;
	scanf("%s", s1);
	scanf("%s", s2);
	n = strlen(s1);
	for (int i = 0; i < n; i++)
		a += (s1[i] == '+'), b += (s1[i] == '-');
	n = strlen(s2);
	for (int i = 0; i < n; i++)
		c += (s2[i] == '+'), d += (s2[i] == '-');
	if (a != c || b != d) {
		printf("-1\n");
		return 0;
	}
	int ret = 0, l = -1, r = -1;
	for (int i = 0; i < a; i++) {
		l++;
		for (; s1[l] != '+'; l++);
		r++;
		for (; s2[r] != '+'; r++);
		ret += abs(l - r);
	}
	printf("%d\n", ret);
	return 0;
}
