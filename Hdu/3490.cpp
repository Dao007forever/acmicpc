/*
 * Author:  Yang Zhang
 * Created Time:  2012/5/26 22:34:37
 * File Name: 3490.cpp
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

map<string, pair<int, int> > mp;
map<int, int> s1, s2;

void remove(map<int, int> &s, int x) {
    if (--s[x] == 0) s.erase(x); 
}

int calc(map<int, int>&s) {
    map<int, int>::iterator ib = s.begin(), ie = s.end();
    return (--ie)->first - ib->first;
}

int main() {
    int Test;
    scanf("%d", &Test);
    while (Test--) {
        int n;
        mp.clear();
        s1.clear(); s2.clear();
        scanf("%d", &n);
        while (n--) {
            int op;
            char str[15];
            scanf("%d%s", &op, str);
            if (op == 1) {
                int x, y;
                scanf("%d%d", &x, &y);
                mp[str] = pair<int, int>(x, y);
                s1[x - y]++; s2[x + y]++;
            } else {
                map<string, pair<int, int> >::iterator it = mp.find(str);
                remove(s1, it->second.first - it->second.second);
                remove(s2, it->second.first + it->second.second);
                mp.erase(it);
            }
            if (mp.size() == 0) puts("-1");
            else {
                printf("%d\n", max(calc(s1), calc(s2)));
            }
        }
        puts("");
    }
    return 0;
}

