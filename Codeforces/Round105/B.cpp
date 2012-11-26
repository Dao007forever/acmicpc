#include <cstdio>
#include <algorithm>
using namespace std;

const double eps = 1e-8;
int vp, vd, t, f, c;

int main() {
	freopen("in.txt", "r", stdin);
	scanf("%d%d%d%d%d", &vp, &vd, &t, &f, &c);
	if (vd <= vp) {
		printf("0\n");
		return 0;
	}
	double pp = vp * t;
	int ret = 0;
	while (1) {
		double t = pp / (vd - vp);
		pp += t * vp;
		if (pp + eps >= c) break;
		else ret++;
		pp += (t + f) * vp;
	}
	printf("%d\n", ret);
	return 0;
}
