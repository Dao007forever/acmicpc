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

int f[32][32];
int M, N, K;

void init()
{
    f[0][0] = 1;
    for (int i = 1; i <= 31; i++) {
        f[i][0] = f[i - 1][0];
        for (int j = 1; j <= i; j++)
            f[i][j] = f[i - 1][j] + f[i - 1][j - 1];
    }
}

int calc(int x, int k)
{
    int tot = 0, ret = 0;
    for (int i = 31; i > 0; i--) {
        if (x & (1 << i)) {
            tot++;
            if (tot > k) break;
            x ^= (1 << i);
        }
        if ((1 << (i - 1)) <= x) {
            ret += f[i - 1][k - tot];
        }
    }
    if (tot + x == k) ret++;
    return ret;
}

int main()
{
	init();
	int Test;
	cin >> Test;
	while (Test--) {
		cin >> M >> N >> K;
		if (M == 0) {
			if (K == 1) {
				puts("0");
				continue;
			}
			M++;
			K--;
		}
		if (N == 0) {
			if (K == 1) {
				puts("0");
				continue;
			}
			N--;
			K--;
		}
		int s = 1, tmp;
		while (tmp = calc(N, s) - calc(M - 1, s), tmp < K) {
			K -= tmp;
			s++;
		}
		int Left = M, Right = N, ret;
		while (Left <= Right) {
			int mid = (Left + Right) >> 1;
			if (calc(mid, s) - calc(M - 1, s) >= K) {
				ret = mid;
				Right = mid - 1;
			}
			else Left = mid + 1;
		}
		cout << ret << endl;
	}
	return 0;
}
