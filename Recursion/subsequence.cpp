#include<iostream>
#include<vector>
using namespace std;

void subseq(int ind,vector<int>&ds,int arr[],int n){
    if(ind==n){
        for(auto it:ds) cout<<it<<" ";
        if(ds.size()==0){
        cout<<"{}";}
    cout<<endl;
    return;
    }
    
    ds.push_back(arr[ind]);
    subseq(ind+1,ds,arr,n);
    ds.pop_back();
    subseq(ind+1,ds,arr,n);
}

int main(){
    int n=4;
    int arr[]={5,3,4,1};
    vector<int>ds;
    subseq(0,ds,arr,n);
}