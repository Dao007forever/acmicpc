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

int n;
bool constraint[31][31];
bool avail[33];
char output[30];
char variable[30];
bool ok;

void init() {
	memset(constraint, false, sizeof(constraint));
	memset(avail, true, sizeof(avail));
}

bool check_constraint(int len, int in) {
	for (int i = 0; i < len; i++)
		if (constraint[in][output[i] - 'A'] == true) return false;
	return true;
}

void dfs(int len) {
	if (len == n) {
		ok = true;
		for (int i = 0; i < len; i++)
			printf("%c%c", output[i], i == len - 1 ? '\n' : ' ');
		return;
	}
	for (int i = 0; i < n; i++)
		if (avail[i] && check_constraint(len, variable[i] - 'A')) {
			output[len] = variable[i];
			avail[i] = false;
			dfs(len + 1);
			avail[i] = true;
		}
}

int main() {
	freopen("in", "r", stdin);
	char input[300], blank[300];
	int Test;
	scanf("%d", &Test);
	gets(blank);
	while (Test--) {
		n = 0;
		gets(blank);
		gets(input);
		for (int i = 0; input[i]; i++)
			if (isalpha(input[i])) variable[n++] = input[i];

		sort(variable, variable + n);
		init();
		gets(input);
		char first, second;

		for (int i = 0; input[i]; i++) 
			if (isalpha(input[i])) {
				first = input[i];
				i++;
				while (!isalpha(input[i])) i++;
				second = input[i];
				constraint[first - 'A'][second - 'A'] = true;
			}
		ok = false;
		dfs(0);
		if (!ok) cout << "NO" << endl;
		if (Test) puts("");
	}
	return 0;
}
