#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <set>
using namespace std;
#define SZ(v) ((int)(v).size())
#define REP(i, n) for (int i = 0; i < (n); ++i) 
const int maxint = -1u>>1;

const int maxn = 40000 + 10;
const double eps = 1e-10;

int sgn(double x) {
    return (x > eps) - (x < -eps);
}

double x0;

struct circle {
    double r, x, y;
    
    void input() {
        scanf ("%lf%lf%lf", &r, &x, &y);
    }
    
    double gety(bool up) {
        double dy = sqrt(abs(r * r - (x - x0) * (x - x0)));
        return up? y + dy : y - dy;
    }
};

circle c[maxn];
bool f[maxn];
int n;

struct node {
    int id;
    bool f;
    
    node() {}
    node(int _id, bool _f): id(_id), f(_f) {}
    
    bool operator<(const node& rhs) const {
        double y1 = c[id].gety(f);
        double y2 = c[rhs.id].gety(rhs.f);
        //printf ("cmp %d %d %lf %d %d %lf\n", id, f, y1,
                //rhs.id, rhs.f, y2);
        return sgn(y1 - y2) == 0? f < rhs.f : sgn(y1 - y2) < 0;
    }
};

struct event {
    double x;
    int id;
    bool f;
    
    event () {}
    event (double _x, int _id, bool _f): 
        x(_x), id(_id), f(_f) {}
    
    bool operator<(const event& e) const {
        return sgn(x - e.x) < 0;
    }
};

vector<event> vec;
set<node> st;

void gao() {
    st.clear();
    sort (vec.begin(), vec.end());
    REP (i, 2 * n) {
        x0 = vec[i].x;
        if (vec[i].f) {
            st.erase (node(vec[i].id, 0));
            st.erase (node(vec[i].id, 1));
            continue;
        }
        node now = node(vec[i].id, 0);
        st.insert (now);
        //printf ("here %lf %d\n", x0, vec[i].id);
        set<node>::iterator it = st.find(now);
        set<node>::iterator p1 = it, p2 = ++it;
        if (p1 != st.begin() && p2 != st.end()) {
            --p1;
            //printf ("find %d %d\n", p1->id, p2->id);
            if (p1->id == p2->id || f[p1->id] || f[p2->id]) {
                f[vec[i].id] = true;
            }
        }
        st.insert (node(vec[i].id, 1));
    }
}

int main() {
    while (scanf ("%d", &n), n) {
        vec.clear();
        REP (i, n) {
            c[i].input();
            f[i] = false;
            vec.push_back(event(c[i].x - c[i].r, i, 0));
            vec.push_back(event(c[i].x + c[i].r, i, 1));
        }
        gao();
        int res = 0;
        REP (i, n) {
            res += !f[i];
        }
        printf ("%d\n", res);
        bool fg = false;
        REP (i, n) if (!f[i]) {
            if (fg) putchar (' ');
            fg = true;
            printf ("%d", i + 1);
        }
        puts ("");
    }
    return 0;
}
