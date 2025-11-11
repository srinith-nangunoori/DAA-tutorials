#include <iostream>
#include<algorithm>
using namespace std;

// Part (a) & (b): Max Flow (BFS based Ford-Fulkerson)
class MaxFlow{
public:
    int V;
    vector<vector<int>> capacity, adj;

    MaxFlow(int n) {
        V = n;
        capacity.assign(V, vector<int>(V, 0));
        adj.assign(V, vector<int>());
    }

    void addEdge(int u, int v, int cap) {
        capacity[u][v] = cap;
        adj[u].push_back(v);
        adj[v].push_back(u); // add reverse edge for residual graph
    }

    int bfs(int s, int t, vector<int> &parent) {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2; // mark source as visited
        queue<pair<int,int>> q;
        q.push({s, INT_MAX});
        while(!q.empty()) {
            int cur = q.front().first;
            int flow = q.front().second;
            q.pop();
            for(int next : adj[cur]) {
                if(parent[next] == -1 && capacity[cur][next] > 0) {
                    parent[next] = cur;
                    int new_flow = min(flow, capacity[cur][next]);
                    if(next == t) return new_flow;
                    q.push({next, new_flow});
                }
            }
        }
        return 0;
    }

    int edmondsKarp(int s, int t, vector<vector<int>> &residual) {
        int flow = 0;
        vector<int> parent(V);
        int new_flow;
        while(new_flow = bfs(s, t, parent)) {
            flow += new_flow;
            int cur = t;
            while(cur != s) {
                int prev = parent[cur];
                capacity[prev][cur] -= new_flow;
                capacity[cur][prev] += new_flow;
                cur = prev;
            }
            residual = capacity;
        }
        return flow;
    }

    void minCut(int s, vector<vector<int>> &residual, vector<int> &cut) {
        vector<bool> visited(V, false);
        queue<int> q; q.push(s); visited[s] = true;
        while(!q.empty()) {
            int u = q.front(); q.pop();
            for(int v : adj[u]) {
                if(residual[u][v] > 0 && !visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        for(int i=0;i<V;i++) if(visited[i]) cut.push_back(i);
    }
};

// Part (c): Min-Cost Max-Flow using Successive Shortest Path (Bellman-Ford)
class MinCostMaxFlow {
public:
    struct Edge {
        int to, rev, cap, cost;
    };
    int N;
    vector<vector<Edge>> G;
    vector<int> dist, prevv, preve;

    MinCostMaxFlow(int n) {
        N = n;
        G.assign(N, vector<Edge>());
        dist.assign(N, 0);
        prevv.assign(N, 0);
        preve.assign(N, 0);
    }

    void addEdge(int from, int to, int cap, int cost) {
        G[from].push_back({to, (int)G[to].size(), cap, cost});
        G[to].push_back({from, (int)G[from].size()-1, 0, -cost});
    }

    pair<int,int> minCostMaxFlow(int s, int t) {
        int flow = 0, cost = 0;
        while(true) {
            fill(dist.begin(), dist.end(), INT_MAX);
            dist[s] = 0;
            bool updated = true;
            while(updated) {
                updated = false;
                for(int v=0; v<N; v++) {
                    if(dist[v] == INT_MAX) continue;
                    for(int i=0; i<G[v].size(); i++) {
                        Edge &e = G[v][i];
                        if(e.cap > 0 && dist[e.to] > dist[v] + e.cost) {
                            dist[e.to] = dist[v] + e.cost;
                            prevv[e.to] = v;
                            preve[e.to] = i;
                            updated = true;
                        }
                    }
                }
            }
            if(dist[t] == INT_MAX) break;
            int d = INT_MAX;
            for(int v=t; v!=s; v=prevv[v]) d = min(d, G[prevv[v]][preve[v]].cap);
            flow += d;
            cost += d * dist[t];
            for(int v=t; v!=s; v=prevv[v]) {
                Edge &e = G[prevv[v]][preve[v]];
                e.cap -= d;
                G[v][e.rev].cap += d;
            }
        }
        return {flow, cost};
    }
};

int main() {
    int n, e;
    cout << "Number of vertices: "; cin >> n;
    cout << "Number of edges: "; cin >> e;

    MaxFlow mf(n);
    cout << "Enter edges (u v capacity):" << endl;
    for(int i=0;i<e;i++){
        int u,v,c; cin>>u>>v>>c;
        mf.addEdge(u,v,c);
    }

    int source, sink;
    cout << "Source vertex: "; cin >> source;
    cout << "Sink vertex: "; cin >> sink;

    vector<vector<int>> residual;
    int maxFlow = mf.edmondsKarp(source, sink, residual);
    cout << "Maximum flow value: " << maxFlow << endl;

    vector<int> cut;
    mf.minCut(source, residual, cut);
    cout << "Minimum cut set: ";
    for(int v: cut) cout << v << " ";
    cout << endl;

    cout << "\nResidual network:" << endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cout << residual[i][j] << " ";
        }
        cout << endl;
    }

    // Part (b) and (c) would need their specific input formats
    // Part (b): Bipartite matching can be modeled as max flow from source to sink
    // Part (c): Min-cost max flow can be computed using the MinCostMaxFlow class
}



// A: Edmonds-Karp / BFS-based Ford-Fulkerson (Maximum Flow)
// Repeatedly find an augmenting path from source to sink in the residual network,
// push the maximum possible flow along this path (bottleneck capacity),
// and update the residual capacities. Stop when no augmenting path exists.(paths form source to destination)
// Maximum flow value = sum of flows along augmenting paths.
// Minimum cut can be found as all vertices reachable from the source in the residual network.

// B: Bipartite Matching as Max Flow
// Model the bipartite graph as a flow network:
// source -> left partition (capacity 1), left -> right partition (capacity 1),
// right -> sink (capacity 1). Run max flow.
// Max flow value = maximum number of matchings, and matched edges correspond to flow = 1.

// C: Min-Cost Max-Flow (Capacitated, Cost-Weighted Network)
// Repeatedly find the shortest path from source to sink in terms of cost in the residual network,
// push flow along the path (limited by bottleneck capacity), and update residual capacities.
// Repeat until no more paths exist. Output is maximum flow with minimum total cost.