/*
 * Author:  Yang Zhang
 * Created Time:  2012/7/6 10:13:17
 * File Name: 7630.cpp
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

#define MAXN 15
LL dp[MAXN][MAXN][1 << MAXN];
vector<int> p[MAXN];
char mat[MAXN][MAXN];
int n, m, num;

int main() {
    freopen("in.txt", "r", stdin);
    int Test;
    scanf("%d", &Test);
    while (Test--) {
        scanf("%d%d%d", &n, &m, &num);
        for (int i = 0; i < n; i++)
            scanf("%s", mat[i]);
        for (int i = 0; i <= m; i++)
            p[i].clear();
        for (int s = 0; s < 1 << m; s++) {
            int cnt = 0;
            for (int j = 0; j < m; j++)
                if (s & (1 << j)) cnt++;
            p[cnt].PB(s);
        }

        LL ret = 0;
        dp[0][0][0] = 1;
        for (int i = 0; i <= n; i++)
            for (int j = 0; j <= i && j <= num; j++)
                for (int k = 0, st; k < p[j].size(); k++) 
                if (dp[i][j][st = p[j][k]]) {
                    LL now = dp[i][j][st];
                    dp[i][j][st] = 0;
                    if (i == n) {
                        if (j == num)
                            ret += now;
                    }
                    else {
                        dp[i + 1][j][st] += now;
                        if (j < num)
                        for (int l = 0; l < m; l++)
                            if (mat[i][l] == '1' && !(st & (1 << l))) {
                                dp[i + 1][j + 1][st | (1 << l)] += now;
                            }
                    }
                }
        cout << ret << endl;
    }
    return 0;
}

