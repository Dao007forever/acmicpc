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

const int MAXN = 100 + 10;
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, 1, 0, -1};
int n, m;
int B[MAXN][MAXN], pass[MAXN][MAXN];

int Pass(int x, int y)
{
	if (pass[x][y]) return B[x][y] / 2;
	else 
	{
		pass[x][y] = true;
		return B[x][y];
	}
}

int Count(int x, int y, int d)
{
	int res = 0;
	switch(d)
	{
		case 0: res += Pass(x - 1, y - 1) + Pass(x - 1, y); break;
		case 1: res += Pass(x - 1, y) + Pass(x, y); break;
		case 2: res += Pass(x, y - 1) + Pass(x, y); break;
		case 3: res += Pass(x - 1, y - 1) + Pass(x, y - 1); break;
	}
	return res;
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d", &n, &m);
	char s[MAXN];
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", s);
		for (int j = 0; j < m; j++)
			B[i][j + 1] = s[j] - '0';
	}

	char ch;
	int d = 1, x = 1, y = 1, cnt = 0;
	while (cin >> ch)
	{
		switch(ch)
		{
			case 'M': cnt += Count(x, y, d);
					  x += dx[d], y += dy[d]; break;
			case 'L': d--;
					  if (d < 0) d = 3; break;
			case 'R': d++;
					  if (d > 3) d = 0;
		}
	}
	cout << cnt << endl;
}
