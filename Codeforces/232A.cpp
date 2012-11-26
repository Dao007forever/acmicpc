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

int mat[111][111];
int calc(int x) {
    return x * (x - 1) * (x - 2) / 6;
}
int main(int argc, char const *argv[])
{
    int k, i;
    cin >> k;
    for (i = 100; i >= 1; i--) {
        if (calc(i) <= k) break;
    }
    int now = calc(i);
    int n = i;
    memset(mat, 0, sizeof(mat));
    for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++)
            mat[j][k] = j == k ? 0 : 1;
    }
    while (now < k) {
        for (int j = n; j >= 2; j--) {
            int add = j * (j - 1) / 2;
            if (now + add > k) continue;
            now += add;
            for (int u = 0; u < j; u++)
                mat[n][u] = mat[u][n] = 1;
            n++;
            break;
        }
    }

    printf("%d\n", n);
    for (i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d", mat[i][j]);
        printf("\n");
    }
    return 0;
}