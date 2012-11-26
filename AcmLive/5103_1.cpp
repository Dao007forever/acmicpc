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

#define MAXK 27
#define MAXN 5005
char keyWord[1111];
char str[5100005], p[5100005], x[5100005];
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

	void insert(char *str) {
		int p = 0;
		for (int i = 0; str[i]; i++) {
			int index = str[i] - 'A';
			if (trie[p][index] == -1) {
				tag[size] = 0;
				fill(trie[size], trie[size] + MAXK, -1);
				trie[p][index] = size++;
			}
			p = trie[p][index];
		}
		tag[p]++;
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
			//tag[p] |= tag[fail[p]];
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

	int match(char *str) {
		int ret = 0, p = 0;
		for (int i = 0; str[i]; i++) {
			int index = str[i] - 'A';
			while (trie[p][index] == -1 && p != 0)
				p = fail[p];
			p = trie[p][index];
			int temp = p;
			while (temp && tag[temp] != -1) {
				ret += tag[temp];
				tag[temp] = -1;
				temp = fail[temp];
			}
		}
		return ret;
	}
}AC;

void change() {
	int len, c;
	len = strlen(str);  
    c = 0;
    for (int i = 0; i < len; i++) {  
		if (str[i] != '[') {  
			p[c++] = str[i];  
        } else {  
			i++;
            int q = 0;  
            while (str[i] >= '0' && str[i] <= '9') {  
                q *= 10;  
                q += str[i] - '0';  
                i++;  
            }
            int k = 0;  
            while (str[i] != ']') {  
                x[k++] = str[i];  
                i++;
            }
            for (int j = 0; j < q; j++) {  
                for (int jj = 0; jj < k; jj++) {  
                    p[c++] = x[jj];  
                }
            }
        }
	}
    p[c] = 0;
}

int main() {
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	while (Test--) {
		int n;
		AC.init();
		cin >> n;
		for (int i = 0; i < n; i++) {
			scanf("%s", keyWord);
			AC.insert(keyWord);
		}
		AC.build();
		scanf("%s", str);
		change();
		int ret = AC.match(p);
		reverse(p, p + strlen(p));
		ret += AC.match(p);
		printf("%d\n", ret);
	}
	return 0;
}
