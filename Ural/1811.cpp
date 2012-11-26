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
#define th(x) this->x = x
const int MAXN = 10000 + 10;
const int MAXM = 100000 + 10;
struct Edge
{
	int u, v, w;
}e[MAXM];
int N, M;
int cnt[MAXN];
vector<int> vec[MAXN];
int vis[MAXN];

bool cmp(int i, int j)
{
	return cnt[i] > cnt[j];
}

set<int> S;
bool judge(int a, int b)
{
	/*S.clear();
	for (int i = 0; i < vec[a].size(); i++)
		S.insert(vec[a][i]);
	for (int i = 0; i < vec[b].size(); i++)
		S.insert(vec[b][i]);
	return S.size() == N;*/
	memset(vis, 0, sizeof(vis));
	int nn = 0;
	for (int i = 0; i < vec[a].size(); i++)
		if (!vis[vec[a][i]]) 
		{
			nn++;
			vis[vec[a][i]] = 1;
		}
	for (int i = 0; i < vec[b].size(); i++)
		if (!vis[vec[b][i]])
		{
			nn++;
			vis[vec[b][i]] = 1;
		}
	return nn == N;
}

bool check(int lim)
{
	memset(cnt, 0, sizeof(cnt));
	for (int i = 1; i <= N; i++)
		vec[i].clear();
	for (int i = 0; i < M; i++)
	{
		if (e[i].w <= lim)
		{
			cnt[e[i].u]++;
			vec[e[i].u].push_back(e[i].v);
		}
	}
	sort(cnt + 1, cnt + N + 1, cmp);
	for (int i = 1; i <= N; i++)
	{
		for (int j = i + 1; j <= N && cnt[i] + cnt[j] >= N; j++)
		{
			if (judge(i, j)) return true;
		}
	}
	return false;
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d%d", &N, &M);
	int Left = 0, Right = 0, ans;
	for (int i = 0; i < M; i++)
	{
		int u, v, w;
		scanf("%d%d%d", &e[i].u, &e[i].v, &e[i].w);
		Right = max(Right, e[i].w);
	}
	if (!check(Right))
	{
		puts("No solution");
		return 0;
	}
	while (Left <= Right)
	{
		int Mid = (Left + Right) / 2;
		if (check(Mid)) 
		{
			Right = Mid - 1;
			ans = Mid;
		}
		else Left = Mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}
