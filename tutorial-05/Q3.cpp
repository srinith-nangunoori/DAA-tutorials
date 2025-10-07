#include <iostream>
using namespace std ;

bool PalCheck(string X) {
    int i = 0, j = X.length() - 1;
    while(i < j) {
        if(X[i] != X[j])
            return false;
        i++;
        j--;
    }
    return true;
}

int main(){
    int n=0 ; 
    cout << "how many number of letters in the string S : " ;
    cin >> n ;
    string S ;
    char temp ;
    cout << "S is : " << endl ;
    for(int i=0 ; i< n ; i++){
        cin >> temp ;
        S.push_back(temp) ;
    }
    vector<int>dp(n , INT_MAX);
    dp[0] = 0 ;
    vector<vector<bool>> ispal(n, vector<bool>(n));
    for(int i=0 ; i<n ; i++){
        for(int j=i ; j<n ; j++){
            ispal[i][j] = PalCheck(S.substr(i,j-i+1)) ;
        }
    }

    for(int j=0 ; j<n ; j++){
        if(ispal[0][j]) dp[j] = 0 ;
        for(int i=0 ; i<=j ; i++){
            if(ispal[i][j]){
                if(dp[i-1]+1 < dp[j]){
                    dp[j] = dp[i-1]+1 ;
                }
            }
        }
    }
    cout << "minimum number of cuts are : " << dp[n-1] << endl ;
    return 0 ;
}


/*actually my main idea was quite similar to the matrix multiplication question (reasoning written below)*/

/* just find all the possible palindromes in the given string (step 1) this is not related to dp */
/* now my idea was to create a 2D table which checked every possible i , j for its least number of cuts just like in 
    matrtix multiplication we set length and then build the whole pyramid */
/* this way is visually more soothing and easier to understand and the recurrence relation would be */

//              {   0           ,if sub string i,j is palindrome
//cuts[i , j] = |
//              {  min(cuts[i , k] + cuts[k+1 , j] + 1 ) (for all k i->j)   ,if not palindrome

// SIMPLE AND EASY BUT O(n^3) , 2D DP


// but we can optimize this into 1D DP 
/* the main idea here is for a partcular point dp[j] all it depends up on is dp[i] where i->j is a palindrome 
    so we just have to iterate over all possible i form 0 to j and check if that i->j is palindrom and find min cuts 
    for that dp[j]*/

//              {   0           ,if sub string 0,j is palindrome
//    dp[j] =   |
//              {  min(dp[i] + 1 ) (for all i  0->j)   ,if i,j is not a palindrome

// this is done in O(n^2) , 1D DP

