#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
using namespace std;

int main() {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
        int t, n;
        for(scanf("%d",&t); t --; ) {
                scanf("%d", &n);
                printf("%d\n", (n+1)&1);
        }
        
        
        return 0;
}
