/*
 * Author: Yang Zhang
 * Created Time: Tue 18 Sep 2012 09:38:53 PM CST
 * File Name: 6829_POLYNOM.cpp
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

const double eps = 1e-8;
int sig(double d) {
	return (d > eps) - (d < -eps);
}
double equ[5][6], res[5];
void Gauss(int n, int m) {
	for (int j = 0, i; j < m; j++) {	
		for (i = j; i < n && !sig(equ[i][j]); i++);	
		if (i == n) 
			break;	//continue
		if (i != j) 	
			for (int k = j; k <= m; k++)		
				swap(equ[i][k], equ[j][k]);
		for (i = j + 1; i < n; i++) if (sig(equ[i][j])) {	
			double mul = equ[i][j] / equ[j][j];
			for (int k = j; k <= m; k++)	
				equ[i][k] = equ[i][k] - equ[j][k] * mul; 
		}
	}
	res[n - 1] = 0.0;
	for (int i = n - 2; i >= 0; i--) {
		res[i] = equ[i][n];
		for (int j = n - 1; j > i; j--)
			res[i] -= equ[i][j] * res[j];
		res[i] /= equ[i][i];
	}
}
int main() {
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		int n;
		scanf("%d", &n);
		vector<double> x(n);
		for (int i = 0; i < n; i++)
			scanf("%lf", &x[i]);
		if (n <= 4) {
			puts("YES");
			continue;
		}
		equ[0][0] = equ[0][1] = equ[0][2] = equ[0][3] = 1.0; equ[0][4] = x[0];
		equ[1][0] = 8.0; equ[1][1] = 4.0; equ[1][2] = 2.0; equ[1][3] = 1.0; equ[1][4] = x[1];
		equ[2][0] = 27.0; equ[2][1] = 9.0; equ[2][2] = 3.0; equ[2][3] = 1.0; equ[2][4] = x[2];
		equ[3][0] = 64.0; equ[3][1] = 16.0; equ[3][2] = 4.0; equ[3][3] = 1.0; equ[3][4] = x[3];
		Gauss(4, 4);
	}
}

