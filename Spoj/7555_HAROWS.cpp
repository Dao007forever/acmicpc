/*
 * Author : Yang Zhang
 */
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
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

int n;
int p[55];

int main() {
	freopen("in", "r", stdin);
	int Test, cas = 1;
	scanf("%d", &Test);
	while (Test--) {
		printf("Case #%d: ", cas++);
		cin >> n;
		for (int i = 0; i < n; i++) {
			char s[55];
			scanf("%s", s);
			p[i] = -1;
			for (int j = 0; j < n; j++)
				if (s[j] == '1') p[i] = j;
		}

		int ret = 0;
		for (int i = 0; i < n; i++) {
			for (int j = i; j < n; j++)
				if (p[j] <= i) {
					for (int k = j; k > i; k--)
						p[k] = p[k - 1];
					ret += j - i;
					break;
				}
		}
		cout << ret << endl;
	}
	return 0;
}
