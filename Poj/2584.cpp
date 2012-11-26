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

const int MAXN = 200 + 10;
int nx, ny, res;
int g[MAXN][MAXN], cx[MAXN], cy[MAXN], mk[MAXN];
int s[MAXN], cnt[MAXN];
char shirt[MAXN][MAXN];

int ID(char ch)
{
	switch (ch)
	{
		case 'S': return 1; break;
		case 'M': return 2; break;
		case 'L': return 3; break;
		case 'X': return 4; break;
		case 'T': return 5; break;
		default: return 0;
	}
}

int path(int u)
{
	for (int v = 1; v <= ny; v++)
	{
		if (g[u][v] > 0 && (!mk[v]))
		{
			mk[v] = 1;
			if (!cy[v] || path(cy[v]))
			{
				cx[u] = v;
				cy[v] = u;
				return 1;
			}
		}
	}
	return 0;
}

int MaxMatch()
{
	res = 0;
	memset(cx, 0, sizeof(cx));
	memset(cy, 0, sizeof(cy));
	for (int i = 1; i <= nx; i++)
	{
		if (!cx[i])
		{
			memset(mk, 0, sizeof(mk));
			res += path(i);
		}
	}
	return 0;
}

int main()
{
	freopen("a", "r", stdin);
	char str[55], START[55], END[55];
	while (cin >> str && strcmp(str, "ENDOFINPUT"))
	{
		memset(g, 0, sizeof(g));
		cin >> nx;
		for (int i = 1; i <= nx; i++)
			cin >> shirt[i];
		s[0] = 0;
		for (int i = 1; i <= 5; i++)
		{
			cin >> cnt[i];
			s[i] = s[i - 1] + cnt[i];
		}
		cin >> END;
		ny = s[5];
		for (int i = 1; i <= nx; i++)
		{
			int st = ID(shirt[i][0]);
			int ed = ID(shirt[i][1]);
			for (int j = s[st - 1] + 1; j <= s[ed]; j++)
				g[i][j] = 1;
		}
		MaxMatch();
		if (res == nx) cout << "T-shirts rock!" << endl;
		else cout << "I'd rather not wear a shirt anyway..." << endl;
	}
	return 0;
}
