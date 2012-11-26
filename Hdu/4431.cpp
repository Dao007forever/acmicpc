
#include <map>
#include <cstdio>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int s[55];
int ans[55];
int len, anslen;
int Cnt[55];
int Pair;
char str[55][5];
map<string, int> id;

inline void init() {
    memset(str, 0, sizeof(str));
    int tot = 0;
    for (int i = 1; i <= 9; i++) {
        str[tot][0] = '0' + i; str[tot][1] = 'm';
        id[str[tot]] = tot; tot++;
    }
    for (int i = 1; i <= 9; i++) {
        str[tot][0] = '0' + i; str[tot][1] = 's';
        id[str[tot]] = tot; tot++;
    }
    for (int i = 1; i <= 9; i++) {
        str[tot][0] = '0' + i; str[tot][1] = 'p';
        id[str[tot]] = tot; tot++;
    }
    for (int i = 1; i <= 7; i++) {
        str[tot][0] = '0' + i; str[tot][1] = 'c';
        id[str[tot]] = tot; tot++;
    }
/*    for (int i = 0; i < 34; i++)
        cout << i << " " << str[i] << endl;*/
}

inline bool Koku() {
    int t = 0;
    for (int i = 1; i <= 7; i++) {
        char ch = '0' + i;
        char add[5] = {};
        memset(add, 0, sizeof(add));
        add[0] = ch; add[1] = 'c';
        int tmp = Cnt[id[add]];
        if (tmp == 0) return false;
        if (tmp > 0) t += tmp - 1;
    }
    int tmp = Cnt[id["1m"]];
    if (tmp == 0) return false;
    if (tmp > 0) t += tmp - 1;
    tmp = Cnt[id["9m"]];
    if (tmp == 0) return false;
    if (tmp > 0) t += tmp - 1;
    tmp = Cnt[id["1p"]];
    if (tmp == 0) return false;
    if (tmp > 0) t += tmp - 1;
    tmp = Cnt[id["9p"]];
    if (tmp == 0) return false;
    if (tmp > 0) t += tmp - 1;
    tmp = Cnt[id["1s"]];
    if (tmp == 0) return false;
    if (tmp > 0) t += tmp - 1;
    tmp = Cnt[id["9s"]];
    if (tmp == 0) return false;
    if (tmp > 0) t += tmp - 1;

    if (t == 0) return false;
    return true;
}

inline bool state(int a, int b) {
    static int temp[35];
    memset(temp, 0, sizeof(temp));
    for (int i = 0; i < len; i++) {
        if (i == a || i == b) continue;
        temp[s[i]]++;
    }
    for (int i = 0; i < 9; i++) {
        if (temp[i] >= 3) temp[i] -= 3;
        if (temp[i] > 0) {
            if (i + 2 < 9 && temp[i + 1] >= temp[i] && temp[i + 2] >= temp[i]) {
                temp[i + 1] -= temp[i];
                temp[i + 2] -= temp[i];
            } else return false;
        }
    }
    for (int i = 9; i < 18; i++) {
        if (temp[i] >= 3) temp[i] -= 3;
        if (temp[i] > 0) {
            if (i + 2 < 18 && temp[i + 1] >= temp[i] && temp[i + 2] >= temp[i]) {
                temp[i + 1] -= temp[i];
                temp[i + 2] -= temp[i];
            } else return false;
        }
    }
    for (int i = 18; i < 27; i++) {
        if (temp[i] >= 3) temp[i] -= 3;
        if (temp[i] > 0) {
            if (i + 2 < 27 && temp[i + 1] >= temp[i] && temp[i + 2] >= temp[i]) {
                temp[i + 1] -= temp[i];
                temp[i + 2] -= temp[i];
            } else return false;
        }
    }
    for (int i = 27; i < 34; i++) {
        if (temp[i] > 0 && temp[i] != 3) return false;
    }
    return true;
}
inline bool win() {
    if (Pair == 7) return true;
    if (Koku()) return true;
    for (int i = 0; i < len; i++) {
        for (int j = i + 1; j < len; j++) {
            if (s[i] == s[j]) {
                if (state(i, j)) {
                    bool flag = true;
                    return true;
                }
            }
        }
    }
    return false;
}
inline void output(int x) {
    printf(" %s", str[x]);
}
int main() {
    init();
    int Test;
    scanf("%d", &Test);
    while (Test--) {
        len = anslen = Pair = 0;
        len = 13;
        memset(Cnt, 0, sizeof(Cnt));
        for (int i = 0; i < len; i++) {
            char input[5];
            scanf("%s", input);
            s[i] = id[input];
            Cnt[s[i]]++;
            if (Cnt[s[i]] == 2) Pair++;
        }

        for (int i = 0; i < 34; i++) {
            if (Cnt[i] == 4) continue;
            Cnt[i]++;
            int tmp = Pair;
            if (Cnt[i] == 2) Pair++;
            s[len++] = i;
            if (win()) {
                ans[anslen++] = i;
            }
            len--;
            Pair = tmp;
            Cnt[i]--;
        }

        if (anslen == 0) {
            printf("Nooten\n");
            continue;
        }
        sort(ans, ans + anslen);
        printf("%d", anslen);
        for (int i = 0; i < anslen; i++)
            output(ans[i]);
        printf("\n");
    }
}