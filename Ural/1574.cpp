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

char input[100005];

int main() {
	scanf("%s", input);
	int n = strlen(input);
	int cur = 0, Min = 1000000000, ret = 1;
	for (int i = 0; i < n; i++) {
		if (input[i] == '(') cur++;
		else cur--;
		if (cur < Min) {
			Min = cur;
			ret = 0;
		}
		if (cur == Min) ret++;
	}
	if (cur == 0) cout << ret << endl;
	else cout << 0 << endl;
	return 0;
}
