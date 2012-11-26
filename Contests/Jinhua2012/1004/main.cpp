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

string input;

int calc(int mask) {
	int ret = 0;
	for (int i = 0; i < SZ(input) - 1; i++) {
		if (!(mask & (1 << i))) {
			LL r1 = 0, now = 0, r2 = 0;
			for (int j = 0; j <= i; j++) {
				now = now * 10 + input[j] - '0';
				if (mask & (1 << j)) {
					r1 += now;
					now = 0;
				}
			}
			r1 += now;
			now = 0;
			for (int j = i + 1; j < SZ(input); j++) {
				now = now * 10 + input[j] - '0'; 
				if (mask & (1 << j)) {
					r2 += now;
					now = 0;
				}
			}
			r2 += now;
			if (r1 == r2) ret++;
		}
	}
	return ret;
}

int main(int argc, char const *argv[])
{
	while (cin >> input && input != "END") {
		int n = input.size();
		int ret = 0;
		for (int i = 0; i < 1 << (n - 1); i++) {
			ret += calc(i);
		}
		printf("%d\n", ret);
	}
	return 0;
}