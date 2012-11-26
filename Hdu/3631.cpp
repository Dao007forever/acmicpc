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
#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

#define MAXN 305
const int inf = 0x3f3f3f3f;
int n, m, q;
int d[MAXN][MAXN];
int mark[MAXN];

int main(int argc, char const *argv[])
{
	int cas = 1; int blank = 0;
	while (~scanf("%d%d%d", &n, &m, &q)) {
		if (n == 0 && m == 0 && q == 0) break;
		if (blank) {
			puts("");
		}
		blank = 1;
		printf("Case %d:\n", cas++);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				d[i][j] = i == j ? 0 : inf;
		memset(mark, 0, sizeof(mark));
		for (int i = 0; i < m; i++) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			d[a][b] = min(d[a][b], c);
		}
		while (q--) {
			int type, a, b;
			scanf("%d", &type);
			if (type == 0) {
				scanf("%d", &a);
				if (mark[a]) {
					printf("ERROR! At point %d\n", a);
					continue;
				}
				mark[a] = 1;
				for (int i = 0; i < n; i++) {
					for (int j = 0; j < n; j++) {
						d[i][j] = min(d[i][j], d[i][a] + d[a][j]);
					}
				}
			} else {
				scanf("%d%d", &a, &b);
				if (!mark[a] || !mark[b]) {
					printf("ERROR! At path %d to %d\n", a, b);
					continue;
				}
				if (d[a][b] == inf) {
					printf("No such path\n");
					continue;
				}
				printf("%d\n", d[a][b]);
			}
		}
	}
	return 0;
}