#include <iostream>
using namespace std ;

int main(){
    int floors =0 ;
    int eggs = 0 ;
    cout << "how many floors : " ;
    cin >> floors ;
    cout << "how many eggs available : " ;
    cin >> eggs ;
    int max_moves = floors ; 
    vector<vector<int>> dp(max_moves+1, vector<int>(eggs+1, 0));
    for(int i=0 ; i<max_moves+1 ; i++){
        dp[i][0] = 0 ;
        dp[i][1] = i ;
    }
    for(int i=0 ; i < eggs+1 ; i++){
        dp[0][i] = 0 ;
        if (i>0) dp[1][i] = 1 ;
    }
    for(int i=2 ; i<max_moves+1 ; i++ ){
        for(int j=2 ; j<eggs+1 ; j++){
            dp[i][j] = dp[i-1][j]+dp[i-1][j-1]+1 ;
        }
        if(dp[i][eggs]>=floors){
            cout << "the number of moves required are : " << i << endl ;
            return 0 ;
        }
    }
    return 0 ;
}

// the main idea here is not to count the moves according to the floors but the opposite 
// we find the maximum floors which can be covered by particular number of moves and eggs 
/* the basic idea is if we have t moves which we can make then the floors which could be
    covered with 2 eggs would be t + t-1 + t-2 + t-3 + ...  as at every check the number 
    moves availble will decrease by one and for example of at the t floor the first egg 
    breaks the we will require t-1 linear steps so that will automatically sum up to t max
    moves ( this is the main logic)*/

// now comming to the recurrence relation 

// dp[m][k] = dp[m-1][k-1] + dp[m-1][k] + 1
//              broke     did not break
// dp[m-1][k] : floors that can be checked if the egg doesn't break, m-1 as the number of moves decreased , k eggs remaining 
// dp[m-1][k-1] : floors that can be checked if the egg breaks, m-1 as the number of moves decreased , k-1 eggs remaining 
// +1 for the current floor being tested


