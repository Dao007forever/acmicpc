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
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

int n, m;
int deg[105];
int g[105][105];

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; cas <= Test; cas++) {
		printf("Case #%d: ", cas);
		scanf("%d%d", &n, &m);
		memset(g, 0, sizeof(g));
		memset(deg, 0, sizeof(deg));
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			g[a][b] = g[b][a] = true;
			deg[a]++; deg[b]++;
		}
		vector<int> ans;
		int now = m;
		while (now > m / 2) {
			int k = -1, Max = 0;
			for (int i = 1; i <= n; i++) {
				if (deg[i] > Max) {
					Max = deg[i]; k = i;
				}
			}
			if (k == -1) break;
			now -= Max;
			ans.PB(k);
			deg[k] = 0;
			for (int i = 1; i <= n; i++)
				if (g[k][i]) {
					deg[i]--;
				}
		}
		if (now > m / 2) {
			puts("Impossible.");
			puts("");
		}
		else {
			printf("%d\n", ans.size());
			for (int i = 0; i < ans.size(); i++)
				printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
			if (ans.size() == 0) puts("");
		}
	}
	return 0;
}