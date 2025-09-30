#include<iostream>
#include <vector>
#include <climits>  
using namespace std ;

vector<vector<int>> cost;
vector<vector<int>> pos;

void printer(int i , int j){
    if(i==j){
        cout << "M" << i+1 ;
    }
    else{
        cout << "("  ;
        printer(i , pos[i][j]);
        cout << ")"  ;
        cout << "("  ;
        printer(pos[i][j]+1 , j);
        cout << ")" ;
    }
}

int main(void){
    int n ;
    cout << "how many matrices : " ;
    cin >> n ;
    vector<int>p(n+1) ;
    for(int i=0 ; i<=n ; i++){
        cout << "dimension " << i << " is : " ;
        cin >> p[i] ;
    }
    cost.assign(n , vector<int>(n , INT_MAX));
    pos.assign(n , vector<int>(n , -1));
    for(int i=0  ; i<n  ; i++ ){
        cost[i][i] = 0 ;
    }
    int len = 2 ;
    while(len<=n){
        for(int i=0 ; i<n-len+1 ; i++){
            int j = i+len-1 ;
            for(int k=i ; k<j ; k++){
                int x = cost[i][k] + cost[k+1][j] + (p[i]*p[k+1]*p[j+1]) ;
                if(x < cost[i][j]){
                    cost[i][j] = x ;
                    pos[i][j] = k ;
                }
            }
        }
        len++ ;
    }
    cout << "the optimal total cost for multiplication is : " << cost[0][n-1] << endl ;
    printer(0 , n-1);
    cout << endl ;
    return 0 ;
}