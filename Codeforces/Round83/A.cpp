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

int h, m;

void step()
{
	m++;
	if (m == 60)
	{
		h++;
		m = 0;
	}
	if (h == 24)
	{
		h = 0;
	}
}

bool judge()
{
	int a = h / 10, b = h % 10;
	int c = m / 10, d = m % 10;
	if (a == d && b == c) return true;
	return false;
}

void output()
{
	if (h < 10)
	{
		printf("0%d:", h);
	}
	else printf("%d:", h);
	if (m < 10)
	{
		printf("0%d", m);
	}else printf("%d", m);
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d:%d", &h, &m);
	step();
	while (!judge())
	{
		step();
	}
	output();
	return 0;
}
