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
int a[222222];
int maxL[222222], minR[222222];

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	sort(a, a + n);
	bool better = false;
	for (int i = 0; i < n - 1; i++)
		if (a[i] > 1 && a[i] != a[i + 1] && (a[i] << 1) > a[i + 1])
		{
			better = true;
			break;
		}
	if (better) printf("YES\n");
	else printf("NO\n");
	return 0;
}

