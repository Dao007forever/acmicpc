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

const int MAXN = 100 + 10;
const double eps = 1e-6;
const double inf = 999999999.0;

int dblcmp(double d)
{
	return (d > eps) - (d < -eps);
}

struct KM
{
        double E[MAXN][MAXN];
		int n;
		double slack;
        bool map[MAXN][MAXN];
        bool visx[MAXN], visy[MAXN];
        int mate[MAXN];
		double lx[MAXN], ly[MAXN];

                void init(int n)
                {
                        this->n = n;
                        memset(E, 0, sizeof(E));
                }

                bool path(int x)
                {
                        visx[x] = true;
                        for (int y = 0; y < n; y++)
                        {
                                if (visy[y]) continue;
                                double t = lx[x] + ly[y] - E[x][y];
                                if (dblcmp(t) == 0)
                                {
                                        visy[y] = true;
                                        if (mate[y] == -1 || path(mate[y]))
                                        {
                                                mate[y] = x;
                                                return true;
                                        }
                                }
                                //else if (slack > t) slack = t;
                        }
                        return false;
                }

                void solve()
                {
                        memset(mate, -1, sizeof(mate));
						for (int i = 0; i < MAXN; i++)
						{
							lx[i] = -inf;
							ly[i] = 0;
						}
                        for (int x = 0; x < n; x++)
                                for (int y = 0; y < n; y++)
                                        if (E[x][y] > lx[x]) lx[x] = E[x][y];
                        for (int x = 0; x < n; x++)
                        {
                                while (1)
                                {
                                        memset(visx, 0, sizeof(visx));
                                        memset(visy, 0, sizeof(visy));
                                        slack = inf;
                                        if (path(x)) break;
										for (int i = 0; i < n; i++)
										if (visx[i])
											for (int j = 0; j < n; j++)
												if (!visy[j])
													slack = min(slack, lx[i] + ly[j] - E[i][j]);
                                        for (int i = 0; i < n; i++)
										{
                                                if (visx[i]) lx[i] -= slack;
                                                if (visy[i]) ly[i] += slack;
										}
                                }
                        }
                }
				void output()
				{
					for (int i = 0; i < n; i++)
						cout << mate[i] + 1 << endl;
				}
};

KM km;
int N;
struct Point
{
	double x, y;
}ant[MAXN], tree[MAXN];

double dist(Point a, Point b)
{
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return sqrt(dx * dx + dy * dy);
}

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%lf%lf", &ant[i].x, &ant[i].y);
	for (int i = 0; i < N; i++)
		scanf("%lf%lf", &tree[i].x, &tree[i].y);
	km.init(N);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			km.E[i][j] = -dist(tree[i], ant[j]);
	km.solve();
	km.output();
	return 0;
}
