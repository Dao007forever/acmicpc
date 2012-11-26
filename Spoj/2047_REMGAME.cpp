#include <cstdio>
#include <iostream>
using namespace std;

int n;
bool flag[1 << 25], win[1 << 25];

void init()
{
	n = 0;
	for (int i = 0; i < 25; i++)
	{
		int k;
		scanf("%d", &k);
		n |= (k << i);
	}
}

void dfs(int state)
{
	if (flag[state]) return;
	flag[state] = true;
	for (int i = 0; i < 25; i++)
	if (state & (1 << i))
	{
		int tmp = (state ^ (1 << i));
		dfs(tmp);
		if (!win[tmp])
		{
			win[state] = true;
			return;
		}

		tmp = (state ^ (1 << i));
		for (int j = i + 1; j % 5 != 0; j++)
		if (tmp & (1 << j))
		{
			tmp ^= (1 << j);
			dfs(tmp);
			if (!win[tmp])
			{
				win[state] = true;
				return;
			}
		}else break;

		tmp = (state ^ (1 << i));
		for (int j = i + 5; j < 25; j += 5)
		if (tmp & (1 << j))
		{
			tmp ^= (1 << j);
			dfs(tmp);
			if (!win[tmp])
			{
				win[state] = true;
				return;
			}
		}else break;
	}
	win[state] = false;
}

void solve()
{
	dfs(n);
	if (win[n]) cout << "winning" << endl;
	else cout << "losing" << endl;
}

int main()
{
	freopen("in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	flag[0] = win[0] = true;
	while (Test--)
	{
		init();
		solve();
	}
}
