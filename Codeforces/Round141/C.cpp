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

char mat[555][555];
bool dp[10][16][555][555];
int main(int argc, char const *argv[])
{
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		cin >> mat[i];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			if (mat[i][j] == '*') dp[0][15][i][j] = true;
			else {
				for (int mask = 0; mask < 15; mask++)
					dp[0][mask][i][j] = true;
			}
		}
	int ret = 0;
	for (int k = 1; k <= 9; k++) {
		for (int i = 0; i + (1<<k)-1 < n; i++)
			for (int j = 0; j + (1<<k)-1 < m; j++) {
				int t = 1<<(k - 1);
				for (int mask = 0; mask < 16; mask++) {
					bool &flag = dp[k][mask][i][j];
					flag = true;
					if (mask & 1) {
						flag &= dp[k - 1][15][i][j];
					} else {
						flag &= dp[k - 1][mask][i][j];
					}

					if (mask & 2) {
						flag &= dp[k - 1][15][i][j + t];
					} else {
						flag &= dp[k - 1][mask][i][j + t];
					}

					if (mask & 4) {
						flag &= dp[k - 1][15][i + t][j];
					} else {
						flag &= dp[k - 1][mask][i + t][j];
					}

					if (mask & 8) {
						flag &= dp[k - 1][15][i + t][j + t];
					} else {
						flag &= dp[k - 1][mask][i + t][j + t];
					}

					if (k > 1 && flag) {
						ret++;
						//cout << k << " " << i << " " << j << endl;
					}
				}
			}
	}
	cout << ret << endl;
	return 0;
}