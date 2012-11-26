/*
 * Author: Yang Zhang
 * Created Time: Wed 29 Aug 2012 02:28:38 PM CST
 * File Name: 219C.cpp
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

int n, K;
string s;
int dp[500005][27], pre[500005][27];
void output(int i, int j) {
	if (pre[i][j] != -1) {
		output(i - 1, pre[i][j]);
	}
	cout << (char)('A' + j);
}
int main() {
	cin >> n >> K >> s;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < K; j++)
			dp[i][j] = 1000000;
	for (int i = 0; i < K; i++) {
		if (s[0] == 'A' + i) dp[0][i] = 0;
		else dp[0][i] = 1;
		pre[0][i] = -1;
	}
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < K; j++)
			for (int k = 0; k < K; k++) {
				if (j == k) continue;
				if (s[i] == 'A' + j) {
					if (dp[i - 1][k] < dp[i][j]) {
						dp[i][j] = dp[i - 1][k];
						pre[i][j] = k;
					}
				} else {
					if (dp[i - 1][k] + 1 < dp[i][j]) {
						dp[i][j] = dp[i - 1][k] + 1;
						pre[i][j] = k;
					}
				}
			}
	}
	int ret = 1000000, retk;
	for (int i = 0; i < K; i++)
		if (dp[n - 1][i] < ret) {
			ret = dp[n - 1][i];
			retk = i;
		}
	cout << ret << endl;
	output(n - 1, retk);
	cout << endl;
	return 0;
}

