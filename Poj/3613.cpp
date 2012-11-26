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
#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

const int inf = 0x3f3f3f3f;
struct Matrix {
	int n, m;
	LL mat[205][205];
}F, A, I;

Matrix operator*(Matrix a, Matrix b) {
	Matrix c;
	c.n = a.n; c.m = b.m;
	for (int i = 0; i < a.n; i++)
		for (int j = 0; j < b.m; j++) {
			c.mat[i][j] = inf;
			for (int k = 0; k < a.m; k++) {
				if (a.mat[i][k] == inf) continue;
				if (b.mat[k][j] == inf) continue;
				c.mat[i][j] = min(c.mat[i][j], a.mat[i][k] + b.mat[k][j]);
			}
		}
	return c;
}

void output(Matrix x) {
	for (int i = 0; i < x.n; ++i) {
		for (int j = 0; j < x.m; ++j)
			cout << x.mat[i][j] << " ";
		cout << endl;
	}
}

//Quickpow
Matrix operator^(Matrix A, LL x) {
	Matrix c;
	c = A;
	x--;
	for (; x; x >>= 1) {
		if (x & 1) {
			c = c * A;
		}
		A = A * A;
	}
	return c;
}

int main() {
	freopen("in", "r", stdin);
	int N, T, S, E;
	vector<int> mp(1001, -1);
	cin >> N >> T >> S >> E;
	int cnt = 0;
	for (int i = 0; i < T; ++i) {
		int a, b, c;
		scanf("%d%d%d", &c, &a, &b);
		if (mp[a] == -1) mp[a] = cnt++;
		if (mp[b] == -1) mp[b] = cnt++;
		F.mat[mp[a]][mp[b]] = F.mat[mp[b]][mp[a]] = c;
	}
	F.n = F.m = cnt;
	for (int i = 0; i < F.n; ++i)
		for (int j = 0; j < F.m; ++j)
			if (F.mat[i][j] == 0)
				F.mat[i][j] = inf;
	Matrix ret = F ^ N;
	printf("%d\n", ret.mat[mp[S]][mp[E]]);
	return 0;
}