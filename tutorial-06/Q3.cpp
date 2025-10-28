#include <iostream>
#include <set>
#include <map>
using namespace std;
vector<int>parent;
vector<int>size ;

int findparent (int x ){
    if(parent[x] == x){
        return x;
    }
    return parent[x] = findparent(parent[x]) ;
}
void Union(int weight , pair<int , int> temp , int &totalweight){
    int a = findparent(temp.first) ;
    int b = findparent(temp.second) ;
    if(a != b){
        if(size[a] != size[b]){
            if(size[a] > size[b]){
                size[a] += size[b] ;
                parent[b] = a ;
            }
            else{
                size[b] += size[a] ;
                parent[a] = b ;
            }
        }
        else{
            size[a] += size[b] ;
            parent[b] = a ;
        }
        cout << temp.first << "  " << temp.second << " (" << weight << ")"  << endl ;
        totalweight += weight ;
    }
}

int main(){
    int n =0 ; 
    cout << "number of vertices : " ;
    cin >> n ;
    int e =0 ;
    cout << "number of edges : " ;
    cin >> e ;
    cout << "provide all the edges in the graphs one by one (in the format u , v , weight)(given graph must not be a forest ): " << endl ;
    vector<vector<pair<int , int>>> graph(n) ;
    map<int , vector<pair<int, int>>> edges ;
    // a
    parent.assign(n, 0);
    size.assign(n , 1 );
    for(int i=0 ; i< n ; i++){
        parent[i] = i ;
    }
    int a , b , c;
    for(int i=0 ; i<e ; i++){
        cin >> a ;
        cin >> b ;
        cin >> c ;
        graph[a].push_back({b , c});
        graph[b].push_back({a , c});
        edges[c].push_back({a ,b}) ;
    }
    int totalweight =0  ;
    cout << "if the MST is obtained by just repeatedly choosing the least weighted edge(kruskal), the edges selected are : " << endl ;
    pair<int , int> temp ;
    for(auto &x : edges){
        for(int i=0 ; i<x.second.size() ; i++){
            Union(x.first , x.second[i] , totalweight) ;
        }
    }
    cout << "the total weight of the MST with kruskal's method is : " << totalweight << endl ;
    //b
    cout << "if the MST is obtained by just repeatedly choosing the least weighted edge starting from a vertex, the edges selected are : " << endl ;
    for(int i=0 ; i<n ; i++){
        parent[i] = -1;
    }
    totalweight = 0 ;
    priority_queue<pair<int, pair<int , int >> , vector<pair<int , pair<int , int >>> , greater <pair<int , pair<int , int >>> > pq ; // by default it is max heap so we are using this kind of syntax
    pq.push({0 , {0 , 0}});
    while(pq.size()){
        pair<int , pair<int , int >> temp = pq.top();
        pq.pop();
        if(parent[temp.second.second]==-1){
            totalweight += temp.first ;
            parent[temp.second.second] =temp.second.first ; 
            for(int i=0 ; i<graph[temp.second.second].size() ; i++){
                if(parent[graph[temp.second.second][i].first] == -1){
                    pq.push({graph[temp.second.second][i].second,{temp.second.second,graph[temp.second.second][i].first}});
                }
            }
        }
    }
    for(int i=1 ; i<n ; i++){
        cout << i << " " << parent[i] << endl ;
    }
    cout << "the total weight of the MST with prim's method is : " << totalweight << endl ;
    return 0 ;
}