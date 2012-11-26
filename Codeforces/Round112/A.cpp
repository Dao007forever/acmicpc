#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

int x[222], y[222];
int N;

int main()
{
	freopen("in.txt", "r", stdin);
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> x[i] >> y[i];
	int ret = 0;
	for (int i = 0; i < N; i++) {
		int a = 0, b = 0, c = 0, d = 0;
		for (int j = 0; j < N; j++) {
			if (x[j] > x[i] && y[j] == y[i]) a++;
			if (x[j] < x[i] && y[j] == y[i]) b++;
			if (x[j] == x[i] && y[j] < y[i]) c++;
			if (x[j] == x[i] && y[j] > y[i]) d++;
		}
		if (a && b && c && d) ret++;
	}
	cout << ret << endl;
	return 0;
}
