const LL mod = 1000000007ll;
struct Matrix {
	int n, m;
	LL mat[55][55];
}F, A, I;
LL n, m, k;

//InitI can not be ignored!
void initI()
{
	I.n = I.m = m;
	memset(I.mat, 0, sizeof(I.mat));
	for (int i = 0; i < m; i++)
		I.mat[i][i] = 1;
}

Matrix operator+(Matrix a, Matrix b) {
	Matrix c;
	c.n = a.n; c.m = a.m;
	for (int i = 0; i < a.n; i++)
		for (int j = 0; j < a.m; j++) {
			c.mat[i][j] = (a.mat[i][j] + b.mat[i][j]) % mod;
		}
	return c;
}

Matrix operator*(Matrix a, Matrix b) {
	Matrix c;
	c.n = a.n; c.m = b.m;
	for (int i = 0; i < a.n; i++)
		for (int j = 0; j < b.m; j++) {
			c.mat[i][j] = 0;
			for (int k = 0; k < a.m; k++) 
				c.mat[i][j] = (c.mat[i][j] + a.mat[i][k] * b.mat[k][j]) % mod;
		}
	return c;
}

//Quickpow
Matrix operator^(Matrix A, LL x) {
	Matrix c;
	c = I;
	for (; x; x >>= 1) {
		if (x & 1) c = c * A;
		A = A * A;
	}
	return c;
}

//Calculating F+F^2+...+F^x
Matrix Sum(int x) {
    if (x == 1) return F;
    if (x & 1) return (F ^ x) + Sum(x - 1);
    else return Sum(x / 2) * ((F ^ (x / 2)) + I);
}
