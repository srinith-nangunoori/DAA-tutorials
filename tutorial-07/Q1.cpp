#include<iostream>
#include<cmath>
using namespace std ;

int total_nodes =0 ;
int pruned_nodes = 0 ;
vector<vector<int>>ans;
int n ;

void recursion(vector<int>&x){
    if(x.size() == n){
        ans.push_back(x);
        return ;
    }
    int test = 0 ;
    for(int i=1 ; i<n+1 ; i++){
        total_nodes++ ;
        for(int j=0 ; j<x.size() ; j++ ){
            int t_col = x[j] ;
            int t_row = j+1 ;
            if(t_col == i || abs(t_col - i) == abs(t_row - ((int)x.size() + 1)) ){
                test++ ;
                break ;
            }
        }
        if(test == 0){
            x.push_back(i) ; //
            recursion(x) ;   // main point of backtracking 
            x.pop_back() ;   //
        }
        else{
            pruned_nodes++ ;
        }
        test = 0 ;
    }
}

int main(){
    cout << "what are the number of coloumns (rows will also be the same value ): " << endl ;
    cin >> n ;
    vector <int> x ;
    recursion(x) ;
    for(int i=0 ; i<ans.size() ; i++){
        for(int j=0 ; j<n ; j++){
            cout << ans[i][j] << " " ;
        }
        cout << endl ;
    }
    cout << "total nodes : " << total_nodes << endl ;
    cout << "pruned nodes : " << pruned_nodes << endl ;
    return 0 ;
}