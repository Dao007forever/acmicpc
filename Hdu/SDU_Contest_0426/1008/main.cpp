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
const int maxV1 = 505, maxV2 = 55, maxn = 305;
int upV1, upV2, n, P[maxn], H[maxn], S[maxn], F[maxV1][maxV2][2];

void update(int &a, int up) {
	a = max(a, up);
}

int main() {
freopen("test.in", "r", stdin);
	for (int Case = 1; scanf("%d %d %d", &upV1, &upV2, &n) && upV1 + upV2 + n; Case++) {
		for (int i = 1; i <= n; i++)
			scanf("%d %d %d", P + i, H + i, S + i);
		memset(F, -1, sizeof(F));
		F[0][0][0] = 0;
		for (int i = 1; i <= n; i++) {
			for (int v1 = upV1; v1 >= 0; v1--) for (int v2 = upV2; v2 >= 0; v2--)
			for (int s = 1; s >= 0; s--) if (F[v1][v2][s] != -1) {
				int cur = F[v1][v2][s];
				if (P[i] + v1 <= upV1)
					update(F[P[i] + v1][v2][s], cur + H[i]);
				if (P[i] + v2 <= upV2)
					update(F[v1][P[i] + v2][s], cur + H[i]);
				if (S[i])
					F[v1][v2][s] = -1;
				if (s == 0)
					update(F[v1][v2][1], cur + H[i]);
			}
		}
		int res = -1;
		for (int v1 = 0; v1 <= upV1; v1++)
		for (int v2 = 0; v2 <= upV2; v2++)
		for (int s = 0; s < 2; s++)
			res = max(res, F[v1][v2][s]);
		printf("Case %d: %d\n\n", Case, res);
	}
}
