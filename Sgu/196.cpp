#include <cstdio>
#include <cstring>
 
const int maxn = 10005;
int n, m;
int a[maxn];
 
int main() {
//  freopen("in", "r", stdin);
        scanf("%d%d", &n, &m);
        memset(a, 0, sizeof(a));
        while (m--) {
            int x, y;
            scanf("%d%d", &x, &y);
            a[x]++;
            a[y]++;
        }
        int ret = 0;
        for (int i = 1; i <= n; i++)
            ret += a[i] * a[i];
        printf("%d\n", ret);
    return 0;
}
