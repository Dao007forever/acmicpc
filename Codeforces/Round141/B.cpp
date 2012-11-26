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

char A[55][55], B[55][55];
int main(int argc, char const *argv[])
{
	int na, ma, nb, mb;
	cin >> na >> ma;
	for (int i = 1; i <= na; i++)
		scanf("%s", A[i] + 1);
	cin >> nb >> mb;
	for (int i = 1; i <= nb; i++)
		scanf("%s", B[i] + 1);
	int ret = 0;
	pair<int, int> ans;
	for (int x = -50; x <= 50; x++)
		for (int y = -50; y <= 50; y++) {
			int sum = 0;
			for (int i = 1; i <= na; i++)
				for (int j = 1; j <= ma; j++) {
					int ii = i + x, jj = j + y;
					if (ii >= 1 && ii <= nb && jj >= 1 && jj <= mb) {
						sum += (A[i][j] - '0') * (B[ii][jj] - '0');
					}
				}
			if (sum > ret) {
				ret = sum;
				ans = MP(x, y);
			}
		}
	//cout << ret << endl;
	cout << ans.first << " " << ans.second << endl;
	return 0;
}