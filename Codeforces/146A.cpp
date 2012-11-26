#include <cstdio>

int n;
char s[55];

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &n);
	scanf("%s", s + 1);
	int s1 = 0, s2 = 0;
	for (int i = 1; i <= n; i++) {
		if (s[i] == '4' || s[i] == '7') {
			if (i <= n / 2) s1 += s[i] - '0';
			else s2 += s[i] - '0';
		}
		else {
			printf("NO\n");
			return 0;
		}
	}
	if (s1 == s2) printf("YES\n");
	else printf("NO\n");
	return 0;
}
