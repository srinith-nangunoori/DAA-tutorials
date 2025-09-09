#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    int n;
    cout << "Enter number of licenses: ";
    cin >> n;
    vector<pair<double,int>> licenses(n); 
    cout << "Enter the growth rate (rj) of each license:\n";
    for(int i = 0; i < n; i++) {
        cin >> licenses[i].first;
        licenses[i].second = i + 1; 
    }
    sort(licenses.rbegin(), licenses.rend());
    cout << "\nPurchase order to minimize total cost:\n";
    for(auto &license : licenses) {
        cout << "License " << license.second << " with growth rate " << license.first << endl;
    }
    double total_cost = 0;
    double base_price = 1000;
    for(int month = 0; month < n; month++) {
        total_cost += base_price * pow(licenses[month].first, month);
    }
    cout << "\nTotal cost = " << total_cost << endl;
    return 0;
}
// main idea :
/* just sort in reverse order and just buy accordingly as we must buy the fastest increasing license 
earlier to minimize cost */ 