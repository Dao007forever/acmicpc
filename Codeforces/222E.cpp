/*
 * Author: Yang Zhang
 * Created Time: Thu 13 Sep 2012 02:36:14 PM CST
 * File Name: 222E.cpp
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
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

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

int change(char c) {
	if (c >= 'a' && c <= 'z') return c - 'a';
	return c - 'A' + 26;
}

int main() {
	cin >> n >> m >> k;
	initI();
	F.n = F.m = m;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < m; j++)
			F.mat[i][j] = 1;
	while (k--) {
		string s;
		cin >> s;
		int a = change(s[0]), b = change(s[1]);
		F.mat[a][b] = 0;
	}
	A.n = 1; A.m = m;
	for (int i = 0; i < m; i++)
		A.mat[0][i] = 1;
	Matrix tmp =  (F ^ (n - 1));
	A = A * tmp;
	LL ret = 0;
	for (int i = 0; i < m; i++)
		ret = (ret + A.mat[0][i]) % mod;
	cout << ret << endl;
	return 0;
}

