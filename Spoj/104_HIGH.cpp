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

const double eps = 1e-15;
double K[15][15];
int A[15][15], D[15][15];
int n, m;

int dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

double det()
{
	int op = 0, i, j, k;
	double ret = 1;
	for (i = 0; i < n; i++)
	{
		if (dblcmp(K[i][i]) == 0)
		{
			for (j = i + 1; j < n; j++)
				if (dblcmp(K[j][i]) != 0) break;
			if (j == n) return 0;
			for (int k = i; k < n; k++)
				swap(K[i][k], K[j][k]);
			op++;
		}
		ret *= K[i][i];
		for (j = i + 1; j < n; j++)
			K[i][j] /= K[i][i];
		for (j = i + 1; j < n; j++)
		{
			for (k = i + 1; k < n; k++)
				K[j][k] -= K[j][i] * K[i][k];
		}
	}
	if (op & 1) ret = -ret;
	return ret;
}

int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		memset(A, 0, sizeof(A));
		memset(D, 0, sizeof(D));
		memset(K, 0, sizeof(K));
		scanf("%d%d", &n, &m);
		int x, y;
		for (int i = 0; i < m; i++)
		{
			scanf("%d%d", &x, &y);
			x--; y--;
			A[x][y] = A[y][x] = 1;
			D[x][x]++;
			D[y][y]++;
		}

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				K[i][j] = D[i][j] - A[i][j];
		n--;
		double ans = det();
		printf("%0.0lf\n", ans);
	}
	return 0;
}
