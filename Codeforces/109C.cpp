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

const int MAXN = 111111;
int N, p[MAXN];
long long cnt[MAXN];

int find(int x)
{
	if (p[x] == x) return x;
	return p[x] = find(p[x]);
}

bool lucky(int k)
{
	if (!k) return false;
	while (k)
	{
		int tmp = k % 10;
		if (tmp != 4 && tmp != 7) return false;
		k /= 10;
	}
	return true;
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		p[i] = i;
	for (int i = 1; i < N; i++)
	{
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		if (!lucky(z)) 
			p[find(x)] = find(y);
	}
	for (int i = 1; i <= N; i++)
		cnt[find(i)]++;
	long long ans = 0;
	for (int i = 1; i <= N; i++)
		ans += cnt[i] * (N - cnt[i]) * (N - cnt[i] - 1);
	cout << ans << endl;
	return 0;
}
