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

const int MAXN = 1000 + 10;
int N, M;
int mp[MAXN][MAXN], s[MAXN], deg[MAXN];

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d", &N, &M);
	for (int i = 1; i <= M; i++)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		if (mp[u][v] == 0)
		{
			mp[u][v] = 1;
			deg[v]++;
		}
	}
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &s[i]);
	}

	bool flag = true;
	for (int i = 1; flag && i <= N; i++)
	{
		if (deg[s[i]] != 0) 
		{
			flag = false;
		}
		else
		{
			for (int j = 1; j <= N; j++)
				if (mp[s[i]][j])
					deg[j]--;
		}
	}
	if (flag) cout << "YES" << endl;
	else cout << "NO" << endl;
	return 0;
}
