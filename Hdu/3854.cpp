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

typedef long long LL;
const int MAXN = 200000 + 10;
int N, M, K;
int data[MAXN], L[MAXN], R[MAXN], color[MAXN];
LL arr[MAXN], res;

int lowbit(int x)
{
	return x & (-x);
}

void add(int x, int num)
{
	for (int i = x; i <= N; i += lowbit(i))
		arr[i] += num;
}

LL sum(int x)
{
	LL ans = 0;
	for (int i = x; i > 0; i -= lowbit(i))
		ans += arr[i];
	return ans;
}

void init()
{
	memset(L, -1, sizeof(L));
	memset(R, -1, sizeof(R));
	memset(arr, 0, sizeof(arr));
	for (int i = 1; i <= N; i++)
		if (data[i] < K)
			for (int j = i + 1; j <= N && data[j] >= K; j++)
				L[j] = i;
	for (int i = N; i >= 1; i--)
		if (data[i] < K)
			for (int j = i - 1; j >= 1 && data[j] >= K; j--)
				R[j] = i;
}

int get(int l, int r, int now)
{
	if (l > r) return 0;
	if (l == -1 || r == -1) return 0;
	if (now == 0) return r - l + 1 - (sum(r) - sum(l - 1));
	return sum(r) - sum(l - 1);
}

int main()
{
	freopen("a", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--)
	{
		scanf("%d%d%d", &N, &M, &K);
		for (int i = 1; i <= N; i++)
			scanf("%d", &data[i]);
		init();
		for (int i = 1; i <= N; i++)
		{
			scanf("%d", &color[i]);
			if (color[i]) add(i, 1);
		}
		res = 0;
		for (int i = 1; i <= N; i++)
			if (data[i] < K) res += get(i + 1, N, !color[i]);
			else res += get(R[i], N, !color[i]);
		while (M--)
		{
			int tmp;
			scanf("%d", &tmp);
			if (tmp == 1)
			{
				cout << res << endl;
				continue;
			}
			else
			{
				scanf("%d", &tmp);
				int i = tmp;
				LL before = 0, after = 0;
				if (data[i] < K)
				{
					before = get(1, i - 1, !color[i]) + get(i + 1, N, !color[i]);
					after = get(1, i - 1, color[i]) + get(i + 1, N, color[i]);
				}	
				else	
				{
					before = get(1, L[i], !color[i]) + get(R[i], N, !color[i]);
					after = get(1, L[i], color[i]) + get(R[i], N, color[i]);
				}
				if (color[i] == 0) add(i, 1), color[i] = 1;
				else add(i, -1), color[i] = 0;
				res += after - before;
			}
		}
	}
	return 0;
}
