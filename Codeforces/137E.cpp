#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 200000 + 5;
int n;
int sum[maxn], dp[maxn];
char str[maxn];
vector<pair<int, int> > vec;

bool isVowel(char c) {
	if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') return true;
	if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') return true;
	return false;
}

void Print() {
	for (vector<pair<int, int> >::iterator it = vec.begin(); it != vec.end(); it++)
		printf("%d %d\n", it->first, it->second);
}

int main() {
//	freopen("in", "r", stdin);
	scanf("%s", str);
	n = strlen(str);
	for (int i = 0; i < n; i++) {
		if (isVowel(str[i])) sum[i + 1] = sum[i] - 1;
		else sum[i + 1] = sum[i] + 2;
	}
	
	for (int i = 0; i <= n; i++) {
		vec.push_back(make_pair(sum[i], i));
	}
	sort(vec.begin(), vec.end());
	reverse(vec.begin(), vec.end());
	int ret = 0, Max = -1;
	for (vector<pair<int, int> >::iterator it = vec.begin(); it != vec.end(); it++) {
		int pos = it->second;
		if (pos < Max) {
			dp[it->second] = Max - pos;
			ret = max(ret, Max - pos);
		}
		if (pos > Max) Max = pos;
	}
	if (ret == 0) printf("No solution\n");
	else {
		int cnt = 0;
		for (int i = 0; i <= n; i++)
			if (dp[i] == ret) cnt++;
		printf("%d %d\n", ret, cnt);
	}
	return 0;
}
