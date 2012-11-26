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

const int MAXN = 1000 + 10;
const int MAXM = 1000000 + 10;
struct Edge
{
    int u, v, next;
    int use, can;
    double w;
}edge[MAXM], ans[MAXN];
struct Node
{
    int x, y, p;
}ps[MAXN];
int N, M, cnt;
int p[MAXN], rank[MAXN];
int Head[MAXN], vis[MAXN];
double max1, max2;

double dist(Node a, Node b)
{
    return sqrt((double)(a.x - b.x) * (a.x - b.x) + (double)(a.y - b.y) * (a.y - b.y));
}

int getfather(int x)
{
    if (x != p[x])
        p[x] = getfather(p[x]);
    return p[x];
}

void Union(int x, int y)
{
    x = getfather(x); y = getfather(y);
    if (rank[x] > rank[y])
    {
        p[y] = x;
    }
    else
    {
        p[x] = y;
        if (rank[x] == rank[y]) rank[y]++;
    }
}

double Kruskal()
{
    cnt = 0;
    double res = 0;
    int num = 0;
    int u, v;
    for (int i = 1; i <= N; i++)
    {
        p[i] = i;
        rank[i] = 0;
    }
    for (int i = 0; i < M; i++)
    {
        u = edge[i].u;
        v = edge[i].v;
        if (getfather(u) != getfather(v))
        {
            res += edge[i].w;
            ans[cnt++] = edge[i];
            num++;
            Union(u, v);
        }
        if (num > N - 1) break;
    }
    return res;
}

bool cmp(Edge a, Edge b)
{
    return a.w < b.w;
}

void dfs(int u, int flag)
{
    vis[u] = 1;
    if (!flag)
    {
        max1 = max(max1, (double)ps[u].p);
    }
    else max2 = max(max2, (double)ps[u].p);
    for (int i = Head[u]; i != -1; i = ans[i].next)
    if (!ans[i].can)
    {
        if (!vis[ans[i].v]) dfs(ans[i].v, flag);
    }
}

int main()
{
    freopen("in.txt", "r", stdin);
    int Test;
    scanf("%d", &Test);
    while (Test--)
    {
        scanf("%d", &N);
        for (int i = 1; i <= N; i++)
        {
            scanf("%d%d%d", &ps[i].x, &ps[i].y, &ps[i].p);
        }
        
        M = 0;
        memset(Head, -1, sizeof(Head));
        for (int i = 1; i < N; i++)
        for (int j = i + 1; j <= N; j++)
        {
            edge[M].u = i;
            edge[M].v = j;
            edge[M].w = dist(ps[i], ps[j]);
            edge[M].next = Head[i];
            Head[i] = M++; 
        }
        
        sort(edge, edge + M, cmp);
        double ret = 0;
        double Sum = Kruskal();
        max1 = 0, max2 = 0;
        for (int j = 0; j < N; j++)
        {
            ans[j].can = 1;
            memset(vis, 0, sizeof(vis));
            int i;
            for (i = 1; i <= N; i++)
            if (!vis[i])
            {
                dfs(i, 0);
                break;
            }
            for (; i <= N; i++)
            if (!vis[i])
            {
                dfs(i, 1);
                break;
            }
            double A = max1 + max2;
            double B = Sum - ans[j].w;
            ret = max(ret, A / B);
        }
        printf("%.2lf\n", ret);
    }
    return 0;
}
