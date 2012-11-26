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

const double PI = acos(-1.0);
double A;
int N;

int main()
{
	freopen("a", "r", stdin);
	int cas = 1;
	while (scanf("%d%lf", &N, &A) && N >= 3)
	{
		printf("Case %d: ", cas++);
		double x = 1.0 * sin(PI / 6);
		double area = A / N, ang = 2.0 * PI / N;
		double r1 = sqrt(2 * area / sin(ang));
		double r2 = r1 * cos(0.5 * ang);
		double s1 = PI * r1 * r1, s2 = PI * r2 * r2;
		printf("%.5lf %.5lf\n", s1 - A, A - s2);
	}
	return 0;
}
