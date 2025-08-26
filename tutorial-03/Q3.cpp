#include <iostream> 
using namespace std ;
vector<int> vec ;
int k = 0 ;

int quicksort(int l , int r ){
    int pivot = vec[l] ; 
    int i = l+1 ;
    int j = r ;
    int mid = 0 ;
    while(true){
        while(i<j && vec[i]<=pivot ){
            i++ ;
        }
        while(j>i && vec[j]>pivot){
            j-- ;
        }
        if(i!=j){
            swap(vec[i] , vec[j]);
            if(j-i >1){
                i++ ;
                j-- ;       
            }
            else{
                i = j ;
            }
        }
        else{
            if(vec[i]>=pivot){
                swap(vec[i-1] , vec[l]);
                mid = i-1 ;
            }
            else{
                swap(vec[i] , vec[l]);
                mid = i ;
            }
            break ;
        }
    }
    return mid ;
}

void divideforsort(int l , int r){
    if(l<r){
        int mid = quicksort(l , r);
        if(mid == k-1){
            return ;
        }
        divideforsort(l , mid-1);
        divideforsort(mid+1 , r);
    }
}

int main(void){
    int n= 0 ;
    cout << "how many elements in the array : " ;
    cin >> n ;
    int x =0 ;
    cout << "what are the elements of the array : "  << endl ;
    for(int i=0 ; i<n ; i++){
        cin >> x ; 
        vec.push_back(x);
    }
    cout << "value of k for the kth smallest number : ";
    cin >> k ;
    divideforsort( 0 , n-1);
    cout << "the kth smallest number in the array is : " << vec[k-1]<< endl ; 
    return 0 ;
}
