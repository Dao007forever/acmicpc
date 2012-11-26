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

#define MAXK 4
#define MAXN 1005
int score[11];
char keyWord[111];
int ID(char ch) {
	if (ch == 'A') return 0;
	if (ch == 'T') return 1;
	if (ch == 'C') return 2;
	return 3;
}
struct AC_Automaton {

	int size;
	int tag[MAXN];
	int fail[MAXN];
	int trie[MAXN][MAXK];

	void init() {
		tag[0] = 0;
		fill(trie[0], trie[0] + 4, -1);
		size = 1;
	}

	void insert(char *str, int t) {
		int p = 0;
		for (int i = 0; str[i]; i++) {
			int index = ID(str[i]);
			if (trie[p][index] == -1) {
				tag[size] = 0;
				fill(trie[size], trie[size] + MAXK, -1);
				trie[p][index] = size++;
			}
			p = trie[p][index];
		}
		tag[p] |= t;
	}

	void build() {
		queue<int> Q;
		fail[0] = 0;
		for (int i = 0; i < MAXK; i++) {
			if (trie[0][i] != -1) {
				fail[trie[0][i]] = 0;
				Q.push(trie[0][i]);
			} else {
				trie[0][i] = 0;
			}
		}
		while (!Q.empty()) {
			int p = Q.front();
			Q.pop();
			tag[p] |= tag[fail[p]];
			for (int i = 0; i < MAXK; i++) {
				if (trie[p][i] != -1) {
					fail[trie[p][i]] = trie[fail[p]][i];
					Q.push(trie[p][i]);
				} else {
					trie[p][i] = trie[fail[p]][i];
				}
			}
		}
	}
}AC;

bool dp[2][MAXN][1 << 10];
int main() {
	freopen("in", "r", stdin);
	int N, M;
	while (scanf("%d%d", &N, &M) != EOF) {
		AC.init();
		for (int i = 0; i < N; i++) {
			scanf("%s %d", keyWord, &score[i]);
			AC.insert(keyWord, 1 << i);
		}
		AC.build();
		
		int pre = 0, cur = 1;
		fill(dp[cur][0], dp[cur][AC.size], false);
		dp[cur][0][AC.tag[0]] = true;
		for (int i = 0; i < M; i++) {
			swap(pre, cur);
			fill(dp[cur][0], dp[cur][AC.size], false);
			for (int j = 0; j < AC.size; j++) {
				for (int k = 0; k < 4; k++) {
					int jj = AC.trie[j][k];
					for (int t = 0; t < (1 << N); t++) {
						dp[cur][jj][t | AC.tag[jj]] |= dp[pre][j][t];
					}
				}
			}
		}
		int ret = -1;
		for (int i = 0; i < (1 << N); i++) {
			for (int j = 0; j < AC.size; j++) {
				if (dp[cur][j][i]) {
					int tmp = 0;
					for (int k = 0; k < N; k++) {
						if (i & (1 << k)) {
							tmp += score[k];
						}
					}
					ret = max(ret, tmp);
					break;
				}
			}
		}
		if (ret < 0) cout << "No Rabbit after 2012!" << endl;
		else cout << ret << endl;
	}
	return 0;
}
