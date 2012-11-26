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

char s[100010], a[110], b[110];
int n, an;

int f()
{
	char *t;
	return (t = strstr(s, a)) && strstr(t + an, b);
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%s%s%s", s, a, b);
	n = strlen(s);
	an = strlen(a);
	int x = f();
	reverse(s, s + n);
	int y = f();
	if (x)
	{
		if (y) puts("both");
		else puts("forward");
	}
	else
	{
		if (y) puts("backward");
		else puts("fantasy");
	}
	return 0;
}
