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
const double eps = 1e-8;
const double pi = 3.141;
int N;
double x[MAXN], y[MAXN], sum;

double dis(int i, int j)
{
	return (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]);
}

int main()
{
	freopen("a", "r", stdin);
	int cas = 0;
	while (scanf("%d", &N) && N)
	{
		cas++;
		int ans = 0;
		scanf("%lf%lf%lf%lf%lf", &x[N + 1], &y[N + 1], &x[N + 2], &y[N + 2], &sum);
		for (int i = 1; i <= N; i++)
			scanf("%lf%lf", &x[i], &y[i]);
		for (int i = 1; i <= N + 1; i++)
		{
			double r1 = dis(i, N + 1), s1 = r1 * pi;
			if (s1 > sum + eps) continue;
			double s2 = sum - s1 + eps, r2 = s2 / pi;
			int cnt = 0;
			for (int j = 1; j <= N; j++)
				if (dis(j, N + 1) <= r1 + eps || dis(j, N + 2) <= r2 + eps)
					cnt++;
			ans = max(ans, cnt);
		}
		printf("%d. %d\n", cas, N - ans);
	}
	return 0;
}
