/*
 * Author: Yang Zhang
 * Created Time: Sun 02 Sep 2012 01:24:45 AM CST
 * File Name: makedata.cpp
 */
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

int n = 47;
int main() {
	freopen("cha", "w", stdout);
	printf("{47");
	for (int i = 1; i < 47; i++)
		printf(",%d", rand() % 15);
	printf("}");
	return 0;
}

