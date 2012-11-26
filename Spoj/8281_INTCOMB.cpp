/*
 * Author:  Yang Zhang
 * Created Time:  2012/7/10 23:57:40
 * File Name: 8281_INTCOMB.cpp
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

#define MAXN 100005
const LL inf = 1LL << 60;
int n;
int a[MAXN];
bool vst[MAXN];
LL dis[MAXN];
int que[100 * MAXN];

void work() {
    int head = 0, tail = 0;
    dis[0] = 0; vst[0] = true;
    que[tail++] = 0;
    while (head <= tail) {
        int u = que[head++];
        for (int i = 0; i < n; i++) {
            int v = (dis[u] + a[i]) % a[0];
            if (dis[u] + a[i] < dis[v]) {
                dis[v] = dis[u] + a[i];
                if (!vst[v]) {
                    vst[v] = true;
                    que[tail++] = v;
                }
            }
        }
        vst[u] = false;
    }

    LL ret = 0;
    for (int i = 1; i < a[0]; i++)
        if (dis[i] == inf) {
            ret = -1;
            break;
        } else ret += dis[i] / a[0];
    if (ret == -1) printf("Infinite\n");
    else cout << ret << endl;
}

int main() {
    freopen("in.txt", "r", stdin);
    int Test;
    scanf("%d", &Test);
    while (Test--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", a + i);
        sort(a, a + n);
        for (int i = 0; i <= 100000; i++) {
            dis[i] = inf; vst[i] = false;
        }
        work();
    }
    return 0;
}

