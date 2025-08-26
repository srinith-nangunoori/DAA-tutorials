#include <iostream> 
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std ;
vector<pair<int,int>>points ;
vector<pair<int,int>>ans ;

double perpendicularDistanceUp(pair<int,int> left, pair<int,int> right, pair<int,int> p) {
    if(p.second > left.second || p.second > right.second){
        double num = fabs((right.second - left.second) * p.first 
                        - (right.first - left.first) * p.second 
                        + right.first * left.second 
                        - right.second * left.first);
        double den = sqrt(pow(right.second - left.second, 2) 
                        + pow(right.first - left.first, 2));
        return num / den;
    }
    else{
        return 0 ;
    }
}
double perpendicularDistanceDown(pair<int,int> left, pair<int,int> right, pair<int,int> p) {
    if(p.second < left.second || p.second < right.second){
        double num = fabs((right.second - left.second) * p.first 
                        - (right.first - left.first) * p.second 
                        + right.first * left.second 
                        - right.second * left.first);
        double den = sqrt(pow(right.second - left.second, 2) 
                        + pow(right.first - left.first, 2));
        return num / den;
    }
    else{
        return 0 ;
    }
}

void recursive (int l , int r , char dir ){
    if (l == r ){   
        return ;
    }
    double maxd = 0 ;
    double temp = 0 ;
    int index = 0 ;
    for(int i = l+1 ; i<r ; i++){
        if(dir == 'U'){
            temp = perpendicularDistanceUp(points[l], points[r], points[i]);
        }
        else{
            temp = perpendicularDistanceDown(points[l], points[r], points[i]);
        }
        if(temp > maxd){
            maxd = temp ; 
            index = i ;
        }
    }
    if(maxd != 0){
        ans.push_back(points[index]);
        recursive(l , index , dir);
        recursive(index , r , dir);
    }
}

int main(void){
    int n ;
    cout << "what are the number of points : " ;
    cin >> n ;
    if (n < 2) {
        cout << "Need at least 2 points.\n";
        return 0;
    }
    int x =0 ; 
    int y=0 ;
    for(int i=0 ; i<n ; i++){
        cout << "what is the x-cord for the " << i+1 <<" point : " ;
        cin >> x ;
        cout << "what is the y-cord for the " << i+1 <<" point : " ;
        cin >> y ;
        points.push_back({x , y});
    }
    sort(points.begin(), points.end());
    ans.push_back(points[0]);
    ans.push_back(points[points.size()-1]);
    recursive(0 , points.size()-1 , 'U') ;
    recursive(0 , points.size()-1 , 'D') ;

    // sorting with the centroid so that the convex hull is printed in the counter clock wise order 
    double cx = 0, cy = 0;
    for (auto &p : ans) {
        cx += p.first;
        cy += p.second;
    }
    cx /= ans.size();
    cy /= ans.size();
    sort(ans.begin(), ans.end(), [cx, cy](pair<int,int> a, pair<int,int> b) {
        double angA = atan2(a.second - cy, a.first - cx);
        double angB = atan2(b.second - cy, b.first - cx);
        return angA < angB;
    });
    cout << "the convex hull in counter clockwise direction" << endl ;
    for(auto &p : ans){
        cout << p.first << "," << p.second << endl ;
    }
    return 0 ;
}