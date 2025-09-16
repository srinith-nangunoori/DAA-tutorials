#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
using namespace std ;

class node {
public :
    char data ;
    node* left ;
    node* right ;
    node(char letter){
        this->data = letter ;
        this->left = NULL ;
        this->right = NULL ;
    }
    node(char letter , node* l , node* r){
        this->data = letter ;
        this->left = l ;
        this->right = r ;
    }
};

map<char , string> codes ;

void buildcodes(node* root  , string t){
    if(root->left != NULL || root->right != NULL){// i wrote extra to show that it would not occur and concept would be much clearer
        if(root->left != NULL && root->right != NULL){ // only this will occur every time 
            buildcodes(root->left , t+'0' );
            buildcodes(root->right , t+'1' );
        }
        else if(root->left != NULL){ // this will never occur
            buildcodes(root->left , t+'0' );
        }
        else{ // this will never occur
            buildcodes(root->right , t+'1' );
        }
    }
    else{
        codes[root->data] = t ;
    }
}

int main (void){
    char ch ;
    int fq ;
    cout << "how many differebt characters are there ? : " ;
    int n =0 ;
    cin >> n ;
    priority_queue<pair<int, node*>, vector<pair<int, node*>>, greater<pair<int, node*>>> pq; // min heap
    for(int i=0 ; i<n ; i++){
        cout << "what is the " << i << " char : " ;
        cin >> ch ;
        cout << "what is its freq : " ;
        cin >> fq ;
        node* temp = new node(ch);
        pq.push({fq,temp}) ;
    }
    while(pq.size()>1){
        int fsum = 0 ;
        fsum += pq.top().first ;
        node* t1 = pq.top().second;
        pq.pop();
        fsum += pq.top().first ;
        node* t2 = pq.top().second;
        pq.pop();
        node* x = new node('_', t1 , t2 );
        pq.push({fsum , x});
    }
    node* root = pq.top().second;
    buildcodes(root , "" );
    for(auto& x : codes){
        cout << x.first << " : " << x.second  << endl ;
    }
    return 0 ;
}