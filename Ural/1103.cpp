#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 5005;
const double eps = 1e-8;
struct Point {
	double x, y, ang;
}P[maxn], other[maxn];
int n, top;
Point Stack[maxn];

int dblcmp(double d) {
	return (d > eps) - (d < -eps);
}

double cross_product(Point o, Point a, Point b) {
	return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

bool cmp(Point a, Point b)
{
    return dblcmp(cross_product(P[0], a, b)) < 0;
}

bool cmpang(Point a, Point b) {
	return dblcmp(a.ang - b.ang) < 0;
}

void Graham(int n)
{
        int tmp = 0;
        for (int i = 1; i < n; i++)
        if (dblcmp(P[i].x - P[tmp].x) < 0 || (dblcmp(P[i].x - P[tmp].x) == 0 && dblcmp(P[i].y - P[tmp].y) < 0))
                tmp = i;
        swap(P[0], P[tmp]);
        sort(P + 1, P + n, cmp);
        Stack[0] = P[0]; Stack[1] = P[1];
        top = 1;
        for (int i = 2; i < n; i++)
        {
                while (dblcmp(cross_product(Stack[top], Stack[top - 1], P[i])) < 0 && top >= 1)
                        top--;
                Stack[++top] = P[i];
        }
}

double len(double x, double y) {
	return sqrt(x * x + y * y);
}

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d", &n);
	top = 0;
	for (int i = 0; i < n; i++)
		scanf("%lf %lf", &P[i].x, &P[i].y);
	Graham(n);

	int M = 0;
	for (int i = 0; i < n; i++) {
		if (dblcmp(Stack[0].x - P[i].x) == 0 && dblcmp(Stack[0].y - P[i].y) == 0) continue;
		if (dblcmp(Stack[1].x - P[i].x) == 0 && dblcmp(Stack[1].y - P[i].y) == 0) continue;
		double x1, x2, y1, y2;
		x1 = P[i].x - Stack[0].x;
		x2 = P[i].x - Stack[1].x;
		y1 = P[i].y - Stack[0].y;
		y2 = P[i].y - Stack[1].y;
		other[M] = P[i];
		other[M].ang = (x1 * x2 + y1 * y2) / (len(x1, y1) * len(x2, y2));
		M++;
	}
	sort(other + 0, other + M, cmpang);
	printf("%.0lf %.0lf\n", Stack[0].x, Stack[0].y);
	printf("%.0lf %.0lf\n", Stack[1].x, Stack[1].y);
	printf("%.0lf %.0lf\n", other[M / 2].x, other[M / 2].y);
	return 0;
}
