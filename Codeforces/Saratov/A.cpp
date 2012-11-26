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

char str[20];
int idx;

int main() {
//      setbuf(stdout, NULL);
        
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
        
        while(scanf("%s%d", str, &idx) != EOF) {
                if(idx==1) {
                        if(*str=='f') {
                                printf("L\n");
                        } else {
                                printf("R\n");
                        }
                } else {
                        if(*str=='f') {
                                printf("R\n");
                        } else {
                                printf("L\n");
                        }
                }
        }
        return 0;
}
