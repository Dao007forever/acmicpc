/*
 * Author:  Yang Zhang
 * Created Time:  2012/7/12 16:01:36
 * File Name: 4869.cpp
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

int n;
int a[250005];

int main() {
    freopen("in.txt", "r", stdin);
    while (scanf("%d", &n) && n) {
        for (int i = 0; i < n; i++)
            scanf("%d", &a[i]);
        int sum = 0, ret = -1000000000;
        for (int i = 0; i < n; i++) {
            sum += a[i];
            ret = max(ret, sum);
            if (sum < 0) sum = 0;
        }
        printf("%d\n", ret);
    }
    return 0;
}

