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

int mat[300][300];
int nxt[300];
int main(int argc, char const *argv[])
{
	int n;
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		memset(mat, 0, sizeof(mat));
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) nxt[i] = i;
		int k = n * n;
		for (int i = 1; k >= 1; i = i % n + 1, k--) {
			mat[i][nxt[i]] = k;
			nxt[i] = nxt[i] % n + 1;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) 
				printf("%d%c", mat[i][j], j == n ? '\n' : ' ');
		}
	}
	return 0;
}