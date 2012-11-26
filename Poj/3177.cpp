#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int MAXN = 5000 + 10;
const int MAXM = 10000 + 10;
struct Edge
{
        int v, next;
}edge[MAXM * 5];
int N, M;
int Head[MAXN];
int low[MAXN], dfn[MAXN], Index, Top, size;
int vis[MAXM], deg[MAXN], Stack[MAXN], id[MAXN];

void AddEdge(int u, int v, int num)
{
        edge[num].v = v; edge[num].next = Head[u]; Head[u] = num;
}

void Tarjan(int u)
{
        low[u] = dfn[u] = ++Index;
        Stack[++Top] = u;
        for (int i = Head[u]; i != -1; i = edge[i].next)
        if (!vis[i])
        {
                vis[i] = vis[i ^ 1] = 1;
                if (!dfn[edge[i].v])
                {
                        Tarjan(edge[i].v);
                        low[u] = min(low[u], low[edge[i].v]);
                }
                else low[u] = min(low[u], dfn[edge[i].v]);
        }
        if (low[u] == dfn[u])
        {
                size++;
                for (;Stack[Top + 1] != u; --Top)
                        id[Stack[Top]] = size;
        }
}

int main()
{
      freopen("in", "r", stdin);
        while (scanf("%d%d", &N, &M) != EOF)
        {
                memset(dfn, 0, sizeof(dfn));
                memset(low, 0, sizeof(low));
                memset(Head, -1, sizeof(Head));
                Index = 0;
                Top = 0;
                size = 0;
                for (int i = 0; i <= 2 * M + 2; i++)
                {
                        edge[i].v = 0;
                        edge[i].next = -1;
                }
                for (int i = 0; i < M; i++)
                {
                        int u, v;
                        scanf("%d%d", &u, &v);
                        int m1 = 2 * i, m2 = m1 ^ 1;//m2为m1反向的边
                        AddEdge(u, v, m1);
                        AddEdge(v, u, m2);
                }
                for (int i = 1; i <= N; i++)
                if (!dfn[i])
                        Tarjan(i);
                for (int u = 1; u <= N; u++)
                for (int i = Head[u]; i != -1; i = edge[i].next)
                if (id[u] != id[edge[i].v])
                        deg[id[edge[i].v]]++;
                int res = 0;
                for (int i = 1; i <= size; i++)
                if (deg[i] == 1)
                        res++;
                printf("%d\n", (res + 1) / 2);
        }
        return 0;
}
