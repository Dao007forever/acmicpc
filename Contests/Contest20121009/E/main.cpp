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

int r, c;
char mat[55][55];

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	for (int cas = 1; Test--; cas++) {
		printf("Case %d: ", cas);
		scanf("%d%d", &r, &c);
		for (int i = 1; i <= r; i++)
			scanf("%s", mat[i] + 1);
		bool flag = true;
		for (int i = 1; i <= r; i++) {
			int j;
			for (j = 0; j <= c; j++)
				if (mat[i][j] == '0') break;
			if (j == c + 1) {
				flag = false;
				break;
			}
		}
		if (!flag) {
			puts("-1");
			continue;
		}
		int ret = 0x3f3f3f3f;
		for (int move = 1; move <= c; move++) {
			int cnt = 0;
			for (int i = 1; i <= r; i++) {
				int Min = 0x3f3f3f3f;
				int k = -1;
				for (int j = move; j <= c; j++)
					if (mat[i][j] == '0') {
						k = j;
						break;
					}
				if (k != -1) Min = min(Min, k - move);
				k = -1;
				for (int j = move - 1; j >= 1; j--)
					if (mat[i][j] == '0') {
						k = j;
						break;
					}
				if (k != -1) Min = min(Min, move - k);
				cnt += Min;
			}
			ret = min(ret, cnt);
		}
		printf("%d\n", ret);
	}
	return 0;
}