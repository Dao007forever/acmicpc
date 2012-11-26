#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

int N, X, Y, Z, A, B;
int t[5000000], queue[5000000];
int dp[25][25][25][25][25];

void init()
{
	scanf("%d%d%d%d%d%d", &N, &X, &Y, &Z, &A, &B);
	memset(dp, 0, sizeof(dp));
	memset(t, 0, sizeof(t));
}

void solve()
{
	dp[N][0][0][0][0] = true;
	t[0] = 0;
	int r = 0;
	queue[0] = N << 20;
	for (int l = 0; l <= r; l++)
	{
		int cur = queue[l];
		int n = cur >> 20, a = (cur & 1048575) >> 15, b = (cur & 32767) >> 10, u = (cur & 1023) >> 5, v = cur & 31;
		for (int i = 0; i <= n; i++)
		{
			int nn = n + u, aa = a + i * X, bb = b + (n - i) * Y;
			if (aa >= A && bb >= B)
			{
				printf("%d\n", t[l] + 1);
				return;
			}
			for (int j = 0; j <= 1 && j * Z <= a && j + nn + v <= 21; j++)
			if (!dp[nn][aa - j * Z][bb][v][j])
			{
				if (j && u + v) continue;
				int aaa = aa - j * Z, bbb = bb;
				if (aaa > 21) aaa = 21;
				if (bbb > 21) bbb = 21;
				dp[nn][aaa][bbb][v][j] = true;
				queue[++r] = (nn << 20) + (aaa << 15) + (bbb << 10) + (v << 5) + j;
				t[r] = t[l] + 1;
			}
		}
	}
}

int main()
{
	freopen("in", "r", stdin);
	int Test;
//	scanf("%d", &Test);
//	while (Test--)
	for (scanf("%d", &Test); Test; Test--)
	{
		init();
		solve();
	}
	return 0;
}
