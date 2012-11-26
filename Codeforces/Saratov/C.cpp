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

int arr[110];
int times[110];
int n, k;

int main() {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
        
        scanf("%d%d", &n, &k);
        int tot = 0;
        for(int i = 0; i < n; i ++) {
                scanf("%d", arr+i);
                tot += arr[i];
        }
        int ans = 0;
        
        while(true) {
                int idx = -1;
                for(int i = 0; i < n; i ++) {
                        if(times[i]==3) continue;
                        if(arr[i]<k)    continue;
                        if(idx==-1 || arr[i]>arr[idx]) {
                                idx = i;
                        }
                }
                if(idx == -1)   break;
                ans ++;
                times[idx] ++;
                arr[idx] -= k;
        }
        printf("%d\n", tot-ans*k);
        return 0;
}
