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
typedef pair<int, int> T;
T ps[MAXN];
int N;

int main()
{
	freopen("a", "r", stdin);
	while (scanf("%d", &N) && N)
	{
		for (int i = 0; i < N; i++)
			scanf("%d%d", &ps[i].first, &ps[i].second);
		sort(ps, ps + N);

		int ans = 0;
		for (int i = 0; i < N; i++)
		{
			for (int j = i + 1; j < N; j++)
			{
				int dx = ps[j].first - ps[i].first;
				int dy = ps[j].second - ps[i].second;
				int mx = ps[i].first + ps[j].first;
				int my = ps[i].second + ps[j].second;

				if ((mx - dy) & 1 || (my - dx) & 1) continue;
				if (binary_search(ps, ps + N, T((mx - dy) / 2, (my + dx) / 2)) && 
					binary_search(ps, ps + N, T((mx + dy) / 2, (my - dx) / 2))) ans++;
			}
		}
		cout << ans / 2 << endl;
	}
	return 0;
}
