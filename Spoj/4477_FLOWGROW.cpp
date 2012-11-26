#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int maxn = 8;
const LL mod = 2370823708LL;
struct Matrix {
	int n, m;
	unsigned int mat[maxn][maxn];
}F, A, I;
LL n, m;
int k;

//初始化单位矩阵
void initI() {
	I.n = I.m = 8;
	for (int i = 0; i < maxn; i++)
		I.mat[i][i] = 1;
}

void initF() {
	F.n = F.m = 8;
	for (int i = 0; i < F.n; i++)
		F.mat[i][i] = 1;
	for (int i = 1; i < F.n; i++)
		F.mat[i][i - 1] = 8 - i;
}

void initA() {
	A.n = 8; A.m = 1;
	A.mat[0][0] = 1;
}

Matrix operator*(Matrix a, Matrix b) {
	Matrix c;
	c.n = a.n; c.m = b.m;
	for (int i = 0; i < a.n; i++)
		for (int j = 0; j < b.m; j++) {
			c.mat[i][j] = 0;
			for (int k = 0; k < a.n; k++) 
				c.mat[i][j] = ((unsigned long long)c.mat[i][j] + (unsigned long long)a.mat[i][k] * b.mat[k][j]) % mod;
		}
	return c;
}

//矩阵快速幂
Matrix operator^(Matrix A, LL x) {
	Matrix c;
	c = I;
	for (; x; x >>= 1) {
		if (x & 1) c = c * A;
		A = A * A;
	}
	return c;
}

unsigned int quickpow(unsigned int a, LL x) {
	unsigned int c = 1;
	for (; x; x >>= 1) {
		if (x & 1) c = ((unsigned long long)c * a) % mod;
		a = ((unsigned long long)a * a) % mod;
	}
	return c;
}

int main() {
	initI();
	initF();
	initA();
	while (cin >> m >> n >> k) {
		Matrix Fn;
		Fn = (F ^ n) * A;
		unsigned int ret = 0;
		for (int i = k; i < 8; i++) {
			ret += Fn.mat[i][0];
			ret %= mod;
		}
		ret = quickpow(ret, m);
		cout << ret << endl;
	}
	return 0;
}
