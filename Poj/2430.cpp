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

int N, M, B;
struct node {
	int x, y;
}p[1005];
int f[1005][1005][5], dp[1005][1005];

bool cmp(node A, node B)
{
	return A.y < B.y;
}

int main()
{
		cin >> N >> M >> B;
		for (int i = 1; i <= N; i++)
			cin >> p[i].x >> p[i].y;
		sort(p + 1, p + N + 1, cmp);
		memset(f, 63, sizeof(f));
		memset(dp, 63, sizeof(dp));
		f[0][1][0] = f[0][1][1] = 0;
		f[0][1][2] = f[0][2][3] = 0;
		dp[0][1] = dp[0][2] = dp[0][0] = 0;
		for (int i = 1; i <= N; i++) {
			int d = p[i].y - p[i - 1].y;
			if (p[i].x == 1) {
				for (int j = 1; j <= M; j++) {
					f[i][j][0] = min(f[i - 1][j][0], f[i - 1][j][3]) + d;
					f[i][j][0] = min(f[i][j][0], dp[i - 1][j - 1] + 1);
					f[i][j][2] = min(f[i - 1][j][2], f[i - 1][j][3]) + 2 * d;
					f[i][j][2] = min(f[i][j][2], dp[i - 1][j - 1] + 2);
					f[i][j][3] = min(f[i - 1][j][3] + 2 * d, f[i - 1][j - 1][1] + d + 1);
				}
			} else {
				for (int j = 1; j <= M; j++) {
					f[i][j][1] = min(f[i - 1][j][1], f[i - 1][j][3]) + d;
					f[i][j][1] = min(f[i][j][1], dp[i - 1][j - 1] + 1);
					f[i][j][2] = min(f[i - 1][j][2], f[i - 1][j][3]) + 2 * d;
					f[i][j][2] = min(f[i][j][2], dp[i - 1][j - 1] + 2);
					f[i][j][3] = min(f[i - 1][j][3] + 2 * d, f[i - 1][j - 1][0] + d + 1);
				}
			}
			for (int j = 0; j <= M; j++)
				dp[i][j] = min(min(f[i][j][0], f[i][j][1]), min(f[i][j][2], f[i][j][3]));
		}
		cout << dp[N][M] << endl;
	return 0;
}
