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

string text;
char S[1111];
int len, n;
int dp[1111], pre[1111];
vector<string>  V[26];
map<string, string> recovery;

string mix(string s) {
	if (s.size() <= 1) return s;
	sort(s.begin() + 1, s.end() - 1);
	return s;
}

bool check(string A, string B) {
	if (A[0] != B[0] || A[A.size() - 1] != B[B.size() - 1]) return false;
	return A == mix(B);
}

void reconstruct(int cur) {
	if (cur == 0) return;
	reconstruct(pre[cur]);
	if (pre[cur]) printf(" ");
	string w = mix(text.substr(pre[cur], cur - pre[cur]));
	printf("%s", recovery[w].c_str());
}

int main() {
	freopen("in", "r", stdin);
	int Test;
	cin >> Test;
	while (Test--) {
		for (int i = 0; i < 26; i++)
			V[i].clear();
		recovery.clear();

		scanf("%s", S);
		text = string(S);
		len = (int)text.size();

		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%s", S);
			string w = mix(S);
			V[w[w.size() - 1] - 'a'].push_back(w);
			recovery[w] = string(S);
		}

		memset(dp, 0, sizeof(dp));
		dp[0] = 1;
		
		for (int i = 1; i <= len; i++) {
			for (vector<string>::iterator it = V[text[i - 1] - 'a'].begin(); it != V[text[i - 1] - 'a'].end(); it++) {
				string w = *it;
				if (w.size() > i) continue;
				if (check(w, text.substr(i - w.size(), w.size())) && dp[i - w.size()]) {
					dp[i] += dp[i - w.size()];
					pre[i] = i - w.size();
				}
			}

			if (dp[i] >= 2) dp[i] = 2;
			
			bool ok = false;
			for (int j = 0; j <= 100; j++)
				if (j <= i && dp[i - j]) ok = true;
			if (!ok) break;
		}

		if (dp[len] == 0) {
			cout << "impossible" << endl;
		} else if (dp[len] == 2) {
			cout << "ambiguous" << endl;
		} else {
			reconstruct(len);
			cout << endl;
		}
	}
	return 0;
}
