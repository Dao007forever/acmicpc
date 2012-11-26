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

int N, K;
int cnt[1 << 10];
long long dp[11][1 << 10][101];
vector<int> valid_pos;

int bitcnt(int x) {
	int ret = 0;
	for (int i = 0; i < N; i++)
		if (x & (1 << i)) ret++;
	return ret;
}

int main() {
	cin >> N >> K;
	for (int i = 0; i < 1 << N; i++) {
		cnt[i] = bitcnt(i);
		if ((i & (i << 1)) == 0 && (i & (i >> 1)) == 0)
			valid_pos.push_back(i);
	}
	dp[0][0][K] = 1;
	for (int n = 0; n < N; n++) {
		for (int i1 = 0; i1 < valid_pos.size(); i1++) {
			int m1 = valid_pos[i1];
			for (int i2 = 0; i2 < valid_pos.size(); i2++) {
				int m2 = valid_pos[i2];
				if (m1 & m2 || m1 & (m2 << 1) || m1 & (m2 >> 1)) continue;
				for (int k = K - cnt[m1]; k - cnt[m2] >= 0; k--) {
					dp[n + 1][m2][k - cnt[m2]] += dp[n][m1][k];
				}
			}
		}
	}

	long long ret = 0;
	for (int i = 0; i < valid_pos.size(); i++) {
		ret += dp[N][valid_pos[i]][0];
	}
	cout << ret << endl;
	return 0;
}
