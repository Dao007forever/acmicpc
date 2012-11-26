#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;

const int mod = 1000003;

long long calc(char c) {
	if (c == '>') return 8;
	if (c == '<') return 9;
	if (c == '+') return 10;
	if (c == '-') return 11;
	if (c == '.') return 12;
	if (c == ',') return 13;
	if (c == '[') return 14;
	if (c == ']') return 15;
}

int main() {
	freopen("in", "r", stdin);
	char str[111];
	scanf("%s", str);
	int n = strlen(str);
	long long ret = 0;
	for (int i = 0; i < n; i++) {
		ret <<= 4;
		ret = (ret + calc(str[i])) % mod;
	}
	cout << ret << endl;
	return 0;
}
