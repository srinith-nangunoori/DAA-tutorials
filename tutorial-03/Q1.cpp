#include <iostream>
#include <vector>
using namespace std ;
int ans =0 ;
vector<int>temp ;

void merger( int s , int mid , int e ){
    vector<int>part1 ;
    vector<int>part2 ;
    for(int i=s ; i<=mid; i++){
        part1.push_back(temp[i]);
    }
    for(int i=mid+1 ; i<=e; i++){
        part2.push_back(temp[i]);
    }
    int i=0 ; 
    int j = 0 ;
    int x = 0 ;
    while(i<part1.size() && j<part2.size()){
        if(part1[i] <= part2[j]){
            temp[s+x]=(part1[i]);
            x++ ;
            i++ ;
        }
        else{
            temp[s+x]=(part2[j]);
            x++ ;
            j++ ;
            ans += (part1.size() - i); // this is the point where the inversions are calculated ,
            //    it actually counts the number of elements present after i which is greater than the element
            //    in the j , as all the elements after that i will also be greater than i and all 
            //    those will be counted as inversions 
        }
    }
    while(i<part1.size()){
        temp[s+x]=(part1[i]);
        i++ ;
        x++ ;
    }
    while(j<part2.size()){
        temp[s+x]=(part2[j]);
        j++ ;
        x++ ;
    }
}

void mergesort( int s , int e){
    if(s<e){
        int mid = s +(e-s)/2 ;
        mergesort( s , mid);
        mergesort( mid+1 , e);
        merger( s , mid, e) ;
    }
}

int main(){
    int n;
    cout << "number of elements in the array are : " ;
    cin >> n;
    temp.resize(n);
    cout << "Input the values for the array: " << endl;
    for (int i = 0; i < n; i++) {
        cin >> temp[i];
    }
    mergesort( 0 , n-1);
    cout << "number of inversions : "<<ans << endl ;
    return 0 ;
}

