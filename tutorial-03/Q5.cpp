#include <iostream>
#include <vector>
#include <algorithm>
using namespace std ;

vector<int> vec ;

void DualQuickSort(int l , int r){
    if (l >= r) return;
    int p1 = vec[l];
    int p2 = vec[r];
    if(p1>p2){
        swap(vec[l],vec[r]);
        swap(p1,p2);
    }
    //process is taking 2 pivot values and 2 bounding indexes to bring out 3 portions in the vector 
    int leftB = l+1 ;
    int rightB = r-1 ; 
    int i=l+1 ;
    while(i<=rightB){
        if(vec[i]<p1){// maintaining the lower limit (LowerB) inside which all are less than p1
            swap(vec[leftB],vec[i]) ;
            leftB++ ;
            i++ ;
        }
        else if(vec[i]>p2){// maintaining the upper limit(RightB) outside which all are greater than p2 
            swap(vec[i], vec[rightB]);
            rightB-- ;
        }
        else{
            i++ ;
        }
    }
    // as they will enter the mid area , we shift them to the start of their territory 
    leftB--;
    rightB++;
    swap(vec[l],vec[leftB]);
    swap(vec[r],vec[rightB]);
    DualQuickSort(l , leftB-1);
    DualQuickSort(leftB+1 , rightB-1);
    DualQuickSort(rightB+1 , r);
}

int main (void){
    int n =0 ;
    cout << "how many elements are in the array : " ;
    cin >> n ;
    cout << "what are the elements in the array : " << endl;
    int x = 0 ;
    for(int i=0; i<n ; i++){
        cin >> x ;
        vec.push_back(x) ;
    }
    DualQuickSort(0, n-1) ;
    cout << "finally the vector becomes : " << endl ;
    for(int i=0 ; i<n ; i++){
        cout << vec[i] << endl ; 
    }
    return 0 ;
}
