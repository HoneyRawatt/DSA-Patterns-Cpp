#include<bits/stdc++.h>
using namespace std;

bool issafe(int node,int color[],bool graph[101][101],int n,int col){
    for(int k=0;k<n;k++){
        if(k!=node && graph[k][node]==1 && color[k]==col){
            return false;
        }
    }
    return true;
}

bool solve(int node,int color[],int m,int N,bool graph[101][101]){
if(node==N) return true;

for(int i=0;i<=m;i++){
    if(issafe(node,color,graph,N,i)){
        color[node]=i;
        if(solve(node+1,color,m,N,graph))return true;
        color[node]=0;
    }
}
}

bool graphcoloring(bool graph[101][101],int m,int N){
    int color[N]={0};
    if(solve(0,color,m,N,graph)) return true;
    return false;
}

int main() {
    int N = 4;  // Number of nodes
    int m = 3;  // Max colors allowed

    bool graph[101][101] = {0};

    // Define edges
    graph[0][1] = graph[1][0] = 1;
    graph[0][2] = graph[2][0] = 1;
    graph[1][2] = graph[2][1] = 1;
    graph[2][3] = graph[3][2] = 1;

    if (graphcoloring(graph, m, N)) {
        cout << "Graph can be colored using " << m << " colors.\n";
    } else {
        cout << "Graph cannot be colored using " << m << " colors.\n";
    }

    return 0;
}
