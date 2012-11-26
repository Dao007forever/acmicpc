 /*
  * Find bridge
  */
vector<pair<int, int> > graph[maxn];
int dfn[maxn], low[maxn], tag[maxn];
bool visit[maxm];

void Tarjan(int u, int dep) {
    dfn[u] = low[u] = dep;
    for (int i = 0; i < graph[u].size(); i++) {
        int v = graph[u][i].first;
        int id = graph[u][i].second;
        if (dfn[v] == -1) {
            visit[id] = true;//It's an undirected graph
            Tarjan(v, dep + 1);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u]) tag[id] = 1;//Edge id is a bridge
        } else if (!visit[id]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

//V is the number of Vertices
void Bridge() {
    for (int i = 0; i < V; i++)
        dfn[i] = -1;
    for (int i = 0; i < V; i++)
        if (dfn[i] == -1) Tarjan(i, 0);
}
