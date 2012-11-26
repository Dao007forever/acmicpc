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

const int inf = 1000000000;
int n, m;
int g[55][55];
map<string, int> mp;

int main()
{
    freopen("in.txt", "r", stdin);
    int cas = 1;
    while (scanf("%d%d", &n, &m) != EOF && (n || m))
    {
        printf("Network %d: ", cas++);
        for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        if (i != j)
            g[i][j] = inf;
        mp.clear();
        int cnt = 0;
        for (int i = 0; i < m; i++)
        {
            char s1[1111], s2[1111];
            scanf("%s %s", s1, s2);
            string t1 = s1;
            string t2 = s2;
            if (mp.find(t1) == mp.end()) mp[t1] = cnt++;
            if (mp.find(t2) == mp.end()) mp[t2] = cnt++;
            int id1 = mp[t1], id2 = mp[t2];
            g[id1][id2] = g[id2][id1] = 1;
        }
        for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        if (i != j && i != k && j != k)
            g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
        int ans = 0;
        for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        if (i != j)
            ans = max(ans, g[i][j]);
        if (ans == inf) puts("DISCONNECTED");
        else printf("%d\n", ans);
        puts("");
    }
    return 0;
}