#include <iostream> 
#include <vector> 
#include <algorithm> 
using namespace std ;

int main(void){
    int n= 0; 
    cout << "how many houses are in the street : " ;
    cin >> n ;
    vector<int> houses ;
    queue <int> checking ;
    int temp = 0 ;
    // assuming houses start at 1 
    cout << "please input the houses one by one : " << endl ;
    for(int i=0 ; i<n ; i++){
        cin >> temp ;
        houses.push_back(temp);
        checking.push(temp);
    }
    sort(houses.begin() , houses.end());
    vector<int> towers ;
    temp = 0 ;
    while(checking.size()){
        if(temp < checking.front()){
            towers.push_back(checking.front()+4);
            temp = checking.front()+8 ;
        }
        checking.pop();
    }
    cout << "so the least number of towers required are : " << towers.size() << endl ;
    cout << "the tower positions are : " << endl ;
    for(int i=0 ; i<towers.size() ; i++){
        cout << towers[i] << endl ;
    }
    return 0 ;
}

// my logic :
/* all I did was every time i got a house which was not covered i just put a tower 4 miles away to the right
of that house and continued that logic until all the houses are covered*/