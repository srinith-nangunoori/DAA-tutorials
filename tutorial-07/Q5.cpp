#include<iostream>
using namespace std ;

class node {
public: 
    int level ;
    int current_weight ;
    int current_profit ; 
    int bound ;
    vector<int>path ;
    node(int l , int c_w , int c_p , int b , vector<int>p){
        level = l ;
        current_weight = c_w ;
        current_profit = c_p ;
        bound = b ;
        path = p ;
    }
};

// this is custom function which i had to use as i chose to use class and objects 
struct cmp {
    bool operator()(node* a, node* b) {
        return a->bound < b->bound;  
        // true means "a has lower priority than b"
        // So pq will pop the node with the largest bound
    }
};

int main(){
    int c =0 ;
    cout << "what is the capacity : " ;
    cin >> c ;
    int n=0  ;
    cout << "how many number of items : " ;
    cin >> n ;
    vector<pair<int , int>> items;
    int a = 0 ;
    int b =0 ; 
    for(int i=0 ; i<n ; i++){
        cin >> a ;
        cin >> b ;
        items.push_back({a, b});
    }  

    // sorting in the reverse order 
    sort(items.begin(), items.end(), [](const pair<int,int>& a, const pair<int,int>& b){
        double r1 = (double)a.first / a.second;
        double r2 = (double)b.first / b.second;
        return r1 > r2;   
    });

    // calculating branchbound for zero node 
    a = 0 ;
    b = c ; 
    for(int i=0 ; i<n && b>0 ; i++){
        if(items[i].second <= b){
            a += items[i].first ;
            b -= items[i].second ;
        }
        else{
            a += (double)items[i].first / items[i].second * b;
            b = 0 ;
        }
    }

    int total_nodes = 0 ;
    int pruned_nodes = 0 ;
    node * n1 = new node(0 , 0 , 0 , a , {});
    priority_queue<node*, vector<node*>, cmp> pq;
    pq.push(n1) ;
    total_nodes++ ;
    int max = INT_MIN ;
    vector<int> maxpath ;
    while(pq.size()){
        node* temp = pq.top();
        if(temp->current_profit > max){
            max = temp->current_profit ;
            maxpath = temp->path ;
        }
        pq.pop();
        int tlev = temp->level  ;
        if(tlev == n) continue ;
        //included child
        total_nodes++ ;
        int temppro = temp->current_profit + items[tlev].first ;
        int tempwei = temp->current_weight + items[tlev].second ;
        int tempbou = temppro ;
        vector<int> x ;
        if(tempwei <= c){
            int tempc = c-tempwei ;
            for(int i=tlev+1 ; i<n && tempc>0 ; i++){
                if(items[i].second <= tempc){
                    tempbou += items[i].first ;
                    tempc -= items[i].second ;
                }
                else{
                    tempbou += (double)items[i].first / items[i].second * tempc; // using fractional knapsack logic for upperbound 
                    tempc = 0 ;
                }
            }
            if(tempbou >= max){
                x = temp->path ;
                x.push_back(tlev) ;
                node * t1 = new node(tlev+1 , tempwei , temppro , tempbou , x) ;
                pq.push(t1) ;
            }
            else{
                pruned_nodes++ ;
            }
        }
        //excluded child
        total_nodes++ ;
        temppro = temp->current_profit  ;
        tempwei = temp->current_weight  ;
        tempbou = temppro ;
        if(tempwei <= c){
            int tempc = c-tempwei ;
            for(int i=tlev+1 ; i<n && tempc>0 ; i++){
                if(items[i].second <= tempc){
                    tempbou += items[i].first ;
                    tempc -= items[i].second ;
                }
                else{
                    tempbou += (double)items[i].first / items[i].second * tempc; 
                    tempc = 0 ;
                }
            }
            if(tempbou >= max){
                node * t1 = new node(tlev+1 , tempwei , temppro , tempbou , temp->path) ;
                pq.push(t1) ;
            }
            else{
                pruned_nodes++ ;
            }
        }
    }
    cout << "the maximum profit is : " << max << endl ;
    cout << "the max set is : " << endl ;
    for(int i=0 ; i<maxpath.size() ; i++){
        cout << "("<< items[maxpath[i]].first << "," << items[maxpath[i]].second << ")"<< endl ; 
    }
    cout <<"total nodes : " << total_nodes << endl ;
    cout <<"pruned nodes : " << pruned_nodes << endl ;
    return 0 ;
}