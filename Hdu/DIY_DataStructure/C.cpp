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

#define MAXN 505 * 505
int r, c, n;
char word[555][555];
char s[21];
int x[10005], y[10005];

struct Trie {
	struct node {
		int id, s;
	};
	int size;
	node chd[MAXN][26];

	void init() {
		size = 1;
		memset(chd[0], 0, sizeof(chd[0]));
	}

	void insert(char *s, int id) {
		int p = 0, len = strlen(s);
		for (int i = 0; i < len; i++) {
			int c = s[i] - 'A';
			if (!chd[p][c].s) {
				memset(chd[size], 0, sizeof(chd[size]));
				chd[p][c].s = size++;
				if (i == len - 1) chd[p][c].id = id;
			}
			p = chd[p][c].s;
		}
	}

	void find(char *s, int sx, int sy) {
		int p = 0, len = strlen(s);
		for (int i = 0; i < len; i++) {
			int c = s[i] - 'A';
			if (chd[p][c].s) {
				if (chd[p][c].id) {
					x[chd[p][c].id] = sx;
					y[chd[p][c].id] = sy;
				}
				p = chd[p][c].s;
			} else return;
		}
	}

}T;

int main() {
	freopen("C.in", "r", stdin);
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		T.init();
		memset(x, -1, sizeof(x));
		memset(y, -1, sizeof(y));
		scanf("%d%d%d", &r, &c, &n);
		for (int i = 0; i < r; i++)
			scanf("%s", word[i]);
		for (int i = 1; i <= n; i++) {
			scanf("%s", s);
			T.insert(s, i);
		}

		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++) {
				char s1[22] = {}, s2[22] = {}, s3[22] = {};
				int len = 0;
				s1[len++] = word[i][j];
				for (int k = 1; k < 20 && j + k < c; k++) {
					s1[len++] = word[i][j + k];
				}
				T.find(s1, i, j);
				len = 0;
				s2[len++] = word[i][j];
				for (int k = 1; k < 20 && i + k < r; k++) {
					s2[len++] = word[i + k][j];
				}
				T.find(s2, i, j);
				len = 0;
				s3[len++] = word[i][j];
				for (int k = 1; k < 20 && i + k < r && j + k < c; k++) {
					s3[len++] = word[i + k][j + k];
				}
				T.find(s3, i, j);
			}
		for (int i = 1; i <= n; i++)
			printf("%d %d\n", x[i], y[i]);
	}
	return 0;
}
