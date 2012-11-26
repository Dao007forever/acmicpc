#include <cstdio>

int n, k, m;

int main()
{
	scanf("%d%d%d", &n, &k, &m);
	if (n == m || k >= 4) printf("YES\n");
	else printf("NO");
	return 0;
}
