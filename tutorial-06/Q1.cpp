#include <iostream>
using namespace std ;

int main(void){
    int n =0 ; 
    cout << "what is the number of nodes in the graph : " ;
    cin >> n ;
    int e =0 ;
    cout << "how many edges are to be provided : " ;
    cin >> e ;
    cout << "provide all the edges in the graphs one by one : " << endl ;
    vector<vector<int>> adj_UD(n) ;
    vector<vector<int>> adj_D(n) ;
    int a , b ;
    for(int i=0 ; i<e ; i++){
        cin >> a ;
        cin >> b ;
        adj_UD[a].push_back(b) ;
        adj_UD[b].push_back(a) ;
        adj_D[a].push_back(b) ;
    }

    //BFS (both directed and undirected)

    queue<int>q ;
    cout << "the order of visiting done in the bfs (considering directed mapping):" << endl ;
    vector<bool>visited(n , false) ;
    for(int i=0 ; i<n ; i++){
        if(!visited[i]){
            visited[i] = true ;
            q.push(i);
            while(q.size()){
                a = q.front() ;
                cout << a << endl ;
                q.pop();
                for(int i=0 ; i<adj_D[a].size() ; i++){
                    if(!visited[adj_D[a][i]]){
                        visited[adj_D[a][i]] = true ;
                        q.push(adj_D[a][i]) ;
                    }
                }
            }
        }
    }
    while(!q.empty()) q.pop();
    fill(visited.begin(), visited.end(), false);
    cout << "the order of visiting done in the bfs (considering undirected mapping):" << endl ;
    for(int i=0 ; i<n ; i++){
        if(!visited[i]){
            visited[i] = true ;
            q.push(i);
            while(q.size()){
                a = q.front() ;
                cout << a << endl ;
                q.pop();
                for(int i=0 ; i<adj_UD[a].size() ; i++){
                    if(!visited[adj_UD[a][i]]){
                        visited[adj_UD[a][i]] = true ;
                        q.push(adj_UD[a][i]) ;
                    }
                }
            }
        }
    }

    // DFS 
    int time = 1 ;
    bool cycle = 0 ;
    stack<int>s ;
    cout << "the order of visiting with time of discovery and time of finish in dfs (considering directed mapping) : " << endl ;
    vector<pair<int , int>> log(n , {0 , 0}) ;
    int count =0 ; 
    for(int i=0 ; i<n ; i++){
        if(log[i].first == 0 ){
            s.push(i);
            while(s.size()){
                int a = s.top() ;
                if(log[a].first == 0){
                    log[a].first = time ;
                    time++ ;
                }
                count = 0 ;
                for(int j=0 ; j<adj_D[a].size() ; j++){
                    if(log[adj_D[a][j]].first !=0  && log[adj_D[a][j]].second == 0){ // cycle detection (if the is a node which is not completed and has an edge with this node , we got ourselves a cycle )
                        cycle = 1 ;
                    }
                    else if(log[adj_D[a][j]].first == 0 ){
                        s.push(adj_D[a][j]) ;
                        count++ ;
                        break ;
                    }
                }
                if(count==0){
                    log[a].second = time ;
                    time++ ;
                    s.pop();
                }
            }
        }
    }
    for(int i=0 ; i<n ; i++){
        cout << i << " =>  start : " << log[i].first << " finish : " << log[i].second << endl  ;
    }
    if(cycle){
        cout << "there is a cycle in the directed version of this graph" << endl ;
    }
    else{
        cout << "there is no cycle in the directed version of this graph" << endl ;
    }
    cout << "Edge classification (directed graph):" << endl;
    for (int u = 0; u < n; u++) {
        for (int v : adj_D[u]) {
            if (log[u].first < log[v].first && log[v].second < log[u].second)
                cout << u << " -> " << v << " : Tree/Forward edge" << endl; // tree and forward are included in 
                // one as the tree edge is literally used to traverse and create the dfs tree but that is found
                // out at the time of traversal , but as we are doing this after the traversal the tree and forward 
                // are kind of same 
            else if (log[v].first < log[u].first && log[u].second < log[v].second)
                cout << u << " -> " << v << " : Back edge" << endl;
            else
                cout << u << " -> " << v << " : Cross edge" << endl;
        }
    }
    while(!s.empty()) s.pop();
    fill(log.begin() , log.end() , make_pair(0,0));
    time =1 ;
    cout << "the order of visiting with time of discovery and time of finish in dfs (considering undirected mapping) : " << endl ;
    count =0 ; 
    cycle = 0 ;
    vector<int>parent(n , -1) ;
    for(int i=0 ; i<n ; i++){
        if(log[i].first == 0 ){
            s.push(i);
            while(s.size()){
                int a = s.top() ;
                if(log[a].first == 0){
                    log[a].first = time ;
                    time++ ;
                }
                count = 0 ;
                for(int j=0 ; j<adj_UD[a].size() ; j++){
                    if(log[adj_UD[a][j]].first != 0 && parent[adj_UD[a][j]] != a){ // detecting cycle (if edge with node which is visited and not the parent of this node)
                        cycle = 1 ;
                    }
                    if(log[adj_UD[a][j]].first == 0 ){
                        s.push(adj_UD[a][j]) ;
                        parent[adj_UD[a][j]] = a ;
                        count++ ;
                        break ;
                    }
                }
                if(count==0){
                    log[a].second = time ;
                    time++ ;
                    s.pop();
                }
            }
        }
    }
    for(int i=0 ; i<n ; i++){
        cout << i << " =>  start : " << log[i].first << " finish : " << log[i].second << endl  ;
    }
    if(cycle){
        cout << "there is a cycle in the undirected version of this graph" << endl ;
    }
    else{
        cout << "there is no cycle in the undirected version of this graph" << endl ;
    }
    cout << "Edge classification (undirected graph):" << endl;
    for (int u = 0; u < n; u++) {
        for (int v : adj_UD[u]) {
            if(u<v){// done to avoid printing same edge multiple times 
                if(parent[v]==u || parent[u]==v){
                    cout << u << " - " << v << " : Tree edge" << endl;
                }
                else{
                    cout << u << " - " << v << " : Back edge" << endl;
                }
            }
        }
    }
    return 0 ;
}


// info on type of edges 

// tree edge : edge which goes form node u to an unvisited node v (this node is definitely added to the dfs tree) 
// back edge : edge whihc goes from node u to node v where v is still not finished (still in recursion stack)(used for detecting cycles)
// forword edge : node u to a descendent v (start[u] < start[v] and finish[v] < finish[u])
// cross edge : any other edge that connects two nodes (finish[v] < start[u] or finish[u] < start[v])