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

int a[26] = {1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2,3,1,2};
int main() {
	char s[1111];
	gets(s);
	int ret = 0;
	for (int i = 0; s[i]; i++) {
		if (s[i] >= 'a' && s[i] <= 'z')
			ret += a[s[i] - 'a'];
		else if (s[i] == '.') ret++;
		else if (s[i] == ',') ret += 2;
		else if (s[i] == '!') ret += 3;
		else ret++;
	}
	cout << ret << endl;
	return 0;
}
