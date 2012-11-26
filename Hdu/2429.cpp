#pragma comment(linker, "/STACK:1024000000,1024000000") 
/*
 * Author: Yang Zhang
 * Created Time: Sat 18 Aug 2012 10:09:05 AM UTC
 * File Name: 2429.cpp
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

const int mod = 10001;
int n;
char st[33][11];
map<string, int> mp;
struct Matrix {
        int n, m;
        int mat[33][33];
}F, A, I;

//InitI can not be ignored!
void initI() {
	I.n = I.m = n;
	memset(I.mat, 0, sizeof(I.mat));
	for (int i = 0; i < n; i++)
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
Matrix operator^(Matrix T, int x) {
        Matrix c;
        c = I;
        for (; x; x >>= 1) {
                if (x & 1) c = c * T;
                T = T * T;
        }
        return c;
}

//Calculating F+F^2+...+F^x
Matrix Sum(int x) {
    if (x == 1) return F;
    if (x & 1) return (F ^ x) + Sum(x - 1);
    else return Sum(x / 2) * ((F ^ (x / 2)) + I);
}

void initF() {
	F.n = F.m = n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			int li = strlen(st[i]), lj = strlen(st[j]);
			if (st[i][li - 1] == st[j][0])
				F.mat[i][j] = 1;
			else F.mat[i][j] = 0;
		}
}

int main() {
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		mp.clear();
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%s", st[i]);
			mp[st[i]] = i;
		}
		initI();
		initF();
		char start[11], end[11];
		scanf("%s", start);
		scanf("%s", end);
		int st = mp[start], ed = mp[end], k;
		scanf("%d", &k);
		if (!(k & 1)) k--;
		A.n = 1;
		A.m = n;
		memset(A.mat, 0, sizeof(A.mat));
		A.mat[0][st] = 1;
		Matrix tmp = F;
		F = F * F;
		Matrix ret;
		if (k == 1) {
			ret = A * F;	
		} else {
			ret = tmp + tmp * Sum((k - 1) / 2);
			ret = A * ret;
		}
		printf("%d\n", ret.mat[0][ed]);
	}
	return 0;
}

