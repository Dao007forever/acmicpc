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

int row;
char ch;

void solve1()
{
	if (row <= 2) {
		int t = ch - 'A' + 1;
		if (t == 1 || t == 4) {
			puts("window");
			return;
		} else {
			puts("aisle");
			return;
		}
	} else {
		int t = ch - 'A' + 1;
		if (t == 1 || t == 6) {
			puts("window");
			return;
		} else{
			puts("aisle");
			return;
		}
	}
}

void solve2()
{
	int t;
	if (ch <= 'I') {
		t = ch - 'A' + 1;
	} else {
		t = ch - 'A';
	}
	if (t == 1 || t == 10) {
		puts("window");
	} else if (t == 3 || t == 4 || t == 7 || t == 8) {
		puts("aisle");
	} else {
		puts("neither");
	}
}

int main()
{
	scanf("%d%c", &row, &ch);
	if (row <= 20) {
		solve1();
	} else {
		solve2();
	}
	return 0;
}

