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

const int MAXN = 100000 + 10;
int T, N;
int pos[MAXN];

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &T);
	while (T--)
	{
		memset(pos, 0, sizeof(pos));
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
		{
			int x;
			scanf("%d", &x);
			pos[x] = i;
		}

		bool flag = false;
		int maxt = (N - 1) / 2;
		for (int t = 1; !flag && t <= maxt; t++)
		{
			int maxi = N - t;
			for (int i = t + 1; i <= maxi; i++)
			{
				int del1 = pos[i] - pos[i - t];
				int del2 = pos[i + t] - pos[i];
				if ((del1 ^ del2) >= 0)
				{
					flag = true;
					break;
				}
			}
		}
		if (flag) cout << "Y" << endl;
		else cout << "N" << endl;
	}
}
