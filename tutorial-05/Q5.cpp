#include <iostream>
using namespace std ;

int main(){
    int n = 0 ;
    cout << "what is the length of the rod : ";
    cin >> n ;
    vector<int> dp ;
    int temp = 0 ;
    cout << "what are the prices of rod pieces : " << endl ;
    for(int i=0 ; i<n ; i++){
        cin >> temp ;
        dp.push_back(temp);
    }
    for(int i=1 ; i<n ; i++){
        for(int j=0 ; j<=i/2 ; j++){
            temp = dp[j]+dp[i-j-1];
            if(dp[i]<temp){
                dp[i] = temp ;
            }
        }
    }
    cout << "the maximum profit is : " << dp[n-1] << endl ;
    return 0 ;
}

// so this was based on my idea of checking for optimal cut with usage of lower optimal answers 

/* my idea is we just check all the single cut possibilities in the whole length , and use dp[] values for the 
individual values during the checks which will take care of inner cuts and finally check if the whole thing is 
greater than the single value of the whole rod */

// dp[i] = max ( dp[i] , max(dp[j]+dp[i-j-1] for all j 0->i/2 ) );


