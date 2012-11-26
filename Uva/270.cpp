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

struct Point
{
	int x, y;
}p[777], cp[777];
int N;

int cross_product(Point a, Point b, Point c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool cmp(Point a, Point b)
{
	return cross_product(cp[0], a, b) < 0;
}

void solve()
{
	int ans = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cp[j] = p[j];
		}
		swap(cp[0], cp[i]);
		sort(cp + 1, cp + N, cmp);
		for (int j = 1; j < N; j++)
			cp[j].x -= cp[0].x, cp[j].y -= cp[0].y;
		int cnt = 2, now = 1;
		for (int j = 2; j < N; j++)
		{
			if (cp[now].y * cp[j].x - cp[now].x * cp[j].y == 0) cnt++;
			else
			{
				ans = max(ans, cnt);
				now = j;
				cnt = 2;
			}
		}
		ans = max(ans, cnt);
	}
	cout << ans << endl;
}

int main()
{
	freopen("a", "r", stdin);
	int Test;
	string s;
	cin >> Test;
	getchar();
	getline(cin, s);
	for (int cas = 0; cas < Test; cas++)
	{
		N = 0;
		while (getline(cin, s))
		{
			if (s.size() == 0) break;
			stringstream is(s);
			int a, b;
			is >> a >> b;
			p[N].x = a;
			p[N].y = b;
			N++;
		}
		if (cas) cout << endl;
		solve();
	}
	return 0;
}
