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

int main(int argc, char const *argv[])
{
	map<int, int> mp;
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	mp[a]++;
	mp[b]++;
	mp[c]++;
	mp[d]++;
	int ret = 0;
	for (map<int, int>::iterator it = mp.begin(); it != mp.end(); it++) {
		if (it->second > 1)
			ret += it->second - 1;
	}
	cout << ret << endl;
	return 0;
}