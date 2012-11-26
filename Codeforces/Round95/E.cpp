#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 1e5 + 50;
int n, m;
int d[4][2][maxn << 1], offset = maxn;
//int ver1[2][maxn], hor[2][maxn], 
//int dia1[2][maxn << 1], offset = maxn, dia2[2][maxn << 1];
int r[maxn], c[maxn];

int _max(int a, int b) {
	if (a == -1) return b;
	if (b == -1) return a;
	return a > b ? a : b;
}

int _min(int a, int b) {
	if (a == -1) return b;
	if (b == -1) return a;
	return a < b ? a : b;
}

int t[4], x[4], anw[10];
int main() {
	cin >> n >> m;
	memset(d, -1, sizeof(d));
	for (int i = 1; i <= m; i++) {
		cin >> r[i] >> c[i];
		d[0][0][r[i]] = _min(d[0][0][r[i]], c[i]);
		d[0][1][r[i]] = _max(d[0][1][r[i]], c[i]);
		d[1][0][c[i]] = _min(d[1][0][c[i]], r[i]);
		d[1][1][c[i]] = _max(d[1][1][c[i]], r[i]);
		d[2][0][r[i] - c[i] + offset] = _min(d[2][0][r[i] - c[i] + offset], r[i]);
		d[2][1][r[i] - c[i] + offset] = _max(d[2][1][r[i] - c[i] + offset], r[i]);
		d[3][0][r[i] + c[i]] = _min(d[3][0][r[i] + c[i]], r[i]);
		d[3][1][r[i] + c[i]] = _max(d[3][1][r[i] + c[i]], r[i]);
	}
	memset(anw ,0, sizeof(anw));
	for (int i = 1,t1, t2, t3, t4, cnt; i <= m; i++) {
		cnt = 0;
		t[0] = r[i]; t[1] = c[i];
		t[2] = r[i] - c[i] + offset; t[3] = r[i] + c[i];
		x[1] = x[2] = x[3] = r[i];
		x[0] = c[i];
		for (int i = 0; i < 4; i++) {
			if (x[i] < d[i][1][t[i]] && x[i] > d[i][0][t[i]])
				cnt += 2;
			else if (x[i] < d[i][1][t[i]] || x[i] > d[i][0][t[i]])
				cnt += 1;
		}
		anw[cnt]++;
	}
	for (int i = 0; i < 8; i++)
		cout << anw[i] << " ";
	cout << anw[8] << endl;
}
