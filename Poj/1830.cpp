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

int n;
int s[33], e[33];
int mat[33][33];
int Gauss(int n, int m) {
	int Rank = 0;
	for (int j = 0, i; j < m && Rank < n; j++) {
		for (i = Rank; i < n && mat[i][j] == 0; i++);
		if (i == n) continue;
		if (i != Rank) {
			swap(mat[Rank], mat[i]);
		}
		for (i = Rank + 1; i < n; i++)
			if (mat[i][j]) {
				for (int k = m; k >= j; k--)
					mat[i][k] ^= mat[Rank][k];
			}
		Rank++;
	}
	for (int i = n - 1; i >= Rank; i--)
		if (mat[i][m] > 0) return -1;
	return m - Rank;
}

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d", &n);
		memset(mat, 0, sizeof(mat));
		for (int i = 0; i < n; i++)
			mat[i][i] = 1;
		for (int i = 0; i < n; i++) 
			scanf("%d", &s[i]);
		for (int i = 0; i < n; i++)
			scanf("%d", &e[i]);
		for (int i = 0; i < n; i++) {
			mat[i][n] = s[i] ^ e[i];
		}
		int a, b;
		while (scanf("%d%d", &a, &b) && a + b) {
			mat[b - 1][a - 1] = 1;
		}

		int ret = Gauss(n, n);
		if (ret == -1) puts("Oh,it's impossible~!!");
		else printf("%.0f\n", pow(2.0, ret));
	}
	return 0;
}