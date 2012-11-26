/*
 * Author:  Yang Zhang
 * Created Time:  2012/7/3 16:51:54
 * File Name: 3179.cpp
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

const int MAXN = 20005; 
const double eps = 1e-6;
int sig(double d) {
    return (d > eps) - (d < -eps);
}
struct Point {
    double x, y;
    int cost, id;

    void input() {
        scanf("%lf%lf%d", &x, &y, &cost);
    }

    bool operator == (const Point &p) const {
        return sig(x - p.x) == 0 && sig(y - p.y) == 0;
    }

    bool operator < (const Point &p) const {
        return sig(x - p.x) != 0 ? x < p.x : sig(y - p.y) < 0;
    }
}ps[MAXN];
int n, m;
int id[MAXN];

double cross(const Point &o, const Point &a, const Point &b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

double dot(const Point &o, const Point &a, const Point &b) {
    return (a.x - o.x) * (b.x - o.x) + (a.y - o.y) * (b.y - o.y);
}

int graham(Point *p, int n, int *ch) {
#define push(x) ch[len++] = x
#define pop(x) len--
    sort(p, p + n);
    int len = 0, len0 = 1, i;
    for (i = 0; i < n; i++) {
        while (len > len0 && sig(cross(p[ch[len - 1]], p[ch[len - 2]], p[i])) <= 0)
            pop();
        push(i);
    }
    len0 = len;
    for (i = n - 2; i >= 0; i--) {
        while (len > len0 && sig(cross(p[ch[len - 1]], p[ch[len - 2]], p[i])) <= 0)
            pop();
        push(i);
    }
    return len - 1;
}

int main() {
    freopen("in.txt", "r", stdin);
    while (scanf("%d", &n) && n) {
        for (int i = 0; i < n; i++)
            ps[i].input(), ps[i].id = i + 1;

        m = graham(ps, n, id);
        vector<pair<int, int> > cc;
        for (int i = 0; i < m; i++) {
            Point o = ps[id[i]], a = ps[id[(i - 1 + m) % m]], b = ps[id[(i + 1) % m]];
            if (sig(dot(o, a, b)) >= 0) 
                cc.PB(MP(ps[id[i]].cost, ps[id[i]].id));
        }
        if (cc.size() < 3) {
            printf("Impossible\n");
        } else {
            sort(cc.begin(), cc.end());
            while (cc.size() > 3) cc.pop_back();
            for (int i = 0; i < 3; i++)
                swap(cc[i].first, cc[i].second);
            sort(cc.begin(), cc.end());
            printf("%d %d %d\n", cc[0].first, cc[1].first, cc[2].first);
        }
    }
    return 0;
}

