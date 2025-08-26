#include <iostream> 
#include <vector>
using namespace std ;
vector<int>vec ;

int BinarySearch(int l , int r ){
    if(l<=r){
        int mid = l+ (r-l)/2 ;
        if(mid ==0){
            if(vec[mid] >= vec[mid+1]){
                return mid ;
            }
            else{
                return BinarySearch(mid+1 , r);
            }
        }
        else if(mid == vec.size()-1){
            if(vec[mid] >= vec[mid-1]){
                return mid ;
            }
            else{
                return BinarySearch(l , mid-1);
            }
        }
        else{
            if(vec[mid] >= vec[mid-1] && vec[mid] >= vec[mid+1] ){
                return mid ;
            }
            else{
                if(vec[mid] <= vec[mid-1]){
                    return BinarySearch(l , mid-1);
                }
                else{
                    return BinarySearch(mid+1 , r );
                }
            }
        }
    }
    return -1 ;
}

/* this process might look like magic at first but think , all this does is , check an element , if the element is lesser than 
any one of its neighbours or both then just move check that half side of the array whose value was greater than the mid then you will 
directly land on answer at one point.
    assume (....... , P , Q , ...)if P is less than Q then we move to Q then check the same thing 
now the 2 options are either 
1) next element may be smaller , directly answers acheived 
2) next element may be greater then we move forward again until 
    i) the end of array which gives the answer as at the end we will only check the previous element 
    ii) a decreasing element , so that point would become the answer  */

int main(void){
    int n= 0 ;
    int ans = -1 ;
    cout << "how many elements in the array : " ;
    cin >> n ;
    int x = 0 ;
    for(int i=0 ; i<n ; i++){
        cin >> x ;
        vec.push_back( x );
    }
    ans = BinarySearch(0 , n-1);
    if(ans == -1){
        cout << "there is no Peak Index"  << endl ;
    }
    else{
        cout << "A Peak Index is : " << ans << endl ;
    }
    return 0;
}

