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

typedef long long LL;
const LL mod = 321555123LL;
struct Matrix {
        int n, m;
        LL mat[55][55];
}F, A, I;
LL N;
int K;

//InitI can not be ignored!
void initI()
{
	I.n = I.m = 2 * K + 1;
	memset(I.mat, 0, sizeof(I.mat));
	for (int i = 0; i < 2 * K + 1; i++)
		I.mat[i][i] = 1;
}

void initA()
{
	A.n = 1; A.m = 2 * K + 1;
	memset(A.mat, 0, sizeof(A.mat));
	A.mat[0][K] = 1;
}

void initF()
{
	F.n = F.m = 2 * K + 1;
	memset(F.mat, 0, sizeof(F.mat));
	for (int i = 0; i < 2 * K + 1; i++) {
		F.mat[i][i] = 1;
		if (i - 1 >= 0) F.mat[i - 1][i] = 1;
		if (i + 1 < 2 * K + 1) F.mat[i + 1][i] = 1;
	}
}

Matrix operator + (Matrix a, Matrix b) {
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

int main()
{
	cin >> N >> K;
	initI();
	initA();
	initF();
	Matrix ret = A;
	ret = ret * (F ^ N);
	/*for (int i = 0; i < N; i++) {
		ret = ret * F;
	}*/
	LL ans = 0;
	for (int i = 0; i < 2 * K + 1; i++) {
		ans += ret.mat[0][i];
		ans %= mod;
	}
	cout << ans << endl;
	return 0;
}
