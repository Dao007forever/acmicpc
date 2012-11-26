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

const int maxn = 1555;
const double PI = acos(-1.0);
double eps = 1e-15;
struct Point {
	double x, y, ang;
}ps[2 * maxn];
int N, M;
int x[maxn], y[maxn];

int sig(double d) 
{
	return (d > eps) - (d < -eps);
}

bool cmp(const Point &A, const Point &B)
{
	return A.ang < B.ang;
}

int main()
{
	freopen("in", "r", stdin);
	cin >> N;
	for (int i = 0; i < N; i++) {
		scanf("%d%d", &x[i], &y[i]);
	}

	int ret = 0;
	for (int i = 0; i < N; i++) {
		M = 0;
		for (int j = 0; j < N; j++) 
			if (i != j) {
				ps[M].x = x[j] - x[i];
				ps[M].y = y[j] - y[i];
				ps[M].ang = atan2(ps[M].y, ps[M].x);
				M++;
			}

		sort(ps, ps + M, cmp);

		for (int j = 0; j < M; j++) {
			ps[M + j] = ps[j];
			ps[M + j].ang = ps[j].ang + PI + PI;
		}

		for (int j = 0, l, r = 0; j < M; j++) {
			for (l = j; l < M && sig(ps[l].ang - ps[j].ang) == 0; l++);
			int cnt = 0;
			for (; r < 2 * M && sig(ps[r].ang - ps[j].ang - PI / 2) <= 0; r++)
				cnt += sig(ps[r].ang - ps[j].ang - PI / 2) == 0;
			ret += (l - j) * cnt;
			j = l - 1;
		}
	}
	printf("%d\n", ret);
}

