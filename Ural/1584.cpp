/*
 * Author : Yang Zhang
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

#define MAXL 25
#define MAXN 105
const int inf = 1000000000;
int N, M, n, p;
char grid[MAXN][MAXN];
int cnt[33], line[MAXN];

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

int main() {
	freopen("in", "r", stdin);
	cin >> N >> M;
	for (int i = 1; i <= N; i++)
		scanf("%s", grid[i] + 1);
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			cnt[grid[i][j] - 'a']++;
	n = 0;
	for (int i = 0; i < 26; i++)
		for (int j = 1; j <= cnt[i] / 4; j++)
			line[n++] = i;
	p = 0;
	for (int i = 1; i <= N / 2; i++)
		for (int j = 1; j <= M / 2; j++) {
			for (int k = 0; k < n; k++) {
				km.E[p][k] = 0;
				if (grid[i][j] == line[k] + 'a') km.E[p][k]++;
				if (grid[N - i + 1][j] == line[k] + 'a') km.E[p][k]++;
				if (grid[i][M - j + 1] == line[k] + 'a') km.E[p][k]++;
				if (grid[N - i + 1][M - j + 1] == line[k] + 'a') km.E[p][k]++;
			}
			p++;
		}
	km.n = n;
	int ret = km.solve();
	cout << N * M - ret << endl;
	return 0;
}
