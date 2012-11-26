/*
 * Author: Yang Zhang
 * Created Time: Sun 02 Sep 2012 02:56:27 PM CST
 * File Name: 10082_CMPANS.cpp
 */
#include <ctime>
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

#define MAXN 1005
int n;
int A[MAXN][MAXN], B[MAXN][MAXN];
LL d[MAXN], e[MAXN], f[MAXN], x[MAXN];

bool check() {
	srand(A[0][0]);
	for (int i = 0; i < n; i++)
		x[i] = rand() % 1000;
	for (int i = 0; i < n; i++) {
		d[i] = f[i] = 0;
		for (int j = 0; j < n; j++) {
			d[i] += x[j] * A[i][j];
			f[i] += x[j] * B[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		e[i] = 0;
		for (int j = 0; j < n; j++) {
			e[i] += d[j] * A[i][j];
		}
	}
	for (int i = 0; i < n; i++)
		if (e[i] != f[i]) return false;
	return true;
}

int main() {
	for (; scanf("%d", &n) && n; ) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				scanf("%d", &A[i][j]);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				scanf("%d", &B[i][j]);
		bool flag = true;
		for (int i = 0; i < 10; i++)
			if (!check()) {
				puts("NO");
				flag = false;
				break;
			}
		if (flag) puts("YES");
	}
	return 0;
}

