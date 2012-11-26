/*
 * Author:  Yang Zhang
 * Created Time:  2012/8/20 12:36:18
 * File Name: 3718.cpp
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

#define MAXN 100
const int inf = 1 << 29;
struct KM {
	int E[MAXN][MAXN], n;		//图的所在，需传入
	bool map[MAXN][MAXN];		//每次二分匹配时的图
	
	bool visx[MAXN], visy[MAXN];//判断二分匹配时,某点是否在交错树上
	int mate[MAXN];				//V2中某点的伙伴，-1为空
	
	bool dfs(int idx) {
		visx[idx] = true;
		for(int i = 0; i < n; i ++) {
			if(map[idx][i] && !visy[i]) {
				visy[i] = true;
				if(mate[i]==-1 || dfs(mate[i])) {
					mate[i] = idx;
					return true;
				}
			}
		}
		return false;
	}
	int solve() {
		static int lx[MAXN], ly[MAXN];//V1和V2中点的标号
		int i, j;
		for(i = 0; i < n; i ++) {
			ly[i] = 0;
			lx[i] = -inf;
			for(j = 0; j < n; j ++) {
				lx[i] = max(lx[i], E[i][j]);
			}
		}
		while(true) {
			for(i = 0; i < n; i ++) {
				for(j = 0; j < n; j ++) {
					map[i][j] = lx[i]+ly[j]==E[i][j];
				}
			}
			//构图完毕，开始二分匹配
			memset(mate, 255, sizeof(mate));
			for(i = 0; i < n; i ++) {
				memset(visx, 0, sizeof(visx));
				memset(visy, 0, sizeof(visy));
				if(false == dfs(i))	break;
			}
			if(i == n) {	//找到完备匹配
				break;
			} else {		//未找到完备匹配，修改标号
				int ex = inf;
				for(i = 0; i < n; i ++) {
					if(false == visx[i])	continue;
					for(j = 0; j < n; j ++) {
						if(false == visy[j])
							ex = min(ex, lx[i]+ly[j]-E[i][j]);
					}
				}
				for(i = 0; i < n; i ++) {
					if(visx[i])	lx[i] -= ex;
					if(visy[i])	ly[i] += ex;
				}
			}
		}
		int ans = 0;
		for(int i = 0; i < n; i ++) {
			ans += E[mate[i]][i];
		}
		return ans;
	}
}km;
/*
 *在此处要做的工作 :
 *读取二分图每两点间边的权并保存在E[][]中,
 *若X与Y数目不等，应添加配合的顶点
 *保存二分图中X与Y的顶点数n,若上一步不等应保
 *存添加顶点完毕后的n
 */

int n, k, m;
char ans[10005][3], sub[10005][3];
int main() {
    freopen("in.txt", "r", stdin);
    int Test;
    scanf("%d", &Test);
    while (Test--) {
        scanf("%d%d%d", &n, &k, &m);
        for (int i = 0; i < n; i++)
            scanf("%s", ans[i]);
        while (m--) {
            km.n = 26;
            memset(km.E, 0, sizeof(km.E));
            for (int i = 0; i < n; i++) {
                scanf("%s", sub[i]);
                km.E[*ans[i] - 'A'][*sub[i] - 'A']++;
            }
            int ret = km.solve();
            double ans = (double)ret / n;
            printf("%.4f\n", ans);
        }
    }
    return 0;
}

