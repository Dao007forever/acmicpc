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

char rank[9] = {'6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
char tr;
char a[5], b[5];

int main()
{
	freopen("a", "r", stdin);
	scanf("%c", &tr);
	scanf("%s%s", a, b);
	if (a[1] != b[1])
	{
		if (a[1] == tr)
		{
			printf("YES");
		}
		else printf("NO");
	}
	else
	{
		int l, r;
		for (int i = 0; i < 9; i++)
			if (rank[i] == a[0])
			{
				l = i;
			}else if (rank[i] == b[0])
			{
				r = i;
			}
		if (l > r) printf("YES");
		else printf("NO");
	}
	return 0;
}
