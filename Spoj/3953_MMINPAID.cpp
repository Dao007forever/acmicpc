#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

struct node {
	int state, u;
};
int N, M;
int a[11], b[11], c[11], p[11], r[11];
int dp[1 << 15][11];

int main()
{
	freopen("in.txt", "r", stdin);
	cin >> N >> M;
	for (int i = 0; i < M; i++)
		cin >> a[i] >> b[i] >> c[i] >> p[i] >> r[i];

	memset(dp, -1, sizeof(dp));
	dp[1][1] = 0;
	node s;
	s.state = 1;
	s.u = 1;
	queue<node> Q;
	Q.push(s);
	while (!Q.empty()) {
		s = Q.front();
		Q.pop();
		for (int i = 0; i < M; i++)
			if (s.u == a[i]) {
				int tmp = s.state | (1 << (b[i] - 1));
				if (dp[tmp][b[i]] == -1 || dp[s.state][s.u] + r[i] < dp[tmp][b[i]]) {
					dp[tmp][b[i]] = dp[s.state][s.u] + r[i];
					node t;
					t.state = tmp;
					t.u = b[i];
					Q.push(t);
				}
				if (s.state & (1 << (c[i] - 1))) {
					if (dp[tmp][b[i]] == -1 || dp[s.state][s.u] + p[i] < dp[tmp][b[i]]) {
						dp[tmp][b[i]] = dp[s.state][s.u] + p[i];
						node t;
						t.state = tmp;
						t.u = b[i];
						Q.push(t);
					}
				}
			}
	}
	int ret = 1000000000;
	for (int i = 0; i < (1 << N); i++)
		if (dp[i][N] != -1 && dp[i][N] < ret)
			ret = dp[i][N];
	if (ret == 1000000000)
		cout << "impossible" << endl;
	else cout << ret << endl;
	return 0;
}
