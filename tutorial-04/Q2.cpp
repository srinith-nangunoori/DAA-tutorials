#include <iostream> 
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

int main(void){
    int n; 
    cout << "how many jobs are available : " ;
    cin >> n;
    vector<pair<int,int>> jobs;
    int tempd = 0 ;
    int maxd = 0 ;
    int tempp = 0 ;
    for(int i=0 ; i<n ; i++) {
        cout << "what is the deadline of job " << i+1 << " : " ;
        cin >> tempd ;
        cout << "what is the profit for job " << i+1 << " : " ;
        cin >> tempp;
        jobs.push_back({tempd, tempp});
        if(tempd > maxd){
            maxd = tempd ;
        }
    }
    sort(jobs.begin() , jobs.end() ,
        [](const pair<int , int>&a ,  const pair<int , int>&b){
            return a.second > b.second;
        });
    set<int>available ;
    for(int i=1 ; i<= maxd ; i++){
        available.insert(i) ;
    }
    int profit = 0 ;
    vector<int>schedule(maxd,-1);
    for(int i=0 ; i<n && available.size()>0  ; i++){
        if(schedule[(jobs[i].first)-1]==-1){
            schedule[(jobs[i].first)-1] = jobs[i].second ;
            profit += jobs[i].second ;
            available.erase(jobs[i].first);
        }
        else{
            auto it = available.lower_bound((jobs[i].first));// gives the first element greater than or equal to this one
            if(it != available.begin()){
                it-- ;
                int slot = *it ;
                schedule[slot-1] = jobs[i].second;
                profit += jobs[i].second ;
                available.erase(it);
            }
        }
    }
    cout << "the maximum profit which can be attained is : " << profit << endl ;
    cout << "the schedule used to acheive this is : " << endl ;
    for(int i=0 ; i<maxd ; i++){
        cout << i+1 << " ---- " ;
        if(schedule[i]== -1 ){
            cout << "no job alloted" << endl ;
        }
        else{
            cout << schedule[i] << endl ;
        }
    }
    return 0 ;
}

// my main idea :
/* I sort the jobs by profit and then iterate through them and add them to each dead line if that point 
is free and if it is not free then I do a binary search on the available slots to find the slot which is 
available and just below the dead line for that work and accordingly place it */