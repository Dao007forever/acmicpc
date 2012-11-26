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

#define maxn 110
typedef pair<int,int> T;
struct Nod {
        int b, nxt;
};
struct Graph {
        int E[maxn], n;
        Nod buf[2*maxn];        int len;
        int ans;
        void init(int n) {
                this->n = n;
                memset(E, 255, sizeof(E));
                len = 0;
        }
        void addEge(int a, int b) {
                buf[len] = (Nod){b, E[a]};      E[a] = len ++;
                buf[len] = (Nod){a, E[b]};      E[b] = len ++;
        }
        int solve() {
                ans = 0;
                dfs(0, 0);
                return ans;
        }
        int dfs(int root, int from) {
                int first = 0;
                int second = 0;
                for(int i = E[root]; i != -1; i = buf[i].nxt) {
                        if(buf[i].b == from)    continue;
                        int tmp = dfs(buf[i].b, root) + 1;
                        if(tmp > second) {
                                second = tmp;
                                if(second > first)
                                        swap(first, second);
                        }
                }
                ans = max(ans, first+second);
                return first;
        }
} tr;

int main() {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
        int n;
        scanf("%d", &n);
        int ans = 0;
        for(int i = 0; i < n; i ++) {
                int tmpN;
                scanf("%d", &tmpN);
                int a, b;
                tr.init(tmpN);
                for(int i = 0; i < tmpN-1; i ++) {
                        scanf("%d%d", &a, &b);
                        tr.addEge(a-1, b-1);
                }
                ans += tr.solve();
        }
        printf("%d\n", ans);
        return 0;
}
