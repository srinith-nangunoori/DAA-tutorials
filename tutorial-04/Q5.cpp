#include<iostream>
#include<vector>
#include<algorithm>
using namespace std ;

int main(void){
    int n=0 ; 
    int tank  =0 ;
    int desti = 0 ;
    cout << "what is the size of the tank : " ;
    cin >> tank;
    cout << "what is the destination point : " ;
    cin >> desti ;
    cout << "how many points for petrol : " ;
    cin >> n ;
    vector<int>points ;
    cout << "please input the petrol points one by one : " << endl ;
    int temp = 0 ;
    for(int i=0 ; i< n ; i++){
        cin >> temp ;
        points.push_back(temp);
    }
    sort(points.begin() ,points.end());
    int reach = tank ;
    if(reach < points[0]){
        cout << "the destination cannot be reached" << endl ;
        return 0 ;
    }
    vector<int> fillings;
    int i=0; 
    while(reach < desti){
        while(i<points.size() && points[i]<=reach){
            i++ ;
        }
        i-- ;
        if(points[i] <=reach-tank){
            cout << "the destination cannot be reached" << endl ;
            return 0 ;
        }
        fillings.push_back(points[i]);
        reach = points[i]+tank ;
    }
    if(reach < desti){
        cout << "the destination cannot be reached" << endl ;
        return 0 ;
    }
    if(fillings.size()==0){
        cout << "no stops required " << endl ;
        return 0 ;
    }
    cout << "the least number of points to fill petrol are : " << fillings.size() << endl ;
    cout << "so the points where petrol must be filled are : "<< endl ;
    for(int i=0 ; i<fillings.size() ; i++){
        cout << fillings[i] << endl;
    }
    return 0 ;
}


// main logic :
/* only to fill the tank at the farthest point where the vehicle could reach */