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

char mat[55][55];
int n;
int dx[4] = {0, 0, -1, 1};
int dy[4] = {-1, 1, 0, 0};

bool check(int i, int j) {
	if (i >= 1 && i <= n && j >= 1 && j <= n)
		if (mat[i][j] == '#') return false;
	return true;
}

int main(int argc, char const *argv[])
{
	while (~scanf("%d", &n) && n) {
		for (int i = 1; i <= n; i++)
			scanf("%s", mat[i] + 1);
		int ret = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (mat[i][j] == '#') {
					int k, cnt = 0;
					bool flag = true;
					vector<int> p;
					for (k = 1; i + k <= n; k++) {
						if (mat[i + k][j] == '#') {
							cnt++;
							if (!check(i + k, j + 1) || !check(i + k, j - 1))
								flag = false;
						} else break;
					}
					p.PB(cnt); cnt = 0;
					for (k = 1; i - k >= 1; k++) {
						if (mat[i - k][j] == '#') {
							cnt++;
							if (!check(i - k, j + 1) || !check(i - k, j - 1))
								flag = false;
						} else break;
					}
					p.PB(cnt); cnt = 0;
					for (k = 1; j + k <= n; k++) {
						if (mat[i][j + k] == '#') {
							cnt++;
							if (!check(i - 1, j + k) || !check(i + 1, j + k))
								flag =false;
						} else break;
					}
					p.PB(cnt); cnt = 0;
					for (k = 1; j - k >= 1; k++) {
						if (mat[i][j - k] == '#') {
							cnt++;
							if (!check(i - 1, j - k) || !check(i + 1, j - k))
								flag = false;
						} else break;
					}
					p.PB(cnt);
					if (flag && p.size()) {
						sort(p.begin(), p.end());
						if (p[0] != p[p.size() - 1])
							flag = false;
						if (flag && p[0] > 0) {
							ret++;
							//cout << i << " " << j << endl;
						}
					}
				}
		printf("%d\n", ret);
	}
	return 0;
}