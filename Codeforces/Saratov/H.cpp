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
#include <queue>
#include <cstdlib>
#include <cstring>
using namespace std;

#define maxn1 210
#define maxn2 1000010
#define maxm 2000000

struct Nod {
        int b,nxt;
        void init(int b,int nxt) {
                this->b=b;
                this->nxt=nxt;
        }
};
struct HK {
        int E[maxn1],n,m;
        Nod buf[maxm]; int len;
        int dis1[maxn1],dis2[maxn2],mate1[maxn1],mate2[maxn2];
        void init(int n,int m) {
                this->n=n;
                this->m=m;
                memset(E,255,sizeof(E));
                len=0;
        }
        void addEdge(int a,int b) {
//              printf("a = %d, b = %d\n", a, b);
                buf[len].init(b,E[a]);E[a]=len++;
        }
        bool bfs() {
                static queue<int> q;
                memset(dis1,0,sizeof(dis1));
                memset(dis2,0,sizeof(dis2));
                for(int i=0;i<n;i++) {
                        if(mate1[i]==-1) {
                                q.push(i);
                        }
                }
                int a,b;
                bool found=false;
                while(!q.empty()) {
                        a=q.front();q.pop();
                        for(int i=E[a];i!=-1;i=buf[i].nxt) {
                                b=buf[i].b;
                                if(dis2[b]==0) {
                                        dis2[b]=dis1[a]+1;
                                        if(mate2[b]==-1) {
                                                found=true;
                                        }else{
                                                dis1[mate2[b]]=dis2[b]+1;
                                                q.push(mate2[b]);
                                        }
                                }
                        }
                }
                return found;
        }
        bool dfs(int a) {
                for(int i=E[a];i!=-1;i=buf[i].nxt) {
                        int b=buf[i].b;
                        if(dis1[a]+1==dis2[b]) {
                                dis2[b]=0;
                                if(mate2[b]==-1||dfs(mate2[b])) {
                                        mate1[a]=b;
                                        mate2[b]=a;
                                        return true;
                                }
                        }
                }
                return false;
        }
        int solve() {
                memset(mate1,255,sizeof(mate1));
                memset(mate2,255,sizeof(mate2));
                int ans=0;
                while(bfs()) {
                        for(int i=0;i<n;i++) {
                                if(mate1[i]==-1&&dfs(i)) {
                                        ans++;
                                }
                        }
                }
                return ans;
        }
}hk;

map<string, int> maps;

char str[210][15];
int m;

void dfs(int nowStrIdx, int len, int idx=0, int start=0) {
        static char tmp[10];
        char * str = ::str[nowStrIdx];
        if(idx == len) {
                tmp[len] = 0;
                string s(tmp);
                if(maps.find(s) == maps.end()) {
                        maps[s] = m ++;
                }
                hk.addEdge(nowStrIdx, maps[s]);
                return;
        }
        for(int i = start; str[i]; i ++) {
                tmp[idx] = str[i];
                dfs(nowStrIdx, len, idx+1, i+1);
        }
}

void insert(int nowStrIdx) {
        dfs(nowStrIdx, 1);
        dfs(nowStrIdx, 2);
        dfs(nowStrIdx, 3);
        dfs(nowStrIdx, 4);
}

string ss[maxn2];

int main() {
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
        int n;
        scanf("%d", &n);
        hk.init(n, 0);
        for(int i = 0; i < n; i ++) {
                scanf("%s", str[i]);
                insert(i);
        }
        hk.m = m;
        
        for(map<string,int>::iterator iter = maps.begin(); iter != maps.end(); iter ++) {
                ss[iter->second] = iter->first;
        }
        
        if(n != hk.solve()) {
                printf("-1\n");
        } else {
                for(int i = 0; i < n; i ++) {
                        cout << ss[ hk.mate1[i] ] << endl;
                }
        }
        return 0;
}
