#include <cstdio>
#include <cstring>

const int maxn = 1000000;
bool flag[maxn];
int prime[maxn], D[maxn];

int main()
{
	for (int i = 2; i <= maxn; i++)
	if (!flag[i])
		for (int j = i * 2; j <= maxn; j += i)
			flag[j] = true;

	for (int i = 1; i <= maxn; i++)
		D[i] = 1;

	int num = 0;
	for (int i = 2; i <= maxn; i++)
	if (!flag[i])
	{
		prime[++num] = i;
		for (int j = i; j <= maxn; j += i)
		{
			int k = j, cnt = 0;
			while (k % i == 0)
				k /= i, cnt++;
			D[j] *= cnt + 1;
		}
	}
	memset(flag, 0, sizeof(flag));
	for (int i = 1; i <= num; i++)
	{
		int limit = maxn / prime[i];
		for (int j = i + 1; j <= num && prime[j] <= limit; j++)
			flag[prime[i] * prime[j]] = true;
	}
	int cnt = 0;
	for (int i = 2; i <= maxn; i++)
	if (flag[D[i]])
	{
		cnt++;
		if (cnt == 9) printf("%d\n", i), cnt = 0;
	}
	return 0;
}
