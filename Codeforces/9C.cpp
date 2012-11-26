#include <cstdio>

int ans, n;

void Find(int x)
{
	if (x > n) return;
	ans++;
	Find(x * 10);
	Find(x * 10 + 1);
}

int main()
{
	scanf("%d", &n);
	ans = 0;
	Find(1);
	printf("%d\n", ans);
}
