#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int L, M;
struct Matrix {
	int n, m;
	int mat[10][10];
}A, B, I;

void init() {
	I.n = I.m = 4;
	for (int i = 0; i < I.n; i++)
		I.mat[i][i] = 1;
}

Matrix operator*(Matrix a, Matrix b) {
	Matrix c;
	if (a.m != b.n) return c;
	for (int i = 0; i < a.n; i++)
		for (int j = 0; j < b.m; j++) {
			c.mat[i][j] = 0;
			for (int k = 0; k < a.m; k++)
				c.mat[i][j] = (c.mat[i][j] + a.mat[i][k] * b.mat[k][j]) % M;
		}
	c.n = a.n;
	c.m = b.m;
	return c;
}

Matrix operator^(Matrix A, int x) {
	Matrix c;
	c = I;
	for (; x; x >>= 1) {
		if (x & 1) c = c * A;
		A = A * A;
	}
	return c;
}

int main() {
	freopen("in.txt", "r", stdin);
	init();
	A.n = A.m = 4;
	A.mat[0][0] = A.mat[0][2] = A.mat[0][3] = 1;
	A.mat[1][0] = A.mat[2][1] = A.mat[3][2] = 1;
	B.n = 4;
	B.m = 1;
	B.mat[0][0] = 9;
	B.mat[1][0] = 6;
	B.mat[2][0] = 4;
	B.mat[3][0] = 2;
	while (scanf("%d%d", &L, &M) != EOF) {
		if (L < 5) {
			if (L == 0) printf("0\n");
			else printf("%d\n", B.mat[4 - L][0] % M);
			continue;
		}
		Matrix tmp = A^(L - 4);
		Matrix C = tmp * B;
		printf("%d\n", C.mat[0][0] % M);
	}
	return 0;
}
