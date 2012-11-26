/*
 * 矩阵乘法
 */
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
const LL mod = 10000LL;
struct Matrix {
        int n, m;
        LL mat[5][5];
}F, A, I;
int N, a[5];
int AA, BB, CC;

//InitI can not be ignored!
void initI()
{
	I.n = I.m = 3;
	memset(I.mat, 0, sizeof(I.mat));
	for (int i = 0; i < 3; i++)
		I.mat[i][i] = 1;
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

void initA()
{
	A.n = 1, A.m = 3;
	memset(A.mat, 0, sizeof(A.mat));
	for (int i = 0; i < 3; i++)
		A.mat[0][i] = a[i];
}

void initF()
{
	F.n = F.m = 3;
	memset(F.mat, 0, sizeof(F.mat));
	F.mat[1][0] = F.mat[2][1] = 1;
	F.mat[0][2] = CC;
	F.mat[1][2] = BB;
	F.mat[2][2] = AA;
}

int main()
{
	cin >> a[0] >> a[1] >> a[2];
	cin >> CC >> BB >> AA;
	cin >> N;
	if (N <= 3) {
		cout << a[N - 1] << endl;
		return 0;
	}
	initI();
	initA();
	initF();
	N -= 3;
	Matrix ret = A;
	ret = ret * (F ^ N);
	cout << ret.mat[0][2] << endl;
	return 0;
}
