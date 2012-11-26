/**
 *  ////////////////////////////
 *  // LINE GRAPH RECOGNITION //
 *  ////////////////////////////
 *
 * MAIN FUNCTION: isLineGraph( n )
 *      Takes an unweighted, undirected graph H on n vertices and
 *      returns true iff there exists a graph G, such that H is
 *      the line graph of G. A line graph is the graph generated
 *      by mapping G's edges to H's vertices and adding an edge to
 *      H whenever the corresponding edges in G share a vertex.
 *          To retrieve the original graph G when isLineGraph()
 *      returns true, look in g[]. Although quite a pain, it will
 *      be possible to reconstruct G from g[].
 * ALGORITHM:
 *      This algorithm is much slower than the optimal O(n) algorithm.
 **/

// The graph H and some internal arrays
int hn, hm;
bool h[512][512], seen[512], oldSeen[512];
int q[512*512], qf, qb, opts[2][2];

// g[u] is the set of edges in G that have u as an endpoint
set< int > g[128], oldG[128];

bool isLineGraph()
{
    // BFS in H and create G
    for( int i = 0; i < 128; i++ ) g[i].clear();
    int gn = 0;
    memset( seen, 0, sizeof( seen ) );
    for( int s = 0; s < hn; s++ ) if( !seen[s] )
    {
        // new connected component
        memcpy( oldSeen, seen, sizeof( seen ) );
        for( int i = 0; i < gn; i++ ) oldG[i] = g[i];
        int oldgn = gn;
        int iter;
        for( iter = 0; iter < 2; iter++ )
        {
            qf = qb = 0;
            q[qb++] = s;
            g[gn++].insert( s );
            g[gn++].insert( s );
            int got1 = 0;
            while( qf < qb )
            {
                int u = q[qf++];
                if( seen[u] ) continue;
                seen[u] = true;

                // count the seen H-vertices u is connected to
                set< int > uadj;
                for( int i = 0; i < hn; i++ ) if( seen[i] && h[i][u] )
                    uadj.insert( i );

                // find all the places in G where we can insert u
                if( u != s )
                {
                    int nopts = 0;
                    for( int i = 0; i < gn && nopts < 2 - got1; i++ )
                    {
                        // can we connect to G-vertex i only?
                        if( ( !nopts || opts[0][1] >= 0 ) && g[i] == uadj )
                        {
                            opts[nopts][0] = i;
                            opts[nopts][1] = -1;
                            nopts++;
                        }

                        // can we connect to two vertices?
                        for( int j = i + 1; j < gn && nopts < 2 - got1; j++ )
                        {
                            if( g[i].size() + g[j].size() != uadj.size() ) continue;
                            set< int > gij = g[i];
                            gij.insert( g[j].begin(), g[j].end() );
                            if( gij == uadj )
                            {
                                opts[nopts][0] = i;
                                opts[nopts][1] = j;
                                nopts++;
                            }
                        }
                    }

                    // dead end?
                    if( !nopts ) { qb++; break; }

                    if( nopts > 1 ) got1 = 1;

                    // pick the correct option, depending on our iteration
                    int opt = min(iter, nopts - 1);
                    //int opt = iter <? ( nopts - 1 );

                    // add a vertex to G if necessary
                    if( opts[opt][1] == -1 ) opts[opt][1] = gn++;

                    // add the edge u to G
                    g[opts[opt][0]].insert( u );
                    g[opts[opt][1]].insert( u );
                }

                // add neighbours to the queue
                for( int v = 0; v < hn; v++ ) if( !seen[v] && h[u][v] )
                    q[qb++] = v;
            }

            if( qf == qb ) break;
            for( int i = 0; i < gn; i++ ) if( !oldSeen[i] && seen[i] )
                g[i] = oldG[i];
            memcpy( seen, oldSeen, sizeof( seen ) );
            gn = oldgn;
        }
        if( iter == 2 ) return false;
    }
    return true;
}

//Uva10988
int main()
{
    // read H into the adjacency matrix h[][] and set hn and
    // hm to the number of vertices and edges, respectively
    int Test;
    scanf("%d", &Test);
    for (int cas = 1; cas <= Test; cas++) {
    	scanf("%d%d", &hn, &hm);
    	memset(h, 0, sizeof(h));
    	for (int i = 0; i < hm; i++) {
    		int a, b;
    		scanf("%d%d", &a, &b);
    		a--; b--;
    		h[a][b] = h[b][a] = true;
    	}
    	bool answer = isLineGraph();
    	printf("Case #%d: %s\n", cas, answer ? "yes" : "no");
    }
    return 0;
}
