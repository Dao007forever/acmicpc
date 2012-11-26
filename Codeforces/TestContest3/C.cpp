#include <cstdio>

int n, s, cnt;
int a[222222];
int ansx[222222], ansy[222222];

bool check() {
	int x = -1, y = -1;
	for (int i = 0; i < n; i++)
		if (a[i] != 0) {
			if (x == -1) x = i;
			else if (y == -1) y = i;
			else break;
		}
	if (x != -1 && y != -1) {
		ansx[cnt] = x + 1; ansy[cnt] = y + 1;
		a[x]--; a[y]--;
		return true;
	}
	return false;
}

int main() {
	freopen("in", "r", stdin);
	scanf("%d%d", &n, &s);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	cnt = 0;
	while (check()) {
		cnt++;
	}
	if (cnt != 0) {
		printf("Yes\n");
		printf("%d\n", cnt);
		for (int i = 0; i < cnt; i++)
			printf("%d %d\n", ansx[i], ansy[i]);
	}
	else printf("No\n");
	return 0;
}
