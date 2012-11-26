#include <cstdio>
#include <cstring>

char str[100010];
int main()
{
	scanf("%s", str);
	int ans = 0, sum = 0;
	int len = strlen(str);
	if (len == 1)
	{
		printf("0\n");
		return 0;
	}
	for (int i = 0; i < len; i++)
		sum += str[i] - '0';
	ans++;
	while (sum >= 10)
	{
		int tmp = 0;
		while (sum > 0)
		{
			tmp += sum % 10;
			sum /= 10;
		}
		sum = tmp;
		ans++;
	}
	printf("%d\n", ans);
	return 0;
}
