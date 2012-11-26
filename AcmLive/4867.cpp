/*
 * Author:  Yang Zhang
 * Created Time:  2012/7/12 13:22:33
 * File Name: 4867.cpp
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
int mat[MAXN][MAXN], dp[MAXN][MAXN];
int n, m;

int main() {
    freopen("in.txt", "r", stdin);
    while (scanf("%d%d", &n, &m) && n && m) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                scanf("%d", &mat[i][j]);
        memset(dp, 0, sizeof(dp));
        for (int i = 0; i < n; i++)
            dp[i][0] = (mat[i][0] == 1);
        for (int j = 0; j < m; j++)
            dp[0][j] = (mat[0][j] == 1);
        for (int i = 1; i < n; i++)
            for (int j = 1; j < m; j++)
                if (mat[i][j] == 1)
                    dp[i][j] = min(min(dp[i - 1][j], dp[i][j - 1]), dp[i - 1][j - 1]) + 1;
                else dp[i][j] = 0;
        int ret = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                ret = max(ret, dp[i][j]);
        printf("%d\n", ret);
    }
    return 0;
}

