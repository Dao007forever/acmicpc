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

int N, K;
int a[55];

int main()
{
	cin >> N >> K;
	for (int i = 1; i <= N; i++) {
		cin >> a[i];
	}
	int ret = 0;
	for (int i = 1; i <= N; i++)
		if (a[i] && a[i] >= a[K]) ret++;
	cout << ret << endl;
	return 0;
}
