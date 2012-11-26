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
int T, N;
int a[MAXN], b[MAXN];

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &N);
		for (int i = 0; i < N; i++)
			scanf("%d", a + i);
		for (int i = 0; i < N; i++)
			scanf("%d", b + i);
		sort(a, a + N);
		sort(b, b + N);
		long long res = 0;
		for (int i = 0; i < N; i++)
			res += a[i] * b[i];
		cout << res << endl;
	}
	return 0;
}
