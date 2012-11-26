/*
 * Author:  Yang Zhang
 * Created Time:  2012/7/12 14:37:39
 * File Name: 4871.cpp
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

#define MAXN 1005
const int mod = 1000000;
int n;
int dp[MAXN][MAXN];

int main() {
    freopen("in.txt", "r", stdin);
    dp[2][0] = dp[2][1] = 1;
    for (int i = 3; i <= 1000; i++) {
        dp[i][0] = 1;
        for (int j = 0; j < i; j++)
            dp[i][j] = (dp[i][j - 1] + dp[i - 1][j]) % mod;
    }
    while (scanf("%d", &n) && n) {
        int ret = 0;
        for (int i = 0; i < n; i++)
            ret = (ret + dp[n][i]) % mod;
        printf("%d\n", ret);
    }
    return 0;
}

