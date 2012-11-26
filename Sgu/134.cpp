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

const int MAXN = 16000 + 10;
const int inf = 1000000000;
int n, x, y, num[MAXN], numSon[MAXN];
vector<int> adj[MAXN], cen;

void dfs(int u, int fa)
{
	num[u] = 1;
	for (int i = 0; i < adj[u].size(); i++)
	{
		if (adj[u][i] != fa)
		{
			int v = adj[u][i];
			dfs(v, u);
			num[u] += num[v];
			numSon[u] = max(numSon[u], num[v]);
		}
	}
}

int main()
{
	freopen("a", "r", stdin);
	cin >> n;
	for (int i = 1; i < n; i++)
	{
		cin >> x >> y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	dfs(1, 0);
	int res = inf;
	for (int i = 1; i <= n; i++)
	{
		int temp = max(n - num[i], numSon[i]);
		if (temp < res)
		{
			res = temp;
			cen.clear();
			cen.push_back(i);
		}
		else if (temp == res)
			cen.push_back(i);
	}
	cout << res << " " << cen.size() << endl;
	for (int i = 0; i < cen.size(); i++)
		cout << cen[i] << " ";
	return 0;
}
