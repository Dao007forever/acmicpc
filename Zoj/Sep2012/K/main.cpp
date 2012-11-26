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

LL calc(string s) {
	LL ret = 0;
	LL now = 0;
	LL op = 1, i = 0;
	if (s[0] == '-') op = -1, i++;
	for (; i < s.size(); i++) {
		if (s[i] >= '0' && s[i] <= '9') {
			now = now*10 + s[i] - '0';
		} else {
			ret += op * now;
			now = 0;
			if (s[i] == '+') {
				op = 1;
			} else {
				op = -1;
			}
		}
	}
	ret += op *  now;
	return ret;
}

int main(int argc, char const *argv[])
{
	string s;
	LL a, b;
	while (cin >> s >> a >> b) {
		LL ret = calc(s);
		if (a == 9) {
			puts("A");
		} else if (b == 9) {
			puts("B");
		} else {
			if (ret == a) puts("B");
			else puts("A");
		}
	}
	return 0;
}