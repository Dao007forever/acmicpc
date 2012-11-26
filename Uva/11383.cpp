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

const int maxV = 555;
const int inf = 0x3f3f3f3f;
//KM_General:O(N^4)
struct KM {
	int lx[maxV], ly[maxV];
	int E[maxV][maxV], n;		//图的所在，需传入
	bool map[maxV][maxV];		//每次二分匹配时的图
	
	bool visx[maxV], visy[maxV];//判断二分匹配时,某点是否在交错树上
	int mate[maxV];				//V2中某点的伙伴，-1为空
	
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

int main(int argc, char const *argv[])
{
	int n;
	while (~scanf("%d", &n)) {
		km.n = n;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &km.E[i][j]);
			}
		}
		km.solve();
		int ret = 0;
		for (int i = 0; i < n; i++) {
			printf("%d%c", km.lx[i], i == n - 1 ? '\n' : ' ');
			ret += km.lx[i];
		}
		for (int i = 0; i < n; i++) {
			printf("%d%c", km.ly[i], i == n - 1 ? '\n' : ' ');
			ret += km.ly[i];
		}
		printf("%d\n", ret);
	}
	return 0;
}