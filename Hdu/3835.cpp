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

const double eps = 1e-6;
int N;

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d", &N) != EOF)
	{
		int res = 0;
		for (int i = 0; i * i <= N; i++)
		{
			int tmp = N - i * i;
			double x = sqrt(tmp);
			if (fabs(x - int(x)) < eps)
			{
				if (i == 0 || tmp == 0) res += 2;
				else res += 4;
			}
		}
		cout << res << endl;
	}
	return 0;
}
