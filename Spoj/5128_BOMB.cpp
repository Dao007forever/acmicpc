#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct Circle {
	int x, y, r;
}b[11];
int w, l, n;
int e[11][11];
int vis[11];

bool isConnect(Circle A, Circle B) {
	int dx = A.x - B.x, dy = A.y - B.y, dr = A.r + B.r;
	if (dx * dx + dy * dy <= dr * dr) return true;
	return false;
}

void solve1() {
	int ret;
	if (w & 1) ret = w / 2 + 1;
	else ret = w / 2;
	printf("%d\n", ret);
}

int solve2() {
	int ret = 0;
	for (int i = 0; i < n; i++)
		if (vis[i] == 1) {
			for (int j = 0; j < n; j++)
				if (e[i][j]) ret = max(ret, b[j].x + b[j].r);
		}
	return w - ret;
}

int solve3() {
	int ret = w;
	for (int i = 0; i < n; i++)
		if (vis[i] == 2) {
			for (int j = 0; j < n; j++)
				if (e[i][j]) ret = min(ret, b[j].x - b[j].r);
		}
	return ret;
}

int dist(Circle A, Circle B) {
	double dx = (double)A.x - B.x, dy = (double)A.y - B.y;
	double d = sqrt(dx * dx + dy * dy) - (double)(A.r + B.r);
	d *= 0.5;
	int z = int(d + 1e-8);
	double rest = d - z;
	if (rest > 1e-6) return z + 1;
	return z;
}

int solve4() {
	int ret = 10000000;
	for (int i = 0; i < n; i++)
		if (vis[i] == 1)
			for (int j = 0; j < n; j++)
				if (vis[j] == 2) {
					for (int k = 0; k < n; k++)
						if (e[i][k])
							for (int l = 0; l < n; l++)
								if (e[j][l]) {
									int tmp = dist(b[k], b[l]);
									if (tmp > 0) ret = min(ret, tmp);
								}
				}
	return ret;
}

int main() {
	freopen("in.txt", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d%d%d", &w, &l, &n);
		for (int i = 0; i < n; i++)
			scanf("%d%d%d", &b[i].x, &b[i].y, &b[i].r);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (i != j) e[i][j] = isConnect(b[i], b[j]);
				else e[i][j] = 1;
		for (int k = 0; k < n; k++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					if (i != j && i != k && j != k)
						e[i][j] = e[i][j] || (e[i][k] && e[k][j]);
		memset(vis, 0, sizeof(vis));
		int flag1 = 0, flag2 = 0;
		for (int i = 0; i < n; i++) {
			if (b[i].x - b[i].r <=0 ) {
				flag1 = 1;
				vis[i] = 1;
			}
			if (b[i].x + b[i].r >= w) {
				flag2 = 1;
				vis[i] = 2;
			}
		}
		if (!flag1 && !flag2) solve1();
		else {
			int r1 = 1000000, r2 = 1000000, r3 = 1000000;
			if (flag1) r1 = solve2();
			if (r1 & 1) r1 = r1 / 2 + 1;
			else r1 /= 2;
			if (flag2) r2 = solve3();
			if (r2 & 1) r2 = r2 / 2 + 1;
			else r2 /= 2;
			if (flag1 && flag2) r3 = solve4();
			int ret = min(min(r1, r2), r3);
			printf("%d\n", ret);
		}
	}
	return 0;
}
