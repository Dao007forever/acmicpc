/*
 * Author:  Yang Zhang
 * Created Time:  2012/7/12 10:55:21
 * File Name: 6852_CT16E.cpp
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

double p[20][20], dp[1 << 18];
int bitcnt[1 << 18];
int n;

int main() {
    freopen("in.txt", "r", stdin);
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lf", &p[i][j]);
    for (int i = 1; i < (1 << n); i++)
        bitcnt[i] = bitcnt[i & (i - 1)] + 1;
    memset(dp, 0, sizeof(dp));
    dp[(1 << n) - 1] = 1.0;
    for (int s = (1 << n) - 1; s >= 0; s--) {
        if (bitcnt[s] < 2) continue;
        for (int i = 0; i < n; i++)
        if (s & (1 << i))
            for (int j = 0; j < n; j++)
            if (s & (1 << j))
                dp[s - (1 << i)] += dp[s] * p[j][i] / (bitcnt[s] * (bitcnt[s] - 1) / 2);
    }
    for (int i = 0; i < n; i++)
        printf("%.6f%c", dp[1 << i], i == n - 1 ? '\n' : ' ');
    return 0;
}

