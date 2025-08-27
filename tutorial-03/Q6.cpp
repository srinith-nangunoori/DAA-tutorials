#include <iostream>
#include <vector>
using namespace std ;

int main(void) {
    vector<pair<int , int>> ans ;
    vector<vector<int>> buildings;
    int n = 0;
    cout << "How many buildings are there: ";
    cin >> n;
    int minx = INT_MAX ;
    int maxx = INT_MIN ;
    if (n > 0) {
        cout << "Enter the Left-coordinate, Right-coordinate, and Height for each building:" << endl;
        for (int i = 0; i < n; ++i) {
            int left, right, height;
            cout << "Building " << i + 1 << ": ";
            cin >> left >> right >> height;
            if(left < minx){
                minx = left ;
            }
            if(right >maxx){
                maxx = right ;
            }
            buildings.push_back({left, right, height});
        }
    }
    vector<vector<int>> vec(maxx+2) ;
    vector<int> maxvec(maxx+2) ;
    for(int i=0 ; i<n ; i++){
        vec[buildings[i][0]].push_back(buildings[i][2]);
        vec[buildings[i][1]].push_back(-buildings[i][2]);
    }
    priority_queue<int> maxHeap;
    unordered_map<int , int> map ;
    for(int i=0 ; i<vec.size() ; i++){
        if(vec[i].size()==0){
            if(maxHeap.size()!=0){
                maxvec[i] = maxHeap.top();
            }
        }
        else {
            for(int j=0 ; j<vec[i].size() ; j++){
                if(vec[i][j]>0){
                    maxHeap.push(vec[i][j]);
                    map[vec[i][j]]++ ;
                }
                else{
                    map[-vec[i][j]]-- ;
                }
            }
            while(maxHeap.size() > 0 && map[maxHeap.top()]==0){
                maxHeap.pop();
            }
            if(maxHeap.size()>0){
                maxvec[i] = maxHeap.top() ;
            }
            else{
                maxvec[i] = 0;
            }
        }
    }
    int temp = maxvec[0] ;
    for(int i=0 ;i<vec.size() ; i++){
        if(maxvec[i]!= temp){
            ans.push_back({i , maxvec[i]});
        }
        temp = maxvec[i] ;
    }
    cout << "the skyline is : " << endl ;
    for(int i=0 ; i<ans.size() ; i++){
        cout << ans[i].first << "," << ans[i].second << endl ;
    }
    return 0;
}