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

int N, A, B;
unsigned long long f[21][21][21], ret;

int main() {
	cin >> N >> A >> B;
	memset(f, 0, sizeof(f));
	f[0][0][0] = 1;
	for (int i = 1; i <= N; i++)
		for (int j = 0; j <= A; j++)
			for (int k = 0; k <= B; k++) {
				f[i][j][k] = f[i - 1][j][k];
				if (j) f[i][j][k] += f[i][j - 1][k];
				if (k) f[i][j][k] += f[i][j][k - 1];
				if (j && k) f[i][j][k] -= f[i][j - 1][k - 1];
			}
	ret = 0;
	for (int i = 0; i <= A; i++)
		for (int j = 0; j <= B; j++)
			ret += f[N][i][j];
	cout << ret << endl;
	return 0;
}
