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
struct Point
{
    int x, y, p;
}ps[MAXN];
int N;
int dis[MAXN];
double Map[MAXN][MAXN], dp[MAXN][MAXN];
int near[MAXN], use[MAXN];

double dist(Point a, Point b)
{
    return sqrt((double)(a.x - b.x) * (a.x - b.x) + (double)(a.y - b.y) * (a.y - b.y));
}

void Prim()
{
    for (int i = 1; i <= N; i++)
    {
        dis[i] = Map[1][i];
        near[i] = 1;
    }
    double B = 0;
    int A = 0;
    near[1] = -1;
    for (int i = 1; i < N; i++)
    {
        double Min = 1e99;
        int k = -1;
        for (int j = 1; j <= N; j++)
        if (near[j] != -1 && dis[j] < Min)
        {
            k = j;
            Min = dis[j];
        }
        int pre;
        if (k != -1)
        {
            pre = near[k];
            B += Map[k][near[k]];
            dp[near[k]][k] = dp[k][near[k]] = Map[k][near[k]];
            near[k] = -1;
            for (int j = 1; j <= N; j++)
            {
                if (near[j] != -1 && Map[k][j] < dis[j])
                {
                    dis[j] = Map[k][j];
                    near[j] = k;
                }
            }
        }
        for (int j = 1; j <= N; j++)
        {
            if (near[j] == -1 && j != k)
            {
                dp[j][k] = dp[k][j] = max(dp[j][pre], dp[pre][k]);
            }
        }
    }
    double ans = 0;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        if (i != j)
        {
            A = ps[i].p + ps[j].p;
            if ((double)A / (B - dp[i][j]) > ans)
                ans = (double)A / (B - dp[i][j]);
        }
    }
    printf("%.2lf\n", ans);
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
        for (int i = 1; i < N; i++)
        for (int j = i + 1; j <= N; j++)
            Map[i][j] = Map[j][i] = dist(ps[i], ps[j]), dp[i][j] = 0;
        Prim();
    }
    return 0;
}