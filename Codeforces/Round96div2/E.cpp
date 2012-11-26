#include <cstdio>
#include <cstring>

char op[111];
int m;

int main() {
	scanf("%s", op);
	scanf("%d", &m);
	int n = strlen(op);
	int cnt = 0;
	for (int i = 0; i < n; i++)
		if (op[i] == 'T') cnt++;
	if (cnt <= m) {
		int t = m - cnt;
		if (t % 2 == 0) printf("%d\n", n);
		else printf("%d\n", n - 1);
	} else {

	}
}
