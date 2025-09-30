#include <iostream> 
#include <vector>
#include <climits>
#include <algorithm>
using namespace std ;

vector<vector<int>>cost ;

int main(){
    int m =0 ;
    int n = 0 ; 
    cout << "what is the length of the string A : " ;
    cin >> m ; 
    cout << "what is the length of the string B : " ;
    cin >> n ;
    cost.assign(m+1 , vector<int>(n+1 ));
    cout << "what are the characters in A : " << endl ;
    vector<char> A(m);
    for(int i=0; i<m; i++){
        cin >> A[i];
    }
    cout << "what are the characters in B : " << endl ;
    vector<char> B(n);
    for(int i=0; i<n; i++){
        cin >> B[i];
    }
    for(int i=0 ; i<n+1 ; i++){
        cost[0][i] = i ;
    }
    for(int i=0 ; i<m+1 ; i++){
        cost[i][0] = i ;
    }
    for(int i=1 ; i<m+1 ; i++){
        for(int j=1 ; j< n+1 ; j++){
            if(A[i-1] == B[j-1]){
                cost[i][j] = cost[i-1][j-1];
            }            
            else{
                cost[i][j] = 1+  min(cost[i-1][j-1], min(cost[i-1][j], cost[i][j-1]));
            }
        }
    }
    cout << "the total number of operations required to be made is : " << cost[m][n] << endl ;
    return 0 ;
}

// the main idea :

// a thing to remember (operations done on A[0....i-1] , B[0.....j-1] , A is turned to B ):

/* if substitution done then the optimal operations would be cost for A[0...i-2] , B[0....j-2] then +1 ,
    as after substitute you make the A[i-1] and B[j-1] equal ,minimal cost for converting the left portion
    is cost for A[0.....i-2] , B[0...j-2] */
/* if deletion done then the optimal operation would be cost for A[0.....i-2] , B[0...j-1] then +1 ,
    as after deleting , minimal cost for converting the left portion is cost for A[0.....i-2] , B[0...j-1] */
/* if insertion done then the optimal operation would be cost for A[0....i-1] , B[0...j-2] then +1 ,
    as after inserting (we equate inserted element with B[j-1]), minimal cost for converting left portion 
    is cost for A[0....i-1] , B[0...j-2] */

// note : in my code cost for optimal conversion A[0...i-1] , B[0...j-1] is shown by cost[i , j]

// recurrence relation :

//                  {   i                   if j==0 
//                  |   j                   if i==0 
//  cost[i , j] =   |   cost[i-1][j-1]      if A[i-1] == B[i-1]
//                  {   1+min (cost[i-1][j-1] + cost[i][j-1] + cost[i-1][j])  if A[i-1] != B[j-1]
//                              substitution      inserion       deletion