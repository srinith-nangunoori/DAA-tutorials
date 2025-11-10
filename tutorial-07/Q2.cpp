#include <iostream>
using namespace std ;
vector<int > nums ;
int minimum = INT_MAX ; 
vector<int>s1 ;
vector<int>s2 ;

void recursion(vector<int>&x1 , vector<int>&x2 , int sum1 , int sum2 , int i ){
    if(i==nums.size()){
        if(abs(sum1 - sum2) < minimum){
            s1 = x1 ;
            s2 = x2 ;
            minimum = abs(sum1 - sum2) ;
        }
        return ;
    }
    x1.push_back(nums[i]);                      //
    sum1+= nums[i] ;                            //
    recursion( x1 , x2 , sum1 , sum2 , i+1 );   //
    x1.pop_back();                              //
    sum1-= nums[i] ;                            //main point of backtracking 
    x2.push_back(nums[i]);                      //
    sum2+= nums[i] ;                            //
    recursion( x1 , x2 , sum1 , sum2 , i+1 );   //
    x2.pop_back();                              //
    sum2-= nums[i] ;                            //
    return ;
}

int main(){
    int n =0 ; 
    cout << "how many numbers ? : " ;
    cin >> n ;
    cout << "give the integers one by one : " << endl ;
    int temp = 0 ;
    for(int i=0 ; i<n ; i++){
        cin >> temp ;
        nums.push_back(temp) ;
    }
    int sum1 = 0 ;
    int sum2 = 0 ;
    int i = 0 ;
    vector<int>x1 ;
    vector<int>x2 ;
    recursion( x1 , x2 , sum1 , sum2 , i) ;
    cout << "the minimum difference is : " << minimum << endl ;
    for(int i=0 ; i<s1.size() ; i++){
        cout << s1[i] << " " ;
    }
    cout << endl ;
    for(int i=0 ; i<s2.size() ; i++){
        cout << s2[i] << " " ;
    }
    cout << endl ;
    return 0 ;
}