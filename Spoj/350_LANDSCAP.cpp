#include <map>
#include <set>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <bitset>
#include <vector>
#include <cstdio>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 1000 + 10;
int N, K, ans;
int h[MAXN];
bool p[MAXN];

int CalcPeak()
{
	int sum = 0;
	memset(p, 0, sizeof(p));
	for (int i = 1; i <= N; )
	{
		int j = i;
		for (; h[j + 1] == h[i]; j++);
		if ((i != 1 || j != N) && h[i - 1] < h[i] && h[j] > h[j + 1])
			p[i] = 1, sum++;
		i = j + 1;
	}
	return sum;
}

void Cut()
{
	int Min = 1 << 30, tmp;
	for (int pos = 1; pos <= N; pos++)
	if (p[pos])
	{
		int l = pos, r = pos;
		for (; l >= 1 && h[l - 1] <= h[l]; l--);
		for (; r <= N && h[r + 1] <= h[r]; r++);
		int height = max(h[l], h[r]), s = 0;
		for (int k = l; k <= r; k++)
			if (h[k] > height) s += h[k] - height;
		if (s < Min) Min = s, tmp = pos;
	}
	ans += Min;
	int l = tmp, r = tmp;
	for (; l >= 1 && h[l - 1] <= h[l]; l--);
	for (; r <= N && h[r + 1] <= h[r]; r++);
	Min = max(h[l], h[r]);

	for (int k = l; k <= r; k++)
		if (h[k] > Min) h[k] = Min;
}

int main()
{
	freopen("a", "r", stdin);
	int T;
	scanf("%d", &T);
	while (T--)
	{
		ans = 0;
		scanf("%d%d", &N, &K);
		for (int i = 1; i <= N; i++)
			scanf("%d", &h[i]);
		while (CalcPeak() > K)
			Cut();
		printf("%d\n", ans);
	}
	return 0;
}
