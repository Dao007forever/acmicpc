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

int r, g, b;

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d%d", &r, &g, &b);
	int t = 0, res = 29;
	while (r != 0 || g != 0 || b != 0)
	{
		if (t == 0 && r != 0)
		{
			if (r == 1) r--;
			else r -= 2;
		}
		if (t == 1 && g != 0)
		{
			if (g == 1) g--;
			else g -= 2;
		}
		if (t == 2 && b != 0)
		{
			if (b == 1) b--;
			else b -= 2;
		}
		t = (t + 1) % 3;
		res++;
	}
	printf("%d\n", res);
	return 0;
}
