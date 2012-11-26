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

#define MAXN 100005
struct Trie {
	int chd[MAXN][26], size;
	int cnt[26];

	void init() {
		size = 1;
		memset(chd[0], 0, sizeof(chd[0]));
		memset(cnt, 0, sizeof(cnt));
	}

	void insert(char *s) {
		int p = 0;
		for (int i = 0; s[i]; i++) {
			int c = s[i] - 'a';
			if (!chd[p][c]) {
				memset(chd[size], 0, sizeof(chd[size]));
				chd[p][c] = size++;
			}
			p = chd[p][c];
		}
	}

	void sol() {
		for (int i = 1; i < size; i++)
			for (int j = 0; j < 26; j++)
				if (chd[i][j]) cnt[j]++;
	}

}pref, suff;
int n, m;
char s[1005];

int main() {
	freopen("in", "r", stdin);
	while (scanf("%d%d", &n, &m) && n + m) {
		pref.init(); suff.init();
		for (int i = 0; i < n; i++) {
			scanf("%s", s);
			pref.insert(s);
		}
		for (int i = 0; i < m; i++) {
			scanf("%s", s);
			int len = strlen(s);
			reverse(s, s + len);
			suff.insert(s);
		}
		pref.sol(); suff.sol();
		LL ret = (LL)(pref.size - 1) * (suff.size - 1);
		for (int i = 0; i < 26; i++) {
			ret -= (LL)pref.cnt[i] * suff.cnt[i];
		}
		printf("%lld\n", ret);
	}
	return 0;
}

