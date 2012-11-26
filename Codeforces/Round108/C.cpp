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

const long long mod = 1000000007;
int n, m;
char st[111][111];
int ch[30];

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		scanf("%s", st[i]);
	long long ret = 1;
	for (int j = 0; j < m; j++) {
		long long sum = 0;
		memset(ch, 0, sizeof(ch));
		for (int i = 0; i < n; i++)
			ch[st[i][j] - 'A']++;
		for (int i = 0; i < 30; i++)
			if (ch[i]) sum++;
		ret = (ret * sum) % mod;
	}
	cout << ret << endl;
}
