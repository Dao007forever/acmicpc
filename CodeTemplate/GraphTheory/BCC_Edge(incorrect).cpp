/*
 * Find BCC, size is the number of bcc, if id[u]=id[v], it means u and v are in the same bcc
 */
const int maxn = 100005;
struct Graph {
    vector<pair<int, int> > graph[maxn];
    int dfn[maxn], low[maxn], id[maxn], deg[maxn];
    bool visit[2*maxn];
    int N, M, size;
    stack<int> S;

    void init(int n) {
        N = n;
        for (int i = 0; i < N; i++)
            graph[i].clear();
        memset(visit, 0, sizeof(visit));
    }

    void addEdge(int u, int v, int id) {
        //cout << u << "<->" << v << endl;
        graph[u].PB(MP(v, id));
        graph[v].PB(MP(u, id));
    }

    void Tarjan(int u, int dep) {
        dfn[u] = low[u] = dep;
        S.push(u);
        for (int i = 0; i < graph[u].size(); i++) {
            int v = graph[u][i].first;
            int id = graph[u][i].second;
            if (dfn[v] == -1) {
                visit[id] = true;//It's an undirected graph
                Tarjan(v, dep + 1);
                low[u] = min(low[u], low[v]);
            } else if (!visit[id]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (low[u] == dfn[u]) {
            int v;
            size++;
            do {
                v = S.top();
                S.pop();
                id[v] = size;
            } while (u != v);
        }
    }

    void BCC() {
        size = 0;
        while (!S.empty())
            S.pop();
        memset(id, -1, sizeof(id));
        for (int i = 0; i < N; i++)
            dfn[i] = -1;
        for (int i = 0; i < N; i++)
            if (dfn[i] == -1) Tarjan(i, 0);
    }
}g;
