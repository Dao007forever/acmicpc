/*
 * 类似LCS，f(i,j)表示子串A前i个字母，子串B前j个字母的最小公共母串的长度，如果A[i]=B[j]，那么f(i,j)=f(i-1,j-1)+1，否则f(i,j)=min{f(i-1,j),f(i,j-1)}+1，同时记录方案数即可
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

const int mod = 1000000007;
char s1[2222], s2[2222];
int f[2222][2222], g[2222][2222];
int n, m;

int main() {
	scanf("%s", s1 + 1);
	scanf("%s", s2 + 1);
	n = strlen(s1 + 1), m = strlen(s2 + 1);
	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++) {
			if (i == 0 || j == 0) {
				f[i][j] = i + j;
				g[i][j] = 1;
			} else {
				if (s1[i] == s2[j]) {
					f[i][j] = f[i - 1][j - 1] + 1;
					g[i][j] = g[i - 1][j - 1];
				}
				else {
					g[i][j] = 0;
					f[i][j] = min(f[i][j - 1], f[i - 1][j]) + 1;
					if (f[i][j - 1] + 1 == f[i][j]) {
						g[i][j] += g[i][j - 1];
						g[i][j] %= mod;
					}
					if (f[i - 1][j] + 1 == f[i][j]) {
						g[i][j] += g[i - 1][j];
						g[i][j] %= mod;
					}
				}
			}
		}
	cout << g[n][m] << endl;
	return 0;
}
