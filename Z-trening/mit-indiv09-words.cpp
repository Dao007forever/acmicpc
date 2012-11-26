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

struct Matrix {
        int n, m;
        LL mat[15][15];
}F, A, I;
struct BigInteger {
	int len;
	int a[222];

	bool isZero() {
		return (len == 0);
	}

	void div2() {
		int d = 0;
		for (int i = len; i >= 1; i--) {
			d = d * 10 + a[i];
			a[i] = d / 2;
			d %= 2;
		}
		for (; len > 1 && a[len] == 0; len--);
	}
}M;
int N;
int cost[30], f[30];

void initI()
{
	I.n = I.m = N;
	memset(I.mat, 0, sizeof(I.mat));
	for (int i = 0; i < N; i++)
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

int main()
{
	char st[222];
	scanf("%d %s", &N, st);
	M.len = strlen(st);
	for (int i = 1; i <= M.len; i++)
		M.a[i] = st[M.len - i] - '0';
	for (int i = 1; i <= N; i++)
		scanf("%d", &cost[i]);

	memset(f, 0, sizeof(f));
	f[0] = 1;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			if (i - cost[j] >= 0)
				f[i] += f[i - cost[j]];
	if (M.compare(N) <= 0) {
		int m = M.valueof()
	}
}
