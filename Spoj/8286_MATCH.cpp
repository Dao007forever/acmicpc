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

const int mod = 2;
int n;
int mat[333][333];

int Determinant() {
	int ret = 1;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (mat[j][i]) {
				for (int k = i; k < n; k++)
					swap(mat[i][k], mat[j][k]);
				ret = -ret;
				break;
			}
		}

		for (int j = i + 1; j < n; j++) {
			while (mat[j][i]) {
				int t = mat[i][i] / mat[j][i];
				for (int k = i; k < n; k++) {
					mat[i][k] -= t * mat[j][k];
					mat[i][k] %= 2;
					swap(mat[i][k], mat[j][k]);
				}
				ret = -ret;
			}
		}

		ret *= mat[i][i];
		ret %= 2;
		if (!ret) return 0;
	}
	if (ret < 0) ret += 2;
	return ret;
}

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			char st[333];
			scanf("%s", st);
			for (int j = 0; j < n; j++)
				mat[i][j] = st[j] == '1';
		}
		int ret = Determinant();
		printf("%s\n", ret ? "Odd" : "Even");
	}
	return 0;
}