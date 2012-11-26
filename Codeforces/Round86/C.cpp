#include <bitset>
#include <cstdio>
using namespace std;

const int MAXN =300000000;
bitset<300000001> v;
int i, j, ans, l, r;

int main()
{
	freopen("in", "r", stdin);
	scanf("%d%d", &l, &r);

	v.set();
	for (i = 3; i * i <= r; i += 2)
		if (v[i])
			for (j = i * i; j <= r; j += (i << 1))
				v[j] = false;
	ans = 0;
	for (i = 5; i <= r; i += 4)
	{
		if (l <= i && v[i])
		{
			ans++;
		}
	}

	printf("%d\n", ans + (l <= 2 && 2 <= r));
	return 0;
}
