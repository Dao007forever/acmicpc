#include <map>
#include <set>
#include <list>
/*
 * 求任意两点之间的路径条数
 * f(i,j) = sigma{f(i,k)*f(k,j)}，如果i->j中存在一个点k使得f(k,k)>0那么f(i,j)=-1
 */
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

const int maxn = 30;
int adj[33][33];

int main() {
	freopen("in", "r", stdin);
	int m, n, test = 0;
	while (cin >> m) {
		printf("matrix for city %d\n", test++);
		memset(adj, 0, sizeof(adj));
		n = 0;
		for (int i = 0; i < m; i++) {
			int a, b;
			cin >> a >> b;
			n = max(n, a);
			n = max(n, b);
			adj[a][b]++;
		}
		n++;
		for (int k = 0; k < n; k++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					adj[i][j] += adj[i][k] * adj[k][j];
		for (int k = 0; k < n; k++)
			if (adj[k][k]) {
				for (int i = 0; i < n; i++)
					for (int j = 0; j < n; j++)
						if (adj[i][k] && adj[k][j])
							adj[i][j] = -1;
			}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (j) {
					printf(" ");
				}
				printf("%d", adj[i][j]);
			}
			printf("\n");
		}
	}
	return 0;
}
