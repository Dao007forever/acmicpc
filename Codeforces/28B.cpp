/*
 * Author : Yang Zhang
 */
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

int n;
int p[111];
bool adj[111][111];

int main() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> p[i], p[i]--;
	for (int i = 0; i < n; i++) {
		int d;
		cin >> d;
		adj[i][i] = true;
		if (i - d >= 0) {
			adj[i][i - d] = adj[i - d][i] = true;		
		}
		if (i + d < n) {
			adj[i][i + d] = adj[i + d][i] = true;
		}
	}
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				adj[i][j] |= adj[i][k] & adj[k][j];

	bool flag = true;
	for (int i = 0; i < n; i++)
		flag &= adj[i][p[i]];
	if (flag) puts("YES");
	else puts("NO");
	return 0;
}
