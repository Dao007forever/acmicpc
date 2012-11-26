#include <cstdio>

int main()
{
	int a, b;
	scanf("%d:%d", &a, &b);
	a %= 12;
	double x = b * 0.5;
	x += a * 30;
	int y = b * 6;
	printf("%.1lf %d\n", x, y);
	return 0;
}
