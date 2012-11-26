#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
using namespace std;

int calc(int x) {
	int num[10] = {0}, cnt = 0;
	while (x) {
		num[cnt++] = x % 2;
		x /= 2;
	}
	int ret = 0;
	for (int i = 7; i >= 0; i--)
		ret += (1 << (7 - i)) * num[i];
	return ret;
}
int main() {
	freopen("in", "r", stdin);
	string str;
	getline(cin, str);
	int pre = 0;
	for (int i = 0; i < str.size(); i++) {
		int t = str[i];
		t = calc(t);
		int tmp = t;
		t = (pre - t) % 256;
		if (t < 0) t += 256;
		printf("%d\n", t);
		pre = tmp;
	}
	return 0;
}

