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


int n, m;
char st[111][111];

int main() {
	cin >> n >> m;
	int ret = 0;
	for (int i = 0; i < n; i++)
		scanf("%s", st[i]);
	for (int i = 0; i < n; i++) {
		bool flag = false;
		for (int j = 0; j < m; j++) {
			bool ok = true;
			int score = st[i][j] - '0';
			for (int k = 0; k < n; k++)
				if (i != k && st[k][j] - '0' > score) {
					ok = false;
				}
			if (ok) {
				flag = true;
				break;
			}
		}
		if (flag) ret++;
	}
	cout << ret << endl;
}
