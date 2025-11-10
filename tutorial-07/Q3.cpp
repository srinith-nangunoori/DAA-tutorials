#include <iostream>
using namespace std ;

vector<int> ans ;
vector<vector<int >> adj;
int n ;

void recursion (vector<int> &x , vector<bool>&check){
    if(x.size() == check.size()){
        for(auto &v : adj[x[x.size()-1]]){
            if(v == 0){
                ans = x ;
                return ;
            }
        }
    }
    for(int i=0 ; i< adj[x[x.size()-1]].size() ; i++){
        if(check[adj[x[x.size()-1]][i]] == 0){      //
            check[adj[x[x.size()-1]][i]] = 1 ;      //
            x.push_back(adj[x[x.size()-1]][i])  ;   // main point of backtracking 
            recursion( x , check) ;                 //
            x.pop_back();                           //
            check[adj[x[x.size()-1]][i]] = 0 ;      //
        }
    }
}

int main(){
    cout << "how many vertices in the undirected graph(will be assumed that 1->given value) : " ;
    cin >> n ;
    int e = 0 ;
    cout << "how many number of edges : " ;
    cin >> e ;
    cout << "provide the edges one by one : " << endl;
    adj.assign (n , vector<int>()) ;
    int a = 0 ;
    int b =0 ; 
    for(int i=0 ; i< e ; i++){
        cin >> a ;
        cin >> b ;
        adj[a-1].push_back(b-1) ;
        adj[b-1].push_back(a-1) ;
    }
    vector<int> x ;
    x.push_back(0) ;
    vector<bool>check(n , false) ;
    check[0] = true;
    recursion(x , check) ;
    if(ans.size() == 0 ){
        cout << "there is no hamiltonian cycle" << endl ;
        return 0 ;
    }
    cout << ans[0]+1 ;
    for(int i=1 ; i<ans.size() ; i++){
        cout << "->" << ans[i]+1 ;
    }
    cout << endl ;
    return 0 ;
}

// in this question the check vector is passed as reference which implies that all the calls
// will use the same vector , but that does not effect at all as we write 
// our backtracking right after the recursive call