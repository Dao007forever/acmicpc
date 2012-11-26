/*
 * Find Cut-Vertex
 */
void Tarjan(int u, int dep) {
    dfn[u] = low[u] = dep;
    for (int i = 0; i < graph[u].size(); i++) {
        int v = graph[u][i].first;
        int id = graph[u][i].second;
        if (dfn[v] == -1) {
            visit[id] = true;//It's an undirected graph
            Tarjan(v, dep + 1);
            low[u] = min(low[u], low[v]);
            if (low[v] >= dfn[u]) tag[u]++;//Vertex u is a Cut-Vertex
        } else if (!visit[id]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

void FindCutVertex() {
	for (int i = 0; i < N; i++)
		dfn[i] = -1;
	for (int i = 0; i < N; i++)
		if (dfn[i] == -1) {
			Tarjan(i, 0);
			tag[i]--;//Vertex i is the root
		}
}
