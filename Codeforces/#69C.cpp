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
vector<int> tree[MAXN];
int n, val[MAXN];

void DFS(int f, int u, long long &max_get, int &left)
{
	vector<int> v_left;
	vector<long long> v_get;

	for (int i = 0; i < tree[u].size(); i++)
	{
		int v = tree[u][i];
		if (v != f && val[v])
		{
			int c_left = val[v] - 1;
			long long c_get = 0;
			DFS(u, v, c_get, c_left);
			v_get.push_back(c_get);
			v_left.push_back(c_left);
		}
	}
	sort(v_get.begin(), v_get.end());
	max_get = 0;

	for (int i = v_get.size() - 1; i >= 0 && left; i--)
	{
		left--;
		max_get += v_get[i] + 2;
	}

	for (int i = 0; i < v_left.size() && left; i++)
	{
		int temp = min(left, v_left[i]);
		left -= temp;
		max_get += 2 * temp;
	}
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%d", &val[i]);

	for (int i = 1; i < n; i++)
	{
		int a, b;
		scanf("%d%d", &a, &b);
		tree[a].push_back(b);
		tree[b].push_back(a);
	}

	int root;
	scanf("%d", &root);

	long long ans = 0;
	DFS(0, root, ans, val[root]);
	printf("%I64d\n", ans);
	return 0;
}
