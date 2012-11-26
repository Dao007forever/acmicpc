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

const int maxn = 100005;
int state[maxn], prime[maxn];
int n, m;

int main()
{
//	freopen("in", "r", stdin);
	cin >> n >> m;
	while (m--) {
		char op[5];
		int p;
		scanf("%s %d", op, &p);
		if (*op == '+') {
			if (state[p]) {
				puts("Already on");
			} else {
				int flag = 1, ans;
				for (int i = 2; i * i <= p; i++)
					if (p % i == 0) {
						if (prime[i]) {
							flag = 0;
							ans = prime[i];
							break;
						}
						if (prime[p / i]) {
							flag = 0;
							ans = prime[p / i];
							break;
						}
					}
				if (p > 1 && prime[p]) {
					flag = 0;
					ans = prime[p];
				}
				if (!flag) {
					printf("Conflict with %d\n", ans);
				} else {
					for (int i = 2; i * i <= p; i++)
						if (p % i == 0) {
							prime[i] = p;
							prime[p / i] = p;
						}
					if (p > 1) prime[p] = p;
					state[p] = 1;
					puts("Success");
				}
			}
		} else {
			if (!state[p]) {
				puts("Already off");
			} else {
				puts("Success");
				for (int i = 2; i * i <= p; i++)
					if (p % i == 0) {
						prime[i] = 0; prime[p / i] = 0;
					}
				if (p > 1) prime[p] = 0;
				state[p] = 0;
			}
		}
	}
}
