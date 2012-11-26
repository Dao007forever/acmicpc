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
#define sqr(x) ((x) * (x))
typedef long long LL;

const double PI = acos(-1.0);
const double eps = 1e-3;
int sig(double d) {
	return (d > eps) - (d < -eps);
}
struct Matrix {
	double mat[4][4];

	void init_E() {
		memset(mat, 0, sizeof(mat));
		for (int i = 0; i < 4; i++)
			mat[i][i] = 1.0;
	}

	void clear() {
		memset(mat, 0, sizeof(mat));
	}

	void transose() {
		for (int i = 0; i < 4; i++)
			for (int j = i + 1; j < 4; j++) {
				swap(mat[i][j], mat[j][i]);
			}
	}
};

Matrix operator*(const Matrix &a, const Matrix &b) {
	Matrix c;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++) {
			c.mat[i][j] = 0;
			for (int k = 0; k < 4; k++) 
				c.mat[i][j] += a.mat[i][k] * b.mat[k][j];
		}
	return c;
}

Matrix operator^(Matrix A, LL x) {
	Matrix c;
	c.init_E();
	for (; x; x >>= 1) {
		if (x & 1) c = c * A;
		A = A * A;
	}
	return c;
}

void getRoate(Matrix &A, double u, double v, double w, double ang) {
	ang = ang / 180 * PI;
	memset(A.mat, 0, sizeof(A.mat));
	double len = sqrt(sqr(u) + sqr(v) + sqr(w));
	u /= len; v /= len; w /= len;
	A.mat[0][0] = sqr(u) + (1 - sqr(u)) * cos(ang);
	A.mat[0][1] = u * v * (1 - cos(ang)) - w * sin(ang);
	A.mat[0][2] = u * w * (1 - cos(ang)) + v * sin(ang);

	A.mat[1][0] = u * v * (1 - cos(ang)) + w * sin(ang);
	A.mat[1][1] = sqr(v) + (1 - sqr(v)) * cos(ang);
	A.mat[1][2] = v * w * (1 - cos(ang)) - u * sin(ang);

	A.mat[2][0] = u * w * (1 - cos(ang)) - v * sin(ang);
	A.mat[2][1] = v * w * (1 - cos(ang)) + u * sin(ang);
	A.mat[2][2] = sqr(w) + (1 - sqr(w)) * cos(ang);

	A.mat[3][3] = 1.0;
}

int repeat[55555];
Matrix M[55555];
int main(int argc, char const *argv[])
{
	int n;
	while (cin >> n && n) {
		string op;
		M[0].init_E();
		int top = 0;
		while (cin >> op) {
			if (op == "end") {
				if (top == 0) break;
				else {
					M[top - 1] = M[top - 1] * (M[top] ^ repeat[top]);
					top--;
				}
			}
			if (op == "rotate") {
				double x, y, z, ang;
				scanf("%lf%lf%lf%lf", &x, &y, &z, &ang);
				Matrix tmp;
				getRoate(tmp, x, y, z, ang);
				tmp.transose();
				M[top] = M[top] * tmp;
			}
			if (op == "repeat") {
				top++;
				scanf("%d", &repeat[top]);
				M[top].init_E();
			}
			if (op == "translate") {
				double x, y, z;
				scanf("%lf%lf%lf", &x, &y, &z);
				Matrix tmp;
				tmp.init_E();
				tmp.mat[0][3] = x; tmp.mat[1][3] = y; tmp.mat[2][3] = z;
				tmp.transose();
				M[top] = M[top] * tmp;
			}
			if (op == "scale") {
				double x, y, z;
				scanf("%lf%lf%lf", &x, &y, &z);
				Matrix tmp;
				tmp.init_E();
				tmp.mat[0][0] = x; tmp.mat[1][1] = y; tmp.mat[2][2] = z;
				tmp.transose();
				M[top] = M[top] * tmp;
			}
		}
		//M[0].transose();
		for (int i = 0; i < n; i++) {
			Matrix input;
			memset(input.mat, 0, sizeof(input.mat));
			scanf("%lf%lf%lf", &input.mat[0][0], &input.mat[0][1], &input.mat[0][2]);
			input.mat[0][3] = 1.0;
			Matrix ret;
			for (int i = 0; i < 1; i++)
				for (int j = 0; j < 4; j++) {
					ret.mat[i][j] = 0;
					for (int k = 0; k < 4; k++)
						ret.mat[i][j] += input.mat[i][k] * M[0].mat[k][j];
				}
			for (int i = 0; i < 4; i++)
				if (sig(ret.mat[0][i]) == 0) ret.mat[0][i] = 0.0;
			printf("%.2f %.2f %.2f\n", ret.mat[0][0], ret.mat[0][1], ret.mat[0][2]);
		}
		puts("");
	}
	return 0;
}