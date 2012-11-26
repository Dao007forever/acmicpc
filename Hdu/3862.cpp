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

const int MAXN = 100000 + 10;
const double eps = 1e-6;
int N;
double k[MAXN];

int dblcmp(double d)
{
    return (d > eps) - (d < -eps);
}

int main()
{
    freopen("a", "r", stdin);
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &N);
		k[0] = 0;
        for (int i = 1; i <= N; i++)
        {
			double b;
			scanf("%lf", &b);
			k[i] = 360 + k[i - 1] + b;
			while (k[i] >= 360.0)
				k[i] -= 360.0;
        }
		sort(k + 1, k + N + 1);
		bool flag = true;
		for (int i = 1; i <= N; i++)
		if (k[i] - k[i - 1] >= 180)
		{
			flag = false;
			break;
		}
		if (k[N] <= 180) flag = false;
		if (N == 1 && k[1] == 180) flag = true;
		if (flag) printf("Yes\n");
		else printf("No\n");
    }
    return 0;
}
