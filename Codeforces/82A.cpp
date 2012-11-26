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

#define REP(i, n) for(i = 0; i < (n); ++i)
#define FOR(i, l, h) for(i = (l); i <= (h); ++i)
#define FORD(i, h, l) for(i = (h); i >= (l); --i)

char s[5][10] = {"Sheldon", "Leonard", "Penny", "Rajesh", "Howard"};
int n, m;

int main()
{
	scanf("%d", &n);
	m = 5;
	while (n > m)
	{
		n -= m;
		m *= 2;
	}
	int k = m / 5;
	n = (n + k - 1) / k;
	printf("%s\n", s[n - 1]);
	return 0;
}
