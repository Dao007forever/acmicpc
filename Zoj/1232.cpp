/*
 * Author:  Yang Zhang
 * Created Time:  2012/8/15 10:59:07
 * File Name: 1232.cpp
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

#define MAXN 105
const int inf = 10000000;
int N, A, B, M, L, K;
int mat[MAXN][MAXN], vis[MAXN][15];
int dp[MAXN][15];
bool adj[MAXN][MAXN];

void floyd() {
    for (int k = 1; k <= N; k++)
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                if (mat[i][k] + mat[k][j] < mat[i][j]) {
                    mat[i][j] = mat[i][k] + mat[k][j];
                    if (k <= A && mat[i][j] <= L)
                        adj[i][j] = true;
                }
}

int main() {
    freopen("in.txt", "r", stdin);
    int Test;
    scanf("%d", &Test);
    while (Test--) {
        scanf("%d%d%d%d%d", &A, &B, &M, &L, &K);
        N = A + B;
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                if (i != j) mat[i][j] = inf;
        memset(adj, 0, sizeof(adj));
        while (M--) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            mat[u][v] = mat[v][u] = w;
            if (w <= L) adj[u][v] = adj[v][u] = true;
        }
        floyd();
        memset(dp, -1, sizeof(dp));
        for (int i = 1; i <= N; i++)
            dp[i][0] = mat[1][i];
        for (int i = 0; i <= K; i++)
            dp[1][i] = 0;
        for (int i = 1; i <= N; i++)
            for (int j = 0; j <= K; j++)
                if (dp[i][j] != -1) {
                    for (int k = 1; k <= N; k++) {
                        if (dp[k][j] == -1 || dp[i][j] + mat[i][k] < dp[k][j]) {
                            dp[k][j] = dp[i][j] + mat[i][k];
                        }
                        if (j < K && adj[i][k]) {
                            if (dp[k][j + 1] == -1 || dp[i][j] < dp[k][j + 1]) {
                                dp[k][j + 1] = dp[i][j];
                            }
                        }
                    }
                }
        int ret = inf;
        for (int i = 1; i <= K; i++)
            if (dp[N][i] != -1)
                ret = min(ret, dp[N][i]);
        printf("%d\n", ret);
    }
    return 0;
}
