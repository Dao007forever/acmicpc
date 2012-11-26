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

const int MAXN = 1111;
int p[MAXN], rank[MAXN];

void init(int x)
{
	p[x] = x;
	rank[x] = 0;
}

int Find(int x)
{
	if (x != p[x]) p[x] = Find(p[x]);
	return p[x];
}

void Union(int x, int y)
{
	x = Find(x), y = Find(y);
	if (rank[x] > rank[y])
		p[y] = x;
	else
	{
		p[x] = y;
		if (rank[y] == rank[x]) rank[y]++;
	}
}

int main()
{
	freopen("a", "r", stdin);
	int Test, n;
	scanf("%d", &Test);
	bool blank = false;
	while (Test--)
	{
		if (blank) puts("");
		blank = true;
		string s;
		int N1 = 0, N2 = 0;
		scanf("%d\n", &n);
		for (int i = 1; i <= n; i++)
			init(i);
		while (getline(cin, s) && s.size() > 1)
		{
			istringstream ss(s);
			string op;
			char str[30];
			int a, b;
			ss >> op >> a >> b;
			if (op == "c")
			{
				Union(a, b);
				continue;
			}
			else if (op == "q")
			{
				if (Find(a) == Find(b))
					N1++;
				else N2++;
				continue;
			}
		}
		printf("%d,%d\n", N1, N2);
	}
	return 0;
}
