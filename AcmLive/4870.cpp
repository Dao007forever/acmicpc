/*
 * Author:  Yang Zhang
 * Created Time:  2012/7/12 15:06:07
 * File Name: 4870.cpp
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
int N, K, Lim;
int dp[2][22 * MAXN];
int F[MAXN], D[MAXN];

void update(int &x, int y) {
    if (x == -1 || y < x) x = y;
}

void work() {
    dp[0][0] = 0;
    int now = 0;
    for (int i = 1; i <= N; i++) {
        int cur = (i & 1);
        for (int j = 0; j <= now + F[i]; j++)
            dp[cur][j] = -1;
        for (int j = 0; j <= now; j++) {
            if (dp[!cur][j] != -1) {
                //closed
                update(dp[cur][j], max(0, dp[!cur][j] - K));
                //open
                if (dp[!cur][j] + D[i] <= Lim)
                    update(dp[cur][j + F[i]], dp[!cur][j] + D[i]);
            }
        }
        now += F[i];
    }
    for (int i = now; i >= 0; i--) {
        if (dp[N & 1][i] != -1) {
            printf("%d\n", i);
            return;
        }
    }
}

int main() {
    freopen("in.txt", "r", stdin);
    while (scanf("%d%d%d", &N, &K, &Lim)) {
        if (N == 0 && K == 0 && Lim == 0) break;
        for (int i = 1; i <= N; i++) {
            scanf("%d%d", &F[i], &D[i]);
        }
        work();
    }
    return 0;
}

