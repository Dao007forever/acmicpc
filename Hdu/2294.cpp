#include <cstdio>
#include <cstring>

const long long mod = 1234567891;
int N, K;
struct Matrix {
	int n, m;
	long long mat[33][33];
}A, F, I;

void initF() {
	F.n = F.m = K + 1;
	for (int i = 0; i < F.n; i++)
		for (int j = 0; j < F.m; j++)
			F.mat[i][j] = 0;
}

void initI() {
	I.n = I.m = K + 1;
	for (int i = 0; i < I.n; i++)
		for (int j = 0; j < I.m; j++)
			I.mat[i][j] = 0;
	for (int i = 0; i < I.n; i++)
		I.mat[i][i] = 1;
}

void initA() {
	A.n = A.m = K + 1;
	for (int i = 0; i < A.n; i++)
		for (int j = 0; j < A.m; j++)
			A.mat[i][j] = 0;
	for (int i = 0; i < A.n; i++) {
		A.mat[i][i] = i;
		if (i < A.n - 1)
			A.mat[i][i + 1] = K - i;
	}
}

Matrix operator*(Matrix a, Matrix b) {
	Matrix c;
	c.n = a.n; c.m = b.m;
	for (int i = 0; i < c.n; i++)
		for (int j = 0; j < c.m; j++) {
			c.mat[i][j] = 0;
			for (int k = 0; k < a.m; k++)
				c.mat[i][j] = (c.mat[i][j] + a.mat[i][k] * b.mat[k][j]) % mod;
		}
	return c;
}

Matrix operator+(Matrix a, Matrix b) {
	Matrix c;
	c.n = a.n; c.m = b.m;
	for (int i = 0; i < c.n; i++)
		for (int j = 0; j < c.m; j++)
			c.mat[i][j] = (a.mat[i][j] + b.mat[i][j]) % mod;
	return c;
}

Matrix operator^(Matrix A, int x) {
	Matrix c;
	c.n = c.m = K + 1;
	c = I;
	for (; x; x >>= 1) {
		if (x & 1) c = c * A;
		A = A * A;
	}
	return c;
}

Matrix sum(int x) {
	if (x == 1) return A;
	Matrix c, tnow;
	memset(tnow.mat, 0, sizeof(tnow));
	memset(c.mat, 0, sizeof(c.mat));
	c.n = c.m = K + 1;
	tnow.n = tnow.m = K + 1;
	c = sum(x / 2);
	if (x & 1) {
		tnow = A ^ (x / 2 + 1);
		c = c + c * tnow;
		c = tnow + c;
	}
	else {
		tnow = A ^ (x / 2);
		c = c + c * tnow;
	}
	return c;
}

int main() {
	freopen("in.txt", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d%d", &N, &K);
		initF();
		initI();
		initA();
		F = I * A;
		Matrix tmp = sum(N - 1) + I;
		F = tmp * F;
		printf("%d\n", F.mat[0][K]);
	}
	return 0;
}
