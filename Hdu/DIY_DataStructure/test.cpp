#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

struct point {
    int x, y;
    void input() {
        scanf("%d%d", &x, &y);
    }
};

const int max_n = 100000 + 10;

struct disjoint_set {
    int p[max_n], num[max_n], miny[max_n], maxy[max_n];
    void clear(int n, const point* pt) {
        for (int i = 0; i < n; ++i) {
            p[i] = i;
            num[i] = 1;
            miny[i] = maxy[i] = pt[i].y;
        }
    }
    int get_root(int k) {
        return p[k] == k ? k : (p[k] = get_root(p[k]));
    }
    void merge(int a, int b) {
        int x = get_root(a), y = get_root(b);
        num[y] += num[x];
        if (miny[x] < miny[y])
            miny[y] = miny[x];
        if (maxy[x] > maxy[y])
            maxy[y] = maxy[x];
        p[x] = y;
    }
};

struct segment_tree {
    struct node {
        int l, r, cnt, num;
        node() {
        }
        node(int _l, int _r): l(_l), r(_r), cnt(0), num(0) {
        }
    };
    node ch[max_n * 8];
    void build(int l, int r, int k = 0) {
        ch[k] = node(l, r);
        if (l == r)
            return;
        int mid = (l + r) / 2;
        build(l, mid, k * 2 + 1);
        build(mid + 1, r, k * 2 + 2);
    }
    void add(int l, int r, int val, int s, int k = 0) {
        int a = k * 2 + 1, b = k * 2 + 2;
        if (ch[k].l == l && ch[k].r == r) {
            ch[k].cnt += s;
            ch[k].num += val * s;
            return;
        }
        int mid = (ch[k].l + ch[k].r) / 2;
        if (r <= mid) {
            add(l, r, val, s, a);
        } else if (l > mid) {
            add(l, r, val, s, b);
        } else {
            add(l, mid, val, s, a);
            add(mid + 1, r, val, s, b);
        }
    }
    pair<int, int> get(int p) {
        pair<int, int> ans(0, 0);
        int k = 0;
        while (true) {
            ans.first += ch[k].cnt;
            ans.second += ch[k].num;
            if (ch[k].l == ch[k].r)
                break;
            int mid = (ch[k].l + ch[k].r) / 2;
            if (p <= mid)
                k = k * 2 + 1;
            else
                k = k * 2 + 2;
        }
        return ans;
    }
};

int n, m;
point p[max_n];
disjoint_set ds;
segment_tree st;
vector<int> vec;

void solve();
void pre_compute();
void make(int a, int b);

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i)
        solve();
    return 0;
}

void solve() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        p[i].input();
    pre_compute();
    ds.clear(n, p);
    scanf("%d", &m);
    for (int i = 0; i < m; ++i) {
        char buf[16];
        scanf("%s", buf);
        if (buf[0] == 'r') {
            int a, b;
            scanf("%d%d", &a, &b);
            make(a, b);
        } else {
            double c;
            scanf("%lf", &c);
            int p = upper_bound(vec.begin(), vec.end(), (int)c) - vec.begin();
            if (p == 0) {
                printf("0 0\n");
                continue;
            }
            pair<int, int> ans = st.get(p * 2 - 1);
            printf("%d %d\n", ans.first, ans.second);
        }
    }
    //for (int i = 0; i <= 10; ++i) {
        //pair<int, int> tmp = st.get(i);
        //printf("-- %d %d\n", tmp.first, tmp.second);
    //}
}

void pre_compute() {
    vec.clear();
    for (int i = 0; i < n; ++i)
        vec.push_back(p[i].y);
    sort(vec.begin(), vec.end());
    vec.resize(unique(vec.begin(), vec.end()) - vec.begin());
    for (int i = 0; i < n; ++i)
        p[i].y = lower_bound(vec.begin(), vec.end(), p[i].y) - vec.begin();
    st.build(0, vec.size() * 2);
    for (int i = 0; i < n; ++i)
        st.add(p[i].y * 2, p[i].y * 2, 1, 1);
}

void make(int a, int b) {
    int x = ds.get_root(a), y = ds.get_root(b);
    if (x == y)
        return;
    st.add(ds.miny[x] * 2, ds.maxy[x] * 2, ds.num[x], -1);
    st.add(ds.miny[y] * 2, ds.maxy[y] * 2, ds.num[y], -1);
    ds.merge(a, b);
    int k = ds.get_root(a);
    st.add(ds.miny[k] * 2, ds.maxy[k] * 2, ds.num[k], 1);
}
