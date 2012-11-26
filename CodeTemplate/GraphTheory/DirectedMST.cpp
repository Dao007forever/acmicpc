/*
 *构建了虚根之后，虚根到每个原图中的点连一条边，边权为其他所有边的边权之和+1，那么如果最后最小树形图的
 *总权值减去加上的虚边的边权仍大于等于这个边权，就说明存在点在原图中是不连通的。
 */
typedef long long F;
const int MAXN = 1005;
const int MAXM = MAXN * MAXN * 5;
const F inf = 1ll<<60;
struct Edge {
    int u, v;
    F cost;
};
int ans_root;
struct DirectedMST {
    int V, E;
    Edge edge[MAXM];
    int pre[MAXN], ID[MAXN], vis[MAXN];
    F In[MAXN];

    void init(int V) {
        this->V = V;
        E = 0;
    }

    void addEdge(int u, int v, F cost) {
        edge[E].u = u; edge[E].v = v; edge[E].cost = cost; E++;
    }

    F solve(int root) {
        F ret = 0;
        while (true) {
            //1.找最小入边
            for (int i = 0; i < V; i++) In[i] = inf;
            for (int i = 0; i < E; i++) {
                int u = edge[i].u, v = edge[i].v;
                if (edge[i].cost < In[v] && u != v) {
                    pre[v] = u;
                    In[v] = edge[i].cost;
                    /*下面两句用来求虚根，ans_root减去原图中的边数就是原图中的根，这里不能用edge[i].v作为
                     *ans_root，因为edge[i]里的内容是会变化的，而新增的m~m+n-1则是虚边，而第i条虚边到达的
                     *点就是在新图中虚根到达的点，也即原图中的根
                     */
                    if (u == root) {
                        ans_root = i;
                    }
                }
            }
            for (int i = 0; i < V; i++) {
                if (i == root) continue;
                if (In[i] == inf) return -1;//除了根意外有点没有入边，则根无法到达它
            }
            //2.找环
            int cntnode = 0;
            memset(ID, -1, sizeof(ID));
            memset(vis, -1, sizeof(vis));
            In[root] = 0;
            for (int i = 0; i < V; i++) {//标记每个环
                ret += In[i];
                int v = i;
                while (vis[v] != i && ID[v] == -1 && v != root) {
                    vis[v] = i;
                    v = pre[v];
                }
                if (v != root && ID[v] == -1) {
                    for (int u = pre[v]; u != v; u = pre[u]) {
                        ID[u] = cntnode;
                    }
                    ID[v] = cntnode++;
                }
            }
            if (cntnode == 0) break;//无环
            for (int i = 0; i < V; i++) if (ID[i] == -1) {
                ID[i] = cntnode++;
            }
            //3.缩点，重新标记
            for (int i = 0; i < E; i++) {
                int v = edge[i].v;
                edge[i].u = ID[edge[i].u];
                edge[i].v = ID[edge[i].v];
                if (edge[i].u != edge[i].v) {
                    edge[i].cost -= In[v];
                }
            }
            V = cntnode;
            root = ID[root];
        }
        return ret;
    }
}dmst;

//Hdu2121
int main(int argc, char const *argv[])
{
    int n, m;
    while (~scanf("%d%d", &n, &m)) {
        LL sum = 0;
        dmst.init(n + 1);
        for (int i = 0; i < m; i++) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            u++; v++;
            dmst.addEdge(u, v, w);
            sum += w;
        }
        sum++;
        for (int i = m; i < n + m; i++) {
            dmst.addEdge(0, i - m + 1, sum);
        }
        F ans = dmst.solve(0);
        if (ans == -1 || ans - sum >= sum) puts("impossible");
        else cout << ans - sum << " " << ans_root - m << endl;
        puts("");
    }
    return 0;
}