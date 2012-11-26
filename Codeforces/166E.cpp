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
const LL mod = 1000000007LL;
struct Matrix {
        int n, m;
        LL mat[15][15];
}F, A, I;

//InitI can not be ignored!
void initI()
{
	I.n = I.m = 4;
	memset(I.mat, 0, sizeof(I.mat));
	for (int i = 0; i < 4; i++)
		I.mat[i][i] = 1;
}

void initA() {
	A.n = 1; A.m = 4;
	memset(A.mat, 0, sizeof(A.mat));
	A.mat[0][3] = 1;
}

void initF() {
	F.n = F.m = 4;
	memset(F.mat, 0, sizeof(F.mat));
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (i != j) F.mat[i][j] = 1;
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

int main() {
	initI();
	initF();
	initA();
	int n;
	cin >> n;
	Matrix ret = A;
	ret = ret * (F ^ n);
	cout << ret.mat[0][3] << endl;
}
