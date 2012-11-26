/*
 * Author:  Yang Zhang
 * Created Time:  2012/7/12 15:46:32
 * File Name: 4872.cpp
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

double inf = 1e50;
int n;
double mat[1005][1005];
double d[1005];
bool vst[1005];
int x[1005], y[1005];

double dist(int x, int y, int xx, int yy) {
    return sqrt((double)(x - xx) * (x - xx) + (double)(y - yy) * (y - yy));
}

void prim() {
    for (int i = 0; i < n; i++) {
        d[i] = inf, vst[i] = false;
    }
    double sum = 0.0;
    d[0] = 0.0;
    for (int i = 0; i < n; i++) {
        double Min = inf;
        int k = -1;
        for (int j = 0; j < n; j++)
            if (!vst[j] && d[j] < Min) {
                Min = d[j];
                k = j;
            }
        if (k == -1) break;
        vst[k] = true;
        sum += d[k];
        for (int j = 0; j < n; j++)
            if (!vst[j] && mat[k][j] < d[j]) {
                d[j] = mat[k][j];
            }
    }
    printf("%.2f\n", sum);
}

int main() {
    freopen("in.txt", "r", stdin);
    while (scanf("%d", &n) && n) {
        for (int i = 0; i < n; i++)
            scanf("%d%d", &x[i], &y[i]);
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                mat[i][j] = mat[j][i] = dist(x[i], y[i], x[j], y[j]);
        prim();
    }
    return 0;
}

