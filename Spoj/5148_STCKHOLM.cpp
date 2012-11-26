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

int main(int argc, char const *argv[])
{
	int n, m, A, B;
	int cas = 1;
	while (~scanf("%d%d%d%d", &n, &m, &A, &B) && n) {
		vector<int> deg(n), rdeg(n);
		vector<vector<int> > g(n);
		for (int i = 0; i < n; i++)
			g[i].resize(n);
		for (int i = 0; i < m; i++) {
			int a, b;
			scanf("%d%d", &a, &b);
			g[a][b] = g[b][a] = true;
		}
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (i != j) {
					if (g[i][j]) {
						deg[i]++;
					} else {
						rdeg[i]++;
					}
				}
		vector<bool> del(n);
		queue<int> q;
		for (int i = 0; i < n; i++) {
			if (deg[i] < A || rdeg[i] < B) {
				del[i] = true; q.push(i);
			}
		}
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int i = 0; i < n; i++) {
				if (del[i]) continue;
				if (g[u][i]) {
					deg[i]--;
				} else {
					rdeg[i]--;
				}
				if (deg[i] < A || rdeg[i] < B) {
					del[i] = true; q.push(i);
				}
			}
		}
		int ret = 0;
		for (int i = 0; i < n; i++)
			ret += del[i] == 0;
		printf("Case #%d: %d\n", cas++, ret);
	}
	return 0;
}