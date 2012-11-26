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

int dp[66][66][66][66];
string A, B;

int dfs(int lA, int rA, int lB, int rB) {
	if (lA > rA || lB > rB) return 0;
	if (dp[lA][rA][lB][rB] != -1) return dp[lA][rA][lB][rB];
	int &ret = dp[lA][rA][lB][rB];
	ret = 0;
	char ch = A[lA];
	if (ch == A[rA] && ch == B[lB] && ch == B[rB]) {
		if (lA == rA || lB == rB) {
			ret = max(ret, dfs(lA + 1, rA - 1, lB + 1, rB - 1) + 1);
		} else {
			ret = max(ret, dfs(lA + 1, rA - 1, lB + 1, rB - 1) + 2);
		}
	}
	ret = max(ret, dfs(lA + 1, rA, lB, rB));
	ret = max(ret, dfs(lA, rA - 1, lB, rB));
	ret = max(ret, dfs(lA, rA, lB + 1, rB));
	ret = max(ret, dfs(lA, rA, lB, rB - 1));
	return ret;
}

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d\n", &Test);
	for (int cas = 1; Test--; cas++) {
		printf("Case %d: ", cas);
		cin >> A >> B;
		memset(dp, -1, sizeof(dp));
		int ret = dfs(0, A.size() - 1, 0, B.size() - 1);
		cout << ret << endl;
	}
	return 0;
}