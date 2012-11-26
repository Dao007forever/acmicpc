/*
 * Author: Yang Zhang
 * Created Time: Fri 01 Jun 2012 08:21:09 PM UTC
 * File Name: main.cpp
 */
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
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

const LL inf = 1LL << 31;
map<int, int> f;
LL fib[100000];
char str[10000];
char ret[10000];

void init() {
	fib[1] = 1; fib[2] = 2;
	f[1] = 1; f[2] = 2;
	for (int i = 3; ; i++) {
		fib[i] = fib[i - 1] + fib[i - 2];
		if (fib[i] >= inf) break;
		f[fib[i]] = i;
	}
}

void work() {
	vector<int> v;
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int x;
		scanf("%d", &x);
		v.PB(f[x]);
	}
	gets(str);
	gets(str);
	memset(ret, ' ', sizeof(ret));
	int cnt = 0;
	for (int i = 0; cnt < n && str[i]; i++) {
		if (isupper(str[i])) {
			ret[v[cnt++]] = str[i];
		}
	}
	cnt = 0;
	for (int i = 1; cnt < n; i++) {
		if (isupper(ret[i])) {
			printf("%c", ret[i]);
			cnt++;
		} else printf(" ");
	}
	puts("");
}

int main() {
	init();
	int Test;
	scanf("%d", &Test);
	while (Test--) {
		work();	
	}
	return 0;
}
