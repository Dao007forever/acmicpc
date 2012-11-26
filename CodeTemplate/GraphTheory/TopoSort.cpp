/*
 *  topo[] is the final topological order
 */
bool toposort()
{
	queue<int> Q;
	for (int cnt = 0; cnt < N;) {
		int k = 0;
		for (int i = 1; i <= N; i++)
			if (ind[i] == 0) {
				Q.push(i);
				k++;
			}
		if (k == 0) {
			return false;
		}
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			topo.push_back(u);
			ind[u] = -1;
			for (int i = 0; i < adj[u].size(); i++)
				ind[adj[u][i]]--;
		}
		cnt += k;
	}
	return true;
}
