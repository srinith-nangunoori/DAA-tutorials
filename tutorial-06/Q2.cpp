// main idea 
// a) to get a valid ordering essentially means providing a list corresponding to a topological sort
// b) just do dfs , reverse the graph , do dfs according to the reverse order of dfs which will give the SCC , and they also form dag 
// so as these questions a , b require completely different types of graphs to work (a requires one with no cycle , b requires one with cycle), I will just put them in if else path with an initial check for a cycle

#include <iostream>
using namespace std;

int main(){
    bool cycle = 0 ;
    int n =0 ; 
    cout << "number of vertices : " ;
    cin >> n ;
    int e =0 ;
    cout << "number of edges : " ;
    cin >> e ;
    cout << "provide all the edges in the graphs one by one : " << endl ;
    vector<vector<int>> graph(n) ;
    vector<vector<int>> Rgraph(n) ;
    int a , b ;
    for(int i=0 ; i<e ; i++){
        cin >> a ;
        cin >> b ;
        graph[a].push_back(b);
        Rgraph[b].push_back(a);
    }
    vector<pair<int , int>> times(n , {0 , 0}) ;
    vector<int>order ;
    int time =1 ;
    int count = 0 ;
    stack <int> s ;
    for(int i=0 ; i<n ; i++){
        if(times[i].first == 0 ){
            s.push(i) ;
            while(!s.empty()){
                int a = s.top();
                if(times[a].first == 0 ){
                    times[a].first = time ;
                    time ++ ;
                }
                count = 0 ;
                for(int j=0 ; j<graph[a].size() ; j++){
                    if(times[graph[a][j]].first != 0 && times[graph[a][j]].second == 0){
                        // this implies a back edge which implies a cycle 
                        cycle = 1 ;
                    }
                    else if(times[graph[a][j]].first == 0){
                        s.push(graph[a][j]) ;
                        count++ ;
                        break ;
                    }
                }
                if(count==0){
                    order.push_back(a);
                    times[a].second = time ;
                    time++ ;
                    s.pop();
                }
            }
        }
    }
    reverse(order.begin() , order.end()) ;
    if(cycle==0){ // a) 
        cout << "the graph does not contain any cycle , it is a DAG and a valid ordering is : " << endl ;
        for(int i=0 ; i<n ; i++){
            cout << order[i] << endl ;
        }
    }
    else{
        cout << "the graph contains cycle(s) , the components in the SCC are : " << endl ;
        stack <int> component ;
        count = 0 ;
        time = 1 ;
        while(!s.empty()) s.pop() ;
        fill(times.begin() , times.end() , make_pair(0,0));
        int counter = 1 ;
        for(int i=0 ; i<n ; i++){
            if(times[i].first == 0 ){
                s.push(i) ;
                while(!s.empty()){
                    int a = s.top();
                    if(times[a].first == 0 ){
                        times[a].first = time ;
                        time ++ ;
                    }
                    count = 0 ;
                    for(int j=0 ; j<graph[a].size() ; j++){
                        if(times[graph[a][j]].first == 0){
                            s.push(graph[a][j]) ;
                            count++ ;
                            break ;
                        }
                    }
                    if(count==0){
                        component.push(a) ;
                        times[a].second = time ;
                        time++ ;
                        s.pop();
                    }
                }
            }
            if(component.size()){
                cout << "component number : " << counter << endl ;
                counter ++ ;
            }
            while(component.size()){
                cout << component.top() << endl;
                component.pop();
            }
        }
    }
    return 0 ;
}
