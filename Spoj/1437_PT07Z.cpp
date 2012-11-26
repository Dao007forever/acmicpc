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

const int MAXN = 50000 + 10;
const int MAXM = 4 * MAXN;
struct Edge
{
    int v, w, next;
}edge[MAXM];
int N, num;
int Head[MAXN];
long long dis[MAXN];

void addEdge(int u, int v, int w)
{
    edge[num].v = v;
    edge[num].w = w;
    edge[num].next = Head[u];
    Head[u] = num++;
}

void dfs(int now)
{
    for (int i = Head[now]; i != -1; i = edge[i].next)
    {
        int v = edge[i].v;
        if (dis[v] == -1)
        {
            dis[v] = dis[now] + (long long)edge[i].w;
            dfs(v);
        }
    }
}

int main()
{
    freopen("a", "r", stdin);
//	int t;
//    scanf("%d", &t);
//    while (t--)
//    {
        num = 0;
        memset(Head, -1, sizeof(Head));

        scanf("%d", &N);
        for (int i = 1; i < N; i++)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            addEdge(a, b, 1);
            addEdge(b, a, 1);
        }
        
        memset(dis, -1, sizeof(dis));
        dis[1] = 0;
        dfs(1);
        int k = 1;
        for (int i = 1; i <= N; i++)
            if (dis[i] > dis[k])
                k = i;
        memset(dis, -1, sizeof(dis));
        dis[k] = 0;
        dfs(k);
        for (int i = 1; i <= N; i++)
            if (dis[i] > dis[k])
                k = i;
        cout << dis[k] << endl;
//    }
    return 0;
}

