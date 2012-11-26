#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

struct Node
{
    int x, y, t;
};
const int inf = 1000000;
char mat[8][8];
int a[8][8][11111];
int dx[9] = {0, 0, 0, 1, -1 ,-1, -1, 1, 1};
int dy[9] = {0, 1, -1, 0, 0, -1, 1, -1, 1};
queue<Node> q;

bool check(int x, int y) {
    if (x >= 0 && x < 8 && y >= 0 && y < 8) return true;
    return false;
}

int main() {
//    freopen("in", "r", stdin);
    for (int i = 0; i < 8; i++) {
        scanf("%s", mat[i]);
    }

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            for (int k = 0; k < 100; k++)
                a[i][j][k] = 1;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (mat[i][j] == 'S') {
                int t = 0, k = i;
                while (k < 8) {
                    a[k][j][t] = 0;
                    k++;
                    t++;
                }
            }
        }
    }

    int sx = 7, sy = 0;
    Node cur;
    cur.x = sx, cur.y = sy, cur.t = 0;
    q.push(cur);
    bool flag = false;
    while (!q.empty()) {
        Node now = q.front();
        q.pop();
        int x = now.x, y = now.y, t = now.t;
        if (x == 0 && y == 7) {
            flag = true;
            break;
        }

        for (int k = 0; k < 9; k++) {
            int xx = x + dx[k], yy = y + dy[k];
            if (check(xx, yy) && a[xx][yy][t] && a[xx][yy][t + 1]) {
                cur.x = xx, cur.y = yy, cur.t = t + 1;
                q.push(cur);
            }
        }

        if (t > 10) {
            flag = true;
            break;
        }
    }
    if (flag) puts("WIN");
    else puts("LOSE");
    return 0;
}
