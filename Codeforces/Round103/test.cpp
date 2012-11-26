#include <set>
#include <map>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <cctype>
#include <cstdio>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>
#define ll __int64
//#define ll long long
#define PI acos(-1.0)
#define PRN 105
#define INF 2000000000
using namespace std;
int f_min(int x,int y){return x<y?x:y;}
int f_max(int x,int y){return x>y?x:y;}
int f_abs(int x){return x<0?-x:x;}
int prime[PRN],Pn;
bool unprime[PRN];
void get_prime(){
        int i,j,lim=sqrt(1.0*PRN);
        memset(unprime,0,sizeof(unprime));Pn=0;
        for(i=2;i<PRN;i++){
                if(unprime[i])continue;
                prime[Pn++]=i;
                if(i>lim)continue;
                for(j=i*i;j<PRN;j+=i)unprime[j]=1;
        }
}
struct Edge{
        int u,v,w,next;
};
Edge edge[210000];
int head[100005],en;
void insert(int u,int v,int w){
        edge[en].u=u;edge[en].v=v;edge[en].w=w;
        edge[en].next=head[u];head[u]=en++;
}
int N,M,root,L;
void get_data(){
        scanf("%d%d%d",&N,&M,&root);root--;
        int i,u,v,w;
        memset(head,-1,sizeof(head));en=0;
        for(i=0;i<M;i++){
                scanf("%d%d%d",&u,&v,&w);u--;v--;
                insert(u,v,w);
                insert(v,u,w);
        }
        scanf("%d",&L);
}
int dis[100000],que[1000000],qhead,qtail;
bool inque[100000];
void spfa(){
        qhead=qtail=0;
        int i,u,v;
        for(i=0;i<N;i++){
                dis[i]=INF;
                inque[i]=0;
        }
        dis[root]=0;inque[i]=1;
        que[qtail++]=root;
        while(qtail>qhead){
                u=que[qhead++];inque[u]=0;
                for(i=head[u];i!=-1;i=edge[i].next){
                        v=edge[i].v;
                        if(dis[v]>dis[u]+edge[i].w){
                                dis[v]=dis[u]+edge[i].w;
                                if(!inque[v]){
                                        inque[v]=1;
                                        que[qtail++]=v;
                                }
                        }
                }
        }
}
void run(){
        spfa();
        int i,t,u,v,res=0;
        for(i=0;i<N;i++){
                if(dis[i]==L)res++;
        }
        for(i=0;i<en;i+=2){
                u=edge[i].u;v=edge[i].v;
                if(L>dis[u]){
                        t=L-dis[u];
                        if(t<edge[i].w){
                                if(dis[v]+edge[i].w-t>=L)res++;
                        }
                }
                if(L>dis[v]){
                        t=L-dis[v];
                        if(t<edge[i].w){
                                if(dis[u]+edge[i].w-t>=L)res++;
                        }
                }
                if(L>dis[u]&&L>dis[v]){
                        if(L-dis[u]+L-dis[v]==edge[i].w)res--;
                }
        }
        printf("%d\n",res);
}
int main(){
	freopen("in.txt", "r", stdin);
        get_data();
        run();
        return 0;
}
