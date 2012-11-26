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

int main(int argc, char const *argv[])
{
	int n, m;
	string A, B;
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		cin >> n >> A >> m >> B;
		int cnt1 = 0, cnt2 = 0;
		for (int i = 0; i < A.size(); i++) {
			cnt1 += A[i] == '1';
		}
		for (int i = 0; i < B.size(); i++) {
			cnt2 += B[i] == '1';
		}
		if (cnt1 > 0 && cnt2 > 0) {
			printf("%d ", cnt1 + cnt2 - 1);
		} else {
			printf("0 ");
		}

		if (cnt1 == n && cnt2 == m) {
			printf("%d\n", cnt1 + cnt2 - 1);
		} else if (cnt1 == n) {
			printf("%d\n", cnt2);
		} else if (cnt2 == m) {
			printf("%d\n", cnt1);
		} else {
			int c = n + m - 1, d = n + m - 1;
			for (int i = 0; i < n; i++) {
				if (A[i] == '0') {
					c = min(c, i);
					d = min(d, n - i - 1);
				}
			}
			for (int i = 0; i < m; i++) {
				if (B[i] == '0') {
					c = min(c, i);
					d = min(d, m - i - 1);
				}
			}
			printf("%d\n", min(n + m -1, c + d));
		}
	}
	return 0;
}