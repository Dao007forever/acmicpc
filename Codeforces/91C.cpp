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
const int P = 1000000009;
int N, M;
int p[MAXN];

int getfather(int x)
{
	if (x != p[x])
		p[x] = getfather(p[x]);
	return p[x];
}

int main()
{
	freopen("a", "r", stdin);
	cin >> N >> M;
	int res = 1;
	for (int i = 1; i <= N; i++)
		p[i] = i;
	for (int i = 1; i <= M; i++)
	{
		int a, b;
		cin >> a >> b;
		int pa = getfather(a), pb = getfather(b);
		if (pa == pb)
		{
			res *= 2;
			res %= P;
		}
		else p[pa] = pb;
		cout << res - 1 << endl;
	}
	return 0;
}
