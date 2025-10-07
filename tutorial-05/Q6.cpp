#include<iostream>
#include <vector>
using namespace std ;


int main() {
    int n;
    cout << "Enter number of keys: ";
    cin >> n;
    vector<double> p(n);
    cout << "Enter probabilities: ";
    for(int i = 0; i < n; i++) cin >> p[i];
    //Precompute cumulative sums (probability table)
    vector<double> sum(n+1, 0);
    for(int i = 0; i < n; i++) {
        sum[i+1] = sum[i] + p[i];
    }
    // Build DP table
    vector<vector<double>> dp(n, vector<double>(n, 0));
    for(int l = 0; l < n; l++) {      
        for(int i = 0; i+l< n; i++) {
            int j =i+l;
            dp[i][j] =INT_MAX;
            for(int r = i; r <= j; r++) {
                double left = (r > i ? dp[i][r-1] : 0) ;
                double right = (r < j ? dp[r+1][j] : 0) ;
                dp[i][j] = min(dp[i][j], left + right + (sum[j+1] - sum[i]));
            }
        }
    }
    cout << "Minimum expected search cost = " << dp[0][n-1] << endl;
    return 0 ;
}


// this is a inferior version of the OBST with out the dummy varibles 
//its recurrence relation is 

//dp[i][j] = min (dp[i , r-1] + dp[r+1 , j] + p[i->j]) for all r i->j