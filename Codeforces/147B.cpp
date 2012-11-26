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

const int inf = 1 << 30;
struct Matrix {
	int mat[305][305];
}I, W;
int n;

void initI() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i == j) I.mat[i][j] = 0;
			else I.mat[i][j] = -inf;
}

Matrix operator * (Matrix a, Matrix b) {
	Matrix c;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			c.mat[i][j] = -inf;
			for (int k = 0; k < n; k++)
				c.mat[i][j] = max(c.mat[i][j], a.mat[i][k] + b.mat[k][j]);
		}
	return c;
}

Matrix operator ^ (Matrix A, int x) {
	Matrix c;
	c = I;
	for (; x; x >>= 1) {
		if (x & 1) c = c * A;
		A = A * A;
	}
	return c;
}

int main() {
	freopen("in", "r", stdin);
	int m;
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (i == j) W.mat[i][j] = 0;
			else W.mat[i][j] = -inf;
	while (m--) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		a--; b--;
		W.mat[a][b] = c;
		W.mat[b][a] = d;
	}
	
	int l = 2, r = n + 1, ret;
	while (l <= r) {
		int mid = (l + r) >> 1;
		int tmp = -inf;
		Matrix T = W ^ mid;
		for (int i = 0; i < n; i++)
			tmp = max(tmp, T.mat[i][i]);
		if (tmp > 0) {
			ret = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	printf("%d\n", ret > n ? 0 : ret);
	return 0;
}


