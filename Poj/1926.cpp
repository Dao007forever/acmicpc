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

int N, M;
int adj[101][101], deg[101];
struct Matrix {
	int n, m;
	double mat[101][101];
}A, F, I;

void initI() {
	I.n = I.m = N;
	memset(I.mat, 0, sizeof(I.mat));
	for (int i = 0; i < N; i++)
		I.mat[i][i] = 1.0;
}

void initF() {
	F.n = F.m = N;
	memset(F.mat, 0, sizeof(F.mat));
	for (int i = 0; i < N; i++) {
		if (!deg[i]) continue;
		for (int j = 0; j < N; j++) {
			F.mat[i][j] = (double)adj[i][j] / deg[i];
		}
	}
}

Matrix operator*(Matrix a, Matrix b) {
	Matrix c;
	c.n = a.n; c.m = b.m;
	for (int i = 0; i < c.n; i++)
		for (int j = 0; j < c.m; j++) {
			c.mat[i][j] = 0;
			for (int k = 0; k < a.m; k++) {
				c.mat[i][j] += a.mat[i][k] * b.mat[k][j];
			}
		}
	return c;
}

Matrix operator^(Matrix T, int x) {
	Matrix c;
	c = I;
	for (; x; x >>= 1) {
		if (x & 1) c = c * T;
		T = T * T;
	}
	return c;
}

int main() {
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	while (Test--) {
		memset(adj, 0, sizeof(adj));
		memset(deg, 0, sizeof(deg));
		cin >> N >> M;
		A.n = 1, A.m = N;
		memset(A.mat, 0, sizeof(A.mat));
		for (int i = 0; i < N; i++) {
			double x;
			scanf("%lf", &x);
			A.mat[0][i] = x;
		}
		for (int i = 0; i < M; i++) {
			int u, v;
			cin >> u >> v;
			u--; v--;
			deg[u]++; deg[v]++;
			adj[u][v] = adj[v][u] = 1;
		}
		initF();
		initI();
		Matrix ret = A;
		int tmp = 1000000;
		ret = ret * (F ^ tmp);
		for (int i = 0; i < N; i++)
			if (deg[i]) {
				printf("%.3f\n", ret.mat[0][i]);
			} else {
				printf("%.3f\n", A.mat[0][i]);
			}
		puts("");
	}
	return 0;
}
