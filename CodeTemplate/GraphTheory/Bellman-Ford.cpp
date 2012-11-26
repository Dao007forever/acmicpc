/*
 * Bellman_Ford
 */
bool Bellman_Ford() {
	for (int i = 0; i <= n; i++)
		dis[i] = inf;
	dis[0] = 0;
	for (int i = 0; i < n; i++) {
		for (int p = 0; p < n; p++)
			for (int j = 0; j < adj[p].size(); j++) {
				int q = adj[p][j].first, tmp = dis[p] + adj[p][j].second;
				if (dis[p] != inf && dis[q] > tmp) {
					dis[q] = tmp;
				}
			}
	}
	for (int p = 0; p < n; p++)
		for (int j = 0; j < adj[p].size(); j++) {
			int q = adj[p][j].first, tmp = dis[p] + adj[p][j].second;
			if (dis[p] != inf && dis[q] > tmp) return false;
		}
	return true;
}
