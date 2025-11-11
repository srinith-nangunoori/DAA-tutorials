#include<iostream>
using namespace std ;

int main(){
    int n=0 ; 
    cout << "number of vertices : " ;
    cin >> n ;
    int e =0 ;
    cout <<"number of edges : " ;
    cin >> e ;
    cout << "provide all the edges (in the format u , v , weight ): " << endl;
    vector<vector<pair<int , int >>> graph(n) ;
    vector<pair<int , pair<int , int >>> edges(e) ;
    int a =0 ;
    int b =0 ; 
    int c =0 ; 
    int neg = 0 ;
    for(int i=0 ; i<e ; i++){
        cin >> a ;
        cin >> b ;
        cin >> c ;
        graph[a].push_back({c , b });
        edges[i] = {c , {a , b}};
        if(c<0){
            neg = 1;
        }
    }
    vector<int>shortest(n , INT_MAX) ;
    if(neg == 0){
        //a Dijkstras
        vector<string> paths(n , "0");
        vector<bool> checked (n);
        shortest[0] = 0 ;
        priority_queue<pair<int, pair<int , int >>  , vector<pair<int , pair<int , int >>> , greater<pair<int , pair<int , int >>> > pq ;
        pq.push({0, {0, 0}});  
        while(pq.size()){
            pair<int , pair<int , int> > temp = pq.top() ;
            if(shortest[temp.second.second] > temp.first){
                shortest[temp.second.second] = temp.first ;
                if(temp.second.second != 0 ){
                    paths[temp.second.second] = paths[temp.second.first]+"->"+to_string(temp.second.second) ;
                }
            }
            pq.pop();
            for(int j=0 ; j<graph[temp.second.second].size() ; j++){
                if(temp.first+graph[temp.second.second][j].first < shortest[graph[temp.second.second][j].second]){
                    pq.push({temp.first+graph[temp.second.second][j].first , {temp.second.second , graph[temp.second.second][j].second}}) ;
                }
            }
        }
        cout << "shortest paths : " << endl ;
        for(int i=1 ; i<n ; i++){
            cout << "0 to " << i << "   shortest path length is : "  << shortest[i] << "    shortest path is : "<< paths[i] <<endl ;
        }
    }
    else{
        //b : bellman-Ford
        shortest[0] = 0 ;
        bool negcycles = false ;
        for(int i=1 ; i<n ; i++){
            for(int j =0 ; j<e ; j++){
                if(shortest[edges[j].second.second] > shortest[edges[j].second.first]+edges[j].first){
                    shortest[edges[j].second.second] = shortest[edges[j].second.first]+edges[j].first ;
                }
            }
        }
        // to detect cycles
        for(int j=0 ; j<e ; j++){
            if(shortest[edges[j].second.second] > shortest[edges[j].second.first]+edges[j].first){
                negcycles = true ;
            }
        }
        if(negcycles){
            cout << "negative cycles are present" << endl ;
        }
        else{
            for(int i=1 ; i<n ; i++){
                cout << "0 to " << i << "   shortest path length is : "  << shortest[i] << endl ;
            }
        }   
    }

    // c
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    for(int i=0; i<n; i++){
        dist[i][i] = 0;
    }
    for(int i=0; i<e; i++){
        int u = edges[i].second.first;
        int v = edges[i].second.second;
        dist[u][v] = edges[i].first;
    }
    // Floyd-Warshall core
    for(int k=0; k<n; k++){
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                   dist[i][j] > dist[i][k] + dist[k][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    // Detect negative cycles
    bool negCycle = false;
    for(int i=0; i<n; i++){
        if(dist[i][i] < 0) negCycle = true;
    }
    cout <<"All pairs shortest paths:" << endl;
    if(negCycle){
        cout << "Negative weight cycle detected in the graph." << endl;
    } 
    else {
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(dist[i][j] == INT_MAX) cout << "INF ";
                else cout << dist[i][j] << " ";
            }
            cout << endl;
        }
    }
    return 0 ;
}

// A : Dijkstra’s Algorithm (Single Source, Non-Negative Weights)
// At each step, pick the vertex with the smallest known distance 
// from the source, finalize that distance, and relax its neighbors.

// B: Bellman-Ford Algorithm (Single Source, Negative Weights)
// Relax all edges V-1 times; if we can still relax after that, there is a negative cycle.

// C : Floyd-Warshall Algorithm (All-Pairs Shortest Paths)
// Use dynamic programming: iteratively consider each vertex as an intermediate 
// point and update the distance matrix.
