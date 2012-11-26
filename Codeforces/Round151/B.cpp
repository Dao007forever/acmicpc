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

int a[100005];
int main(int argc, char const *argv[])
{
	int n, sum = 0;
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i], sum += a[i];
	if (sum % n == 0) {
		cout << n << endl;
	} else {
		cout << n - 1 << endl;
	}
	return 0;
}