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

int n;
int h[22], fac[22];

void init()
{
	fac[1] = 1;
	for (int i = 2; i <= 8; i++)
		fac[i] = fac[i - 1] * i;
}

int main()
{
	freopen("in", "r", stdin);
	init();
	while (scanf("%d", &n) && n) {
		for (int i = 0; i < n; i++) {
			scanf("%d", &h[i]);
		}
		sort(h, h + n);
		long long ret, way;
		int k1 = (n - 1) >> 1, k2 = (n + 1) >> 1;
		int num1 = 0, num2 = 0;
		for (int i = 0; i < k1; i++)
			num1 += h[i];
		for (int i = 0; i < k2; i++)
			num2 += h[n - i - 1];
		ret = (n + num2 - num1) << 1;
		way = (long long)fac[n >> 1] * fac[(n + 1) >> 1];
		if ((n & 1) == 0) way *= 2;
		cout << ret << " " << way << endl;
	}
	return 0;
}
