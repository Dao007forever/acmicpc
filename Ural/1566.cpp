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

const double eps = 1e-8;
int sig(double d) {
	return (d > eps) - (d < -eps);
}
struct Triangle {
	double l[3];

	void input() {
		cin >> l[0] >> l[1] >> l[2];
	}
}A, B;
struct node {
	double a, b, c;
}T, P;

double area(node A) {
	double r = (A.a + A.b + A.c) / 2;
	return sqrt(r * (r - A.a) * (r - A.b) * (r - A.c));
}

bool check(int u, int v, int w) {
	T.a = A.l[u]; T.b = A.l[(u + 1) % 3]; T.c = A.l[(u + 2) % 3];
	P.a = B.l[v]; P.b = B.l[(v + 1) % 3]; P.c = B.l[(v + 2) % 3];
	if (w) {
		swap(P.b, P.c);
	}

	double sT = area(T), sP = area(P);
	double BC = T.a, YZ = P.a;
	double AP = 2.0 * sT / T.a, XQ = 2.0 * sP / P.a;
	double BP, PC, YQ, QZ;
	if (T.b * T.b - AP * AP < eps) BP = 0.0;
	else BP = sqrt(T.b * T.b - AP * AP);
	if (T.c * T.c - AP * AP < eps) PC = 0.0;
	else PC = sqrt(T.c * T.c - AP * AP);
	if (P.b * P.b - XQ * XQ < eps) YQ = 0.0;
	else YQ = sqrt(P.b * P.b - XQ * XQ);
	if (P.c * P.c - XQ * XQ < eps) QZ = 0.0;
	else QZ = sqrt(P.c * P.c - XQ * XQ);

	if (sig(BP + PC - BC) > 0) {
		if (sig(T.b < T.c) < 0) BP = -BP;
		else PC = -PC;
	}

	if (sig(YQ + QZ - YZ) > 0) {
		if (sig(P.b - P.c) < 0) YQ = -YQ;
		else QZ = -QZ;
	}

	if (sig(YZ - BC) > 0) return false;

	//Case1
	double angT = (T.a * T.a + T.b * T.b - T.c * T.c) / (2 * T.a * T.b);
	double angP = (P.a * P.a + P.b * P.b - P.c * P.c) / (2 * P.a * P.b);
	if (sig(angT - angP) <= 0 && sig(BP - YQ) >= 0) 
		return true;

	//Case3
	double tmp = XQ / AP * BP + QZ;
	if (sig(AP - XQ) >= 0 && sig(angT - angP) >= 0 && sig(tmp - BC) <= 0)
		return true;

	// Case2
	angT = (T.a * T.a + T.c * T.c - T.b * T.b) / (2 * T.a * T.c);
	angP = (P.a * P.a + P.c * P.c - P.b * P.b) / (2 * P.a * P.c);
	if (sig(angT - angP) <= 0 && sig(PC - QZ) >= 0) 
		return true;

	//Case4
	tmp = XQ / AP * PC + YQ;
	if (sig(AP - XQ) >= 0 && sig(angT - angP) >= 0 && sig(tmp - BC) <= 0)
		return true;
}

int main() {
//	freopen("in", "r", stdin);
	A.input();
	B.input();
	bool flag = false;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			if (check(i, j, 0)) {
				flag = true;
				break;
			}
			if (check(i, j, 1)) {
				flag = true;
				break;
			}
		}
	if (flag) puts("YES");
	else puts("NO");
	return 0;
}
