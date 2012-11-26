/*
 * Author:  Yang Zhang
 * Created Time:  2012/7/12 16:25:54
 * File Name: 4868.cpp
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

string s;

bool check(string st) {
    string tmp = st;
    reverse(tmp.begin(), tmp.end());
    return tmp == st;
}

int main() {
    freopen("in.txt", "r", stdin);
    while (cin >> s && s != "0") {
        int n = atoi(s.c_str()), i = 0;
        char st[50], buf[50];
        sprintf(st, "%%0%dd", s.length());
        do {
            sprintf(buf, st, n + i);
            i++;
        } while (!check(string(buf)));
        printf("%d\n", i - 1);
    }
    return 0;
}

