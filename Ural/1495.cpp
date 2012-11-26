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

#define MAXN 1000005
int N;
int power[31], now = 0;
int f[2][MAXN];
bool a[2][MAXN] = {false};

int main()
{
	cin >> N;
	memset(f, 64, sizeof(f));
	a[0][1 % N] = a[0][2 % N] = true;
	f[0][1 % N] = 0 % N;
	f[0][2 % N] = 1 % N;
	power[0] = 1 % N;
	for (int i = 1; i <= 30; i++)
		power[i] = (power[i - 1] * 10) % N;
	for (int i = 1; i <= 30; i++) {
		if (a[now][0]) {
			for (int j = i - 1; j >= 0; j--)
				cout << (f[now][0] >> j & 1) + 1;
			cout << endl;
			return 0;
		}
		if (i == 30) break;
		now ^= 1;
		memset(a[now], false, sizeof(a[now]));
		memset(f[now], 64, sizeof(f[now]));
		for (int j = 0; j < N; j++)
			if (a[now ^ 1][j]) {
				int x = (j + power[i]) % N, y = (j + (power[i] << 1)) % N;
				int p = f[now ^ 1][j], q = f[now ^ 1][j] ^ (1 << i);
				a[now][x] = a[now][y] = true;
				if (p < f[now][x])
					f[now][x] = p;
				if (q < f[now][y])
					f[now][y] = q;
			}
	}
	cout << "Impossible" << endl;
	return 0;
}
