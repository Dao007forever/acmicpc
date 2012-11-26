/*
 * 一个由'L'和'P'构成的序列，要求长度为N的且任意一段里L和P的个数相差不超过2个的这样一个序列是所有可能的序列中字典序第几小的，答案模M
 * DP, 在数轴上维护N个点(对应N个字母)，最左端的点纵坐标为0，遇到字母L，则当前点的纵坐标为上一个点纵坐标减一，遇到P则加一，然后把这些点顺次连接起来，就是一条折线了。f(i,j,k,l)表示当前在第i个，之前最低为j，最高为k，当前高度为l的方案数，如果当前是L，那么就可以更新f(i+1,min(l-1,j),k,l-1)，如果是P，更新f(i+1,j,max(l+1,k),l+1)，用滚动数组。
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

const int maxn = 1000005;
struct state {
	int now, lo, hi;
}T[maxn];
char st[maxn];
int N, Mod;
int dp[2][7][7][7];

int main()
{
	cin >> N >> Mod;
	cin >> st;
	T[0].now = T[0].hi = T[0].lo = 3;
	if (st[0] == 'L') {
		T[0].lo = T[0].now = 2;
	} else {
		T[0].hi = T[0].now = 4;
	}
	for (int i = 1; i < N; i++)
		if (st[i] == 'L') {
			T[i].now = T[i - 1].now - 1;
			T[i].lo = min(T[i - 1].lo, T[i].now);
			T[i].hi = T[i - 1].hi;
		} else {
			T[i].now = T[i - 1].now + 1;
			T[i].lo = T[i - 1].lo;
			T[i].hi = max(T[i - 1].hi, T[i].now);
		}
	for (int i = 1; i <= 3; i++)
		for (int j = 3; j <= i + 2; j++)
			for (int k = i; k <= j; k++)
				dp[0][i][j][k] = 1;
	int ret = 0;
	for (int i = 1; i <= N; i++) {
		int p = i & 1, q = 1 - p;
		if (st[N - i] == 'P') {
			int lo = min(T[N - i].lo, T[N - i].now - 2);
			int hi = i == N ? 3 : T[N - i - 1].hi;
			int now = T[N - i].now - 2;
			ret = (ret + dp[q][lo][hi][now]) % Mod;
		}
		for (int lo = 1; lo <= 3; lo++)
			for (int hi = 3; hi <= lo + 2; hi++)
				for (int now = lo; now <= hi; now++) {
					dp[p][lo][hi][now] = 0;
					if (now + 1 - lo <= 2) //P
						dp[p][lo][hi][now] = (dp[p][lo][hi][now] + dp[q][lo][max(hi, now + 1)][now + 1]) % Mod;
					if (hi - now + 1 <= 2) // L
						dp[p][lo][hi][now] = (dp[p][lo][hi][now] + dp[q][min(lo, now - 1)][hi][now - 1]) % Mod;
				}
	}
	cout << (ret + 1) % Mod << endl;
	return 0;
}
