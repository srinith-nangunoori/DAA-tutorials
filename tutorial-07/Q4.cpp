#include <iostream>
using namespace std ;
vector<vector<int>>ans ;
vector<int> nums ;

void recursion (vector<int>&x , int i ,  int sum , int target , int rem_sum  ){
    if(i == nums.size()){
        return ;
    }
    if(sum == target) {
        ans.push_back(x) ;
    }
    else if(sum > target || sum + rem_sum < target){
        return ;
    }
    else{
        rem_sum -= nums[i] ; 
        recursion(x , i+1 , sum , target , rem_sum) ;   //
        x.push_back(nums[i]) ;                          //
        sum += nums[i] ;                                // main point of back tracking 
        recursion(x , i+1 , sum , target , rem_sum) ;   //
        x.pop_back() ;                                  //
        sum -= nums[i] ;                                //
    }
}

int main(){
    int n =0 ; 
    cout << "how many numbers in the set ?(unique) : " ;
    cin >> n ;
    cout << "give the integers one by one : " << endl ;
    int temp = 0 ;
    int sum = 0 ;
    int rem_sum = 0 ;
    for(int i=0 ; i<n ; i++){
        cin >> temp ;
        rem_sum += temp ;
        nums.push_back(temp) ;
    }
    int target = 0 ;
    cout << "what is the target : " ;
    cin >> target ;
    vector<int>x ;
    recursion( x , 0 ,  sum , target ,  rem_sum) ;
    for(int i=0 ; i<ans.size() ; i++){
        for(int j=0 ; j<ans[i].size() ; j++){
            cout << ans[i][j] << " " ;
        }
        cout << endl ;
    }
    return 0 ;
}

// this question is done in such a way that , for each value we either take the value
// or we just skip the value and accordingly update and do recursion 