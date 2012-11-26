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

int n;
int adj[33][33], pos[33];
int dp[111111];
char st[111111];

int main()
{
	scanf("%s", st + 1);
	int len = strlen(st + 1);
	cin >> n;
	while (n--) {
		char a[2];
		scanf("%s", a);
		adj[a[0] - 'a'][a[1] - 'a'] = 1;
		adj[a[1] - 'a'][a[0] - 'a'] = 1;
	}
	int Max = 0;
	for (int i = 1; i <= len; i++) {
		for (int j = 0; j < 26; j++)
			if (!adj[st[i] - 'a'][j])
				dp[i] = max(dp[i], dp[pos[j]] + 1);
		pos[st[i] - 'a'] = i;
		Max = max(Max, dp[i]);
	}
	cout << len - Max << endl;
	return 0;
}
