#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define sqr(x) ((x) * (x))

const int MAXN = 100 + 10;
int N;
double x[MAXN], y[MAXN], z[MAXN];

int main()
{
	freopen("a", "r", stdin);
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%lf%lf%lf", &x[i], &y[i], &z[i]);

	double d = 1;
	double ansx = 0, ansy = 0, ansz = 0;
	for (int i = 0; i < 200000; i++)
	{
		double tmp = -1;
		int id = 0;
		for (int j = 0; j < N; j++)
		{
			double dis = sqr(x[j] - ansx) + sqr(y[j] - ansy) + sqr(z[j] - ansz);
			if (dis > tmp)
			{
				tmp = dis;
				id = j;
			}
		}
		ansx += (x[id] - ansx) * d;
		ansy += (y[id] - ansy) * d;
		ansz += (z[id] - ansz) * d;
		d *= 0.999;
	}
	printf("%.10f %.10f %.10f\n", ansx, ansy, ansz);
	return 0;
}
