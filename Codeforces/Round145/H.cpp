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

const int maxn = 100005;
int n, m;
int A[maxn], B[maxn];
int main(int argc, char const *argv[])
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> A[i];
	cin >> m;
	for (int i = 0; i < m; i++)
		cin >> B[i];

	vector<int> s;
	vector<int> output;
	int l = n - 1, r = m - 1;
	if (A[l] != B[r]) {
		if (A[l] == 0) {
			for (; l >= 0 && A[l] != B[r]; l--) {
				output.PB(l + 1);
				s.PB(A[l]);
			}
		} else {
			for (; r >= 0 && A[l] != B[r]; r--) {
				output.PB(n + r + 1);
				s.PB(B[r]);
			}
		}
	}

	while (l >= 0 && r >= 0) {
		int ch = A[l];
		for (; l >= 0 && A[l] == ch; l--) {
			output.PB(l + 1);
			s.PB(A[l]);
		}
		for (; r >= 0 && B[r] == ch; r--) {
			output.PB(n + r + 1);
			s.PB(B[r]);
		}
	}

	if (l == -1 && r >= 0) {
		for (; r >= 0; r--) {
			output.PB(n + r + 1);
			s.PB(B[r]);
		}
	}
	if (r == -1 && l >= 0) {
		for (; l >= 0; l--) {
			output.PB(l + 1);
			s.PB(A[l]);
		}
	}

	reverse(output.begin(), output.end());
	reverse(s.begin(), s.end());
	for (int i = 0; i < output.size(); i++)
		printf("%d%c", output[i], i == output.size() - 1 ? '\n' : ' ');

//	for (int i = 0; i < s.size(); i++)
//		cout << s[i];
	vector<int> ans;
	for (int i = 0; i < s.size() - 1; i++)
		if (s[i] != s[i + 1]) ans.PB(i + 1);
	if (s[s.size() - 1] == 1) ans.PB(s.size());
	cout << ans.size() << endl;
	for (int i = 0; i < ans.size(); i++)
		printf("%d%c", ans[i], i == ans.size() - 1 ? '\n' : ' ');
	return 0;
}