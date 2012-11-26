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

int n, m;

int main()
{
	cin >> n >> m;
	if ((n * m) & 1) cout << "[second]=:]" << endl;
	else cout << "[:=[first]" << endl;
	return 0;
}
