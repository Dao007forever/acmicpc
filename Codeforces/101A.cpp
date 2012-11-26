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
int K;
int cnt[30], vis[30], id[MAXN];
char str[MAXN];

int main()
{
	freopen("a", "r", stdin);
	scanf("%s", str);
	scanf("%d", &K);
	int n = strlen(str);
	for (int i = 0; i < n; i++)
		cnt[str[i] - 'a']++;
	int j, Max = 0, sum = 0;
	for (int i = 0; i < 26; i++)
	{
		id[i] = i;
		if (cnt[i] > Max)
		{
			Max = cnt[i];
			j = i;
		}
		sum += cnt[i];
	}

	if (sum < K)
	{
		printf("0\n");
		return 0;
	}
	for (int i = 0; i < 26; i++)
	for (int j = i + 1; j < 26; j++)
	if (cnt[j] < cnt[i])
	{
		swap(cnt[i], cnt[j]);
		swap(id[i], id[j]);
	}
	
	memset(vis, 0, sizeof(vis));
	for (int i = 0; K - cnt[i] >= 0; i++)
	{
		K -= cnt[i];
		cnt[i] = 0;
		vis[id[i]] = true;
	}
	int ans = 0;
	for (int i = 0; i < 26; i++)
	if (cnt[i]) ans++;
	printf("%d\n", ans);
	for (int i = 0; i < n; i++)
	if (!vis[str[i] - 'a'])
		printf("%c", str[i]);
	return 0;
}
