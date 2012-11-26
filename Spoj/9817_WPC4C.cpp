/*
 * Author:  Yang Zhang
 * Created Time:  2012/8/20 14:25:32
 * File Name: 9817_WPC4C.cpp
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

const double eps = 1e-8;
LL x, y;
int sig(double d) {
    return (d > eps) - (d < -eps);
}
int main() {
    freopen("in.txt", "r", stdin);
    int Test;
    scanf("%d", &Test);
    while (Test--) {
        LL maxS = 0, ansh = 0, answ = 0;
        cin >> x >> y;
        int bound = (int)(log((double)y) / log(2.0));
        for (int i = 0; i <= bound; i++) {
            LL h = 1, w;
            for (int j = 0; j < i; j++)
                h *= 2ll;
            w = h * 5 / 4;
            if (sig((double)h / w - 0.8) >= 0 && w <= x) {
                LL S = w * h;
                if (S > maxS || (S == maxS && h > ansh)) {
                    maxS = S;
                    ansh = h;
                    answ = w;
                }
            }
        }

        bound = (int)(log((double)x) / log(2.0));
        for (int i = 0; i <= bound; i++) {
            LL w = 1, h;
            for (int j = 0; j < i; j++)
                w *= 2ll;
            h = w * 5 / 4;
            if (sig((double)h / w - 0.8) >= 0 && h <= y) {
                LL S = w * h;
                if (S > maxS || (S == maxS && h > ansh)) {
                    maxS = S;
                    ansh = h;
                    answ = w;
                }
            }
        }
        cout << ansh << " " << answ << endl;
    }
    return 0;
}

