#include <cstdio>
#include <cstring>
 
const int maxn = 500000 + 10;
int n;
int f[maxn], ans[maxn], col[maxn], cnt;
 
int main() {
//  freopen("in", "r", stdin);
        scanf("%d", &n);
        memset(col, 0, sizeof(col));
        for (int i = 2; i <= n; i++) {
            scanf("%d", &f[i]);
        }
        cnt = 0;
        for (int i = n; i >= 2; i--) {
            if (!col[f[i]] && !col[i]) {
                col[f[i]] = 1;
                ans[cnt++] = i;
            }
        }
 
        printf("%d\n", cnt * 1000);
        for (int i = cnt - 1; i >= 0; i--)
            printf("%d%c", ans[i], i < cnt - 1 ? ' ' : '\n');
    return 0;
}
