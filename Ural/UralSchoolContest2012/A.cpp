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

int main(int argc, char const *argv[])
{
	vector<int> a(4);
	cin >> a[0] >> a[1] >> a[2] >> a[3];
	sort(a.begin(), a.end());
	bool flag = (a[0] == a[1]) && (a[2] == a[3]);
	printf("%s\n", flag ? "YES" : "NO");
	return 0;
}