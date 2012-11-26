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

#define mod 20000000
int hash[mod];
char st[16000001];
int word_map[256], hash_add = 0;
int n, nc;

int strhash(char *key)
{
	int h = 0;
	for (int i = 0; i < n; i++) {
		h = h * nc + word_map[*(key + i)];
	}
	return h % mod;
}

int main()
{
	int SizeNC = 0, cnt = 0;
	scanf("%d%d", &n, &nc);
	scanf("%s", st);
	SizeNC = nc;

	//init map
	for (int i = 0; SizeNC; i++) {
		if (!word_map[st[i]]) {
			word_map[st[i]] = SizeNC;
			SizeNC--;
		}
	}

	for (int i = 0; st[n + i - 1] != '\0'; i++) {
		hash_add = strhash(st + i);
		if (!hash[hash_add]) {
			hash[hash_add]++;
			cnt++;
		}
	}
	printf("%d\n", cnt);
	return 0;
}
