#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

int n, m, ans;
int a[111][111], x[5];
int srow[111], scol[111];
int sumrow[111], sumcol[111];

void solverow(int A, int B, int C)
{
	for (int i = 1; i < n; i++)
		for (int j = i + 1; j < n; j++)
			{
				int tmp1 = sumrow[i], tmp2 = sumrow[j] - sumrow[i], tmp3 = sumrow[n] - sumrow[j];
				if (tmp1 == A && tmp2 == B && tmp3 == C)
				{
					ans++;
				//	cout << i << j << k << endl;
				}
			}
}

void solvecol(int A, int B, int C)
{
	for (int i = 1; i < m; i++)
		for (int j = i + 1; j < m; j++)
			{
				int tmp1 = sumcol[i], tmp2 = sumcol[j] - sumcol[i], tmp3 = sumcol[m] - sumcol[j];
				if (tmp1 == A && tmp2 == B && tmp3 == C)
				{
					ans++;
				//	cout << i << j << k << endl;
				}
			}

}

int main()
{
	freopen("in", "r", stdin);
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
	for (int j = 1; j <= m; j++)
	{
		scanf("%d", &a[i][j]);
	}
	for (int i = 1; i <= n; i++)
	for (int j = 1; j <= m; j++)
		srow[i] += a[i][j], scol[j] += a[i][j];
	for (int i = 1; i <= n; i++)
		sumrow[i] = sumrow[i - 1] + srow[i];
	for (int j = 1; j <= m; j++)
		sumcol[j] = sumcol[j - 1] + scol[j];

	for (int i = 0; i < 3; i++)
		scanf("%d", &x[i]);
	sort(x, x + 3);
	ans = 0;
	int tot = 0;
	do
	{
		tot++;
		if (n >= 3)
		{
			solverow(x[0], x[1], x[2]);
		}
		if (m >= 3)
		{
			solvecol(x[0], x[1], x[2]);
		}
	}while (next_permutation(x, x + 3));
	printf("%d\n", ans);
	//printf("%d\n", tot);
	return 0;
}
