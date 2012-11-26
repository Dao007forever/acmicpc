#include <cstdio>

int main()
{
	int n, x, y;
	scanf("%d%d%d", &n, &x, &y);
	n /= 2;
	bool flag = true;
	if (x == n && y == n) flag = false;
	if (x == n && y == n + 1) flag = false;
	if (x == n + 1 && y == n) flag = false;
	if (x == n + 1 && y == n + 1) flag = false;
	if (flag) printf("YES\n");
	else printf("NO\n");
	return 0;
}
