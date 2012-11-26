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
	char mat[11][11];
	while (~scanf("%s", mat[0])) {
		map<string, int> mp;
		mp["RAKIBUL"] = 1;
		mp["ANINDYA"] = 1;
		mp["MOSHIUR"] = 1;
		mp["SHIPLU"] = 1;
		mp["KABIR"] = 1;
		mp["SUNNY"] = 1;
		mp["OBAIDA"] = 1;
		mp["WASI"] = 1;
		for (int i = 1; i < 9; i++)
			scanf("%s", mat[i]);
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				string tmp;
				for (int k = 0; j + k < 9; k++) {
					tmp += mat[i][j + k];
					string s = tmp;
					sort(s.begin(), s.end());
					do {
						if (mp.find(s) != mp.end()) {
							cout << s << endl;
						}
					} while (next_permutation(s.begin(), s.end()));
				}
				tmp.clear();
				for (int k = 0; i + k < 9; k++) {
					tmp += mat[i + k][j];
					string s = tmp;
					sort(s.begin(), s.end());
					do {
						if (mp.find(s) != mp.end()) {
							cout << s << endl;
						}
					} while (next_permutation(s.begin(), s.end()));
				}
			}
		}
	}
	return 0;
}