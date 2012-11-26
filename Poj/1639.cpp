#include <map>
#include <cmath>
#include <queue>
#include <vector>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define fi first
#define se second
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
typedef long long LL;

#define th(x)	this->x = x
#define maxn 1010
typedef pair<int, int> T;
typedef vector<T>::iterator I;
const int inf = 0x3f3f3f3f;
///开始并查集！
int p[maxn], r[maxn];
void make() {
	memset(r, 0, sizeof(r));
	memset(p, 255, sizeof(p));
}
int find(int x) {
	int px, i;
	for(px = x; p[px] != -1; px = p[px]);
	while(x != px) {
		i = p[x];
		p[x] = px;
		x = i;
	}
	return px;
}
//失败返回-1，否则返回新祖先
int unio(int x, int y) {
	x = find(x);	y = find(y);
	if(x == y)	return -1;
	if(r[x]>r[y]) {
		p[y]=x;
		return x;
	} else {
		p[x] = y;
		if(r[x] == r[y])	r[y] ++;
		return y;
	}
}
///////////////以上是并查集！
struct  TT {
	int a, b, v;
	void set(int a, int b, int v) {
		th(a);	th(b);	th(v);
	}
	bool operator < (const TT & tt) const {
		return v < tt.v;
	}
};
struct Kruskal {
	vector<T> E[maxn];	///图
	
	int result, part;	///最小生成树长度, 分支数
	vector<T> tree[maxn];	///用于保存最后的最小生成树
	
	void init() {
		for(int i = 0; i < maxn; i ++)	E[i].clear();
	}
	
	void addEdge(int a, int b, int val) {
		E[a].push_back(T(val, b));
		E[b].push_back(T(val, a));
	}
	void kruskal(int n) {	///顶点数[0, n)
		static TT ee[maxn*maxn];//不解释
		result = 0;
		part = n;
		make();
		for(int i = 0; i < n; i ++)		tree[i].clear();
		//初始化完毕
		int eNum = 0;
		for(int j = 0; j < n; j ++)
			for(I i = E[j].begin(); i != E[j].end(); i ++)
				if(i->second > j)
					ee[eNum ++].set(j, i->second, i->first);
		sort(ee, ee+eNum);
		//排序完毕！
		TT e;
		for(int i = 0; i < eNum; i ++) {
			e = ee[i];
			if(unio(e.a, e.b) != -1) {
				result += e.v;
				part --;
				tree[ e.a ].push_back(T( e.v, e.b ));
				tree[ e.b ].push_back(T( e.v, e.a ));
			}
		}
	}
};
/**
	最小度限制生成树[0, n)
	----
	调用kruskal
	在addEdge()前，先指明那条边要限制度数(即V0)
	solve完以后，result保存度恰好为k的最小长度，minResult保存度介于分支数和result度之间的最小长度
*/
struct Degree_MST {
	vector<T> E0;		///要限制度数的那条边
	int v0;			///要限制读书的那条边号
	Kruskal kr;			///不解释
	vector<T> tmpE0;		///用于动态保存构造过程中限度点尚未用到的边
	int result;			///度恰好为k的最小长度
	int minResult;		///度介于分支数和result度之间的最小长度
	
	void init(int v0) {
		th(v0);
		E0.clear();
		kr.init();
	}
	void addEdge(int a, int b, int val) {
		if(a == v0 || b == v0)
			E0.push_back(T(val, a+b-v0));//a+b-v0即为另外一条边！
		else 
			kr.addEdge(a, b, val);
	}
	///求小于等于k度的最小限度生成树，返回生成树大小，-1表示无法完成！
	int k_degree_mst(int n, int k) {	///定点数[0, n)	包含度限制的那个点。要限制的度数k
		if(E0.size() < k)	k = E0.size();
		/**如果要求正好是k度，换成这个
		if(E0.size() < k) {
			result = -1;
			return -1;
		}
		*/
		kr.kruskal(n);
		tmpE0.clear();
		result = kr.result;
		
		int part = 0;
		sort(E0.begin(), E0.end());
		for(I i = E0.begin(); i != E0.end(); i ++) {
			if(unio(v0, i->second) != -1){
				kr.tree[v0].push_back(T(i->first, i->second));
				kr.tree[i->second].push_back(T(i->first, v0));
				
				part ++;
				result += i->first;
			} else {
				tmpE0.push_back(*i);
			}
		}
		if(part!=kr.part-1||part>k)	return minResult=-1;//分别对应v0度不够、度大于限度
		//初始化完毕
		minResult = result;
		for(int i = 0; i < k-part; i ++)
			extend_degree();
		return minResult;
	}
	void extend_degree() {
		static bool vis[maxn];
		static TT best[maxn];
		static queue<int> q;
		memset(best, 255, sizeof(best));
		memset(vis, 0, sizeof(vis));
		q.push(v0);
		vis[v0] = true;
		int u, v, dv;
		while(!q.empty()) {
			u = q.front();
			q.pop();
			for(I i=kr.tree[u].begin();i!=kr.tree[u].end();i++){
				dv = i->first;	v = i->second;
				if(vis[v])	continue;
				vis[v] = true;
				q.push(v);
				if(u != v0) {
					if(best[u].v > dv)
						best[v]=best[u];
					else
						best[v].set(u,v,dv);//best[i->second]= i;
				}
			}
		}
		int min = inf;
		T tgt;			//要插入的那条边
		for(I i = tmpE0.begin(); i != tmpE0.end(); i ++) {
			if(i->first - best[i->second].v < min) {
				min = i->first - best[i->second].v;
				tgt = *i;
			}
		}
		kr.tree[v0].push_back(T(tgt.first, tgt.second));
		kr.tree[tgt.second].push_back(T(tgt.first, v0));
		TT tt = best[tgt.second];	//要删除的那条边
		remove(kr.tree[tt.a].begin(),kr.tree[tt.a].end(),T(tt.v, tt.b));
		remove(kr.tree[tt.b].begin(),kr.tree[tt.b].end(),T(tt.v, tt.a));
		remove(tmpE0.begin(), tmpE0.end(), tgt);
		result += tgt.first - tt.v;
		if(result < minResult)	minResult = result;
	}
} dm;
/**
 * poj-1639
	Input:
		10						//边数
		Alphonzo Bernardo 32	//边和边权
		Alphonzo Park 57
		Alphonzo Eduardo 43
		Bernardo Park 19
		Bernardo Clemenzi 82
		Clemenzi Park 65
		Clemenzi Herb 90
		Clemenzi Eduardo 109
		Park Herb 24
		Herb Eduardo 79
		3						//Park限制的度数
	Output:
		Total miles driven: 183
 */
int main() {
	int m, v, k;
	string a, b;
	cin >> m;
	map<string, int> maps;
	maps["Park"] = 0;
	dm.init(0);
	int n = 1;
	while(m --) {
		cin >> a >> b >> v;
		if(maps.find(a) == maps.end())	maps[a] = n ++;
		if(maps.find(b) == maps.end())	maps[b] = n ++;
		dm.addEdge(maps[a], maps[b], v);
	}
	cin >> k;
	int ans = dm.k_degree_mst(maps.size(), k);
	printf("Total miles driven: %d\n", ans);
	return 0;
}
