#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

vector<pair<int,int>> points;
vector<pair<int,int>> ans;

double perpendicularDistance(pair<int,int>& left, pair<int,int>& right, pair<int,int>& p, char dir) {
    long long orient = (right.first - left.first) * (p.second - left.second)
                     - (right.second - left.second) * (p.first - left.first);// this is the 2-D cross product check for point position wrt line

    bool valid = (dir == 'U') ? (orient > 0) : (orient < 0);
    if (!valid) return 0;

    double num = fabs((right.second - left.second) * p.first 
                    - (right.first - left.first) * p.second 
                    + right.first * left.second 
                    - right.second * left.first);
    double den = hypot(right.second - left.second, right.first - left.first);
    return num / den;
}

void recursive(int l, int r, char dir) {
    if (l == r) return;

    double maxd = 0;
    int index = -1;

    for (int i = l + 1; i < r; i++) {
        double temp = perpendicularDistance(points[l], points[r], points[i], dir);
        if (temp > maxd) {
            maxd = temp;
            index = i;
        }
    }

    if (index != -1) {
        ans.push_back(points[index]);
        recursive(l, index, dir);
        recursive(index, r, dir);
    }
}

int main() {
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
    ans.reserve(n);
    ans.push_back(points.front());
    ans.push_back(points.back());

    recursive(0, points.size() - 1, 'U');
    recursive(0, points.size() - 1, 'D');

    // Remove duplicates
    sort(ans.begin(), ans.end());
    ans.erase(unique(ans.begin(), ans.end()), ans.end());

    // Sort counter-clockwise using centroid
    double cx = 0, cy = 0;
    for (auto &p : ans) {
        cx += p.first;
        cy += p.second;
    }
    cx /= ans.size();
    cy /= ans.size();

    sort(ans.begin(), ans.end(), [cx, cy](auto &a, auto &b) {
        return atan2(a.second - cy, a.first - cx) < atan2(b.second - cy, b.first - cx);
    });

    for (auto &p : ans) {
        cout << p.first << " " << p.second << "\n";
    }

    return 0;
}