#include <iostream>
#include <vector>
#include <algorithm>
using namespace std ;

int main(void){
    vector<pair<int , int>> items ;
    int W = 0 ;
    int n =0 ;
    cout << "how many items are available : " ;
    cin >> n ;
    int tempv =0 ;
    int tempw = 0 ;
    for(int i=0 ; i<n ; i++){
        cout << "what is the value of item " << i+1 << " : " ;
        cin >> tempv ;
        cout << "what is the weight of item " << i+1 << " : " ;
        cin >> tempw ;
        items.push_back({tempv , tempw});
    }
    cout << "what is weight that the kanpsack can hold : " ;
    cin >> W ;
    vector<pair<float , int>>greedypriority ;
    for(int i=0 ; i<n ; i++){
        greedypriority.push_back({( (float)items[i].first/items[i].second ) , i});
    }
    sort(greedypriority.begin(), greedypriority.end(),
     [](const pair<float,int>& a, const pair<float,int>& b) {
         return a.first > b.first; 
     });
    float profit = 0 ;
    int e_space = W ;
    for(int i=0 ; i<n && e_space>0 ; i++){
        if(e_space >= items[greedypriority[i].second].second){
            profit += items[greedypriority[i].second].first ;
            e_space -= items[greedypriority[i].second].second ;
        }
        else{
            profit += items[greedypriority[i].second].first *( (float)e_space / items[greedypriority[i].second].second) ;
            e_space = 0 ;
        }
    }
    cout << "the maximum profit that can be acheived is : " << profit << endl ;
    return 0 ;
}