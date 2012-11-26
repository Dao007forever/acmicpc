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

const int MAXN = 55;
const int inf = 0x3f3f3f3f;
int T, N;
int s[MAXN * MAXN], tmp[MAXN * MAXN], a[MAXN];

int Find(int x)
{
	for (int i = 1; i <= N * (N - 1) / 2; i++)
	if (tmp[i] == x) return i;
	return -1;
}

int main()
{
	freopen("a", "r", stdin);
	while (cin >> N)
	{
		memset(s, 0, sizeof(s));
		memset(tmp, 0, sizeof(tmp));
		for (int i = 1; i <= N * (N - 1) / 2; i++)
			cin >> s[i];
		sort(s + 1, s + N * (N - 1) / 2 + 1);
		bool ok = false, impossible;
		for (int p = 3; p <= N * (N - 1) / 2 && !ok; p++)
		{
			memset(a, 0, sizeof(a));
			for (int i = 1; i <= N * (N - 1) / 2; i++)
				tmp[i] = s[i];
			if ((tmp[1] + tmp[2] - tmp[p]) % 2 != 0) continue;
			a[1] = (tmp[1] + tmp[2] - tmp[p]) / 2;
			a[2] = tmp[1] - a[1];
			a[3] = tmp[2] - a[1];
			tmp[1] = tmp[2] = tmp[p] = inf;
	
			if (N == 3)
			{
				if (a[1] + a[2] == s[1] && a[1] + a[3] == s[2] && a[2] + a[3] == s[3])
				{
					ok = true;
					break;
				}
			}
			for (int i = 4; i <= N; i++)
			{
				int Min = inf;
				for (int j = 1; j <= N * (N - 1) / 2; j++)
				if (tmp[j] < Min) Min = tmp[j];
				a[i] = Min - a[1];
				impossible = false;
				for (int j = 1; j <= i - 1; j++)
				{
					int pos = Find(a[i] + a[j]);
					if (pos < 0)
					{	
						impossible = true;
						break;
					}
					tmp[pos] = inf;
				}
				if (impossible) break;
				if (i == N) ok = true;
			}
			if (ok) break;
		}
		if (!ok) cout << "Impossible" << endl;
		else
		{
			for (int i = 1; i <= N; i++)
				if (i == 1) printf("%d", a[i]);
				else printf(" %d", a[i]);
			cout << endl;
		}
	}
	return 0;
}
