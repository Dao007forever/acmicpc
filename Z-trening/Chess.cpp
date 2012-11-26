/*
 * N*M的棋盘中，放K个King的方案数
 * 很好的状压DP，f(i,j,k)表示前i行，且第i行的状态为j，还有k个King没有放的方案数，需要先预处理出那些可能的状态，以及每种状态当前行有多少个1，即左右bit都为1的方案数，然后枚举上一行的状态m1和当前行的状态m2，以及上一行还有多少个King没有放，然后状态转移。最后答案就是sigma{f(n,valid_pos,0)}
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

const int mod = 1000007;
int N, M, K;
int cnt[1 << 10];
int dp[52][1 << 10][10];
vector<int> valid_pos;

int bitcnt(int x)
{
	int ret = 0;
	for (int i = 0; i < M; i++)
		if (x & (1 << i)) ret++;
	return ret;
}

int main()
{
	cin >> N >> M >> K;
	for (int i = 0; i < 1 << M; i++) {
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
					dp[n + 1][m2][k - cnt[m2]] %= mod;
				}
			}
		}
	}

	int ret = 0;
	for (int i = 0; i < valid_pos.size(); i++) {
		ret += dp[N][valid_pos[i]][0];
		ret %= mod;
	}
	cout << ret << endl;
	return 0;
}
