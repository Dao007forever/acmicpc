#include <vector>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define MAXN 1005
int n;
char s1[MAXN], s2[MAXN];
bool f[MAXN][MAXN];
short p[MAXN][MAXN];
short v1[MAXN], v2[MAXN];
vector<int> ans;

void output(int x, int y) {
	if (x == 0 && y == 0) return;
	ans.push_back(p[x][y]);
	if (p[x][y] == 22) output(x, y - 2);
	else if (p[x][y] == 11) output(x - 2, y);
	else output(x - 1, y - 1);
}

int main() {
	freopen("in.txt", "r", stdin);
	cin >> n;
	scanf("%s\n%s", s1, s2);
	for (int i = 1; i <= n; i++) {
		v1[i] = (s1[i - 1] == '1');
		v2[i] = (s2[i - 1] == '1');
	}
	f[0][0] = true;
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= n; j++)
			if (f[i][j]) {
				if (v1[i + 1] != v1[i + 2]) {
					f[i + 2][j] = true;
					p[i + 2][j] = 11;
				}
				if (v2[j + 1] != v2[j + 2]) {
					f[i][j + 2] = true;
					p[i][j + 2] = 22;
				}
				if (v1[i + 1] != v2[j + 1]) {
					f[i + 1][j + 1] = true;
					p[i + 1][j + 1] = 12;
				}
			}
	if (!f[n][n]) {
		cout << "Impossible" << endl;
		return 0;
	}
	output(n, n);
	reverse(ans.begin(), ans.end());
	for (int i = 0; i < ans.size(); i++)
		printf("%d", ans[i]);
	return 0;
}
