#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int len = 10000 + 10;
const int maxn = 3000;
int n, k;
char line[4][len];
char yuan[5] = {'a', 'e', 'i', 'o', 'u'};
string anw[4] = {"aaaa", "aabb", "abab", "abba"};
bool pp[5][5];
int f[4][len];

int findIdx(char* s, int k) {
	int l = strlen(s);
	int i;
	for (i = l - 1; i >= 0 && k > 0; i--) {
		for (int j = 0; j < 5; j++) if (s[i] == yuan[j]) {
			k--;
		}
	}
	if (k == 0) return i + 1;
	else return -1;
}
bool pare(char* s1, char* s2) {
	int i1 = findIdx(s1, k);
	int i2 = findIdx(s2, k);
	if (i1 == -1 || i2 == -1) return false;
	return strcmp(s1 + i1, s2 + i2) == 0;
}

bool check(int ind) {
	for (int i = 0; i < n; i++) if ((!f[ind][i]) && !f[0][i]) return false;
	return true;
}

void output() {
	cout << "NO" << endl;
}

int main() {
//freopen("test.in", "r", stdin);
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 4; j++)
			cin >> line[j];
		int u, v;
		memset(pp, 0, sizeof(pp));
		for (u = 0; u < 4; u++) for (int v = u + 1; v < 4; v++) {
			if (pare(line[u], line[v])) pp[u][v] = 1;
		}
		if (pp[0][1] && pp[0][2] && pp[0][3]) {
			f[0][i] = 1;
		} else if (pp[0][1]) {
			if (pp[2][3]) f[1][i] = 1; 
			else {
				output();
				return 0;
			}
		} else if (pp[0][2]) {
			if (pp[1][3]) f[2][i] = 1; 
			else {
				output();
				return 0;
			}
		} else if (pp[0][3]) {
			if (pp[1][2]) f[3][i] = 1; 
			else {
				output();
				return 0;
			}
		} else {
			output();
			return 0;
		}
	} 
	for (int i = 0; i < 4; i++) if (check(i)) {
		cout << anw[i] << endl;
		return 0;
	}
	output();
	return 0;
}
