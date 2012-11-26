#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int n, m, t;
const int maxn = 32;
long long com[maxn][maxn];

void init() {
	for (int i = 0; i < maxn; i++)
		com[i][0] = com[i][i] = 1;
	for (int i = 1; i < maxn; i++)
		for (int j = 1; j < i; j++)
			com[i][j] = com[i - 1][j - 1] + com[i - 1][j];
}

int main() {
	init();
	cin >> n >> m >> t;
	int dn = max(4, t - m), up = min(n, t - 1);
	long long res = 0;
	for (int i = dn; i <= up; i++)
		res += com[n][i] * com[m][t - i];
	cout << res << endl;
}
