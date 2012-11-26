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

#define MAXN 50005
int len, K;
int n;
int row[MAXN];

int main(int argc, char const *argv[])
{
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		scanf("%d%d%d", &len, &K, &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &row[i]);
		}
		int ans1 = 0, cur = 0, curRow = 1;
		LL ans2 = 0;
		for (cur = 0; cur < n && row[cur] >= 1 && row[cur] <= K; cur++);
		while (cur < n) {
			ans1++;
			int Min = row[cur], Max = row[cur];
			while (cur < n) {
				cur++;
				if (cur == n) break;
				if (max(Max, row[cur]) - min(Min, row[cur]) >= K)
					break;
				Min = min(Min, row[cur]);
				Max = max(Max, row[cur]);
			}
			int l = Max - (K - 1), r = Min;
			if (curRow < l) {
				ans2 += l - curRow;
				curRow = l;
			} else if (curRow > r) {
				ans2 += curRow - r;
				curRow = r;
			}
		}
		cout << ans1 << " " << ans2 << endl;
	}
	return 0;
}