#include <cstdio>

const int maxn = 1005;
bool vis[maxn][maxn];
double p[maxn][maxn];

double F(int W, int B) {
	if (W <= 0) return 0.0;
	if (B <= 0) return 1.0;
	if (W == 1 && B == 1) return 0.5;

	if (vis[W][B]) return p[W][B];
	vis[W][B] = 1;

	double w = W;
	double b = B;
	double ret = w / (w + b);
	double oth = 1 - ret;
	oth = oth * ((b - 1) / (b + w - 1));
	oth = oth * ( (w) * F(W - 1, B - 2) / (b + w - 2) + (b - 2) * F(W, B - 3) / (b + w - 2));
	return p[W][B] = ret + oth;
}

int main() {
	freopen("in.txt", "r", stdin);
	int w, b;
	scanf("%d%d", &w, &b);
	printf("%.9f\n", F(w, b));
	return 0;
}
