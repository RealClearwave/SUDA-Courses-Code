/*
[问题描述]
（1）创建一个无向图的邻接矩阵和邻接表结构；
（2）在邻接矩阵结构下对该图进行深度优先搜索；
（3）在邻接表结构下对该图进行广度优先搜索。
*/

#include <iostream>
#include <vector>
#include <map>
#include <cstring>
using namespace std;

const int maxn = 2001;
map<pair<int,int>, bool> ga;
vector<int> gv[maxn];
bool visited[maxn];

int n, m;

void DFTraverse_ga(int u){
    if (visited[u]) return;
    visited[u] = true;

    cout << u << " ";
    for (int i=1; i<=n; i++){
        if (ga.find(make_pair(u,i)) != ga.end()){
            DFTraverse_ga(i);
        }
    }
}

void BFTraverse_gv(int u){
    vector<int> q;
    q.push_back(u);
    visited[u] = true;

    while (!q.empty()){
        int u = q.front();
        cout << u << " ";
        q.erase(q.begin());
        for (int i=0; i<gv[u].size(); i++){
            int v = gv[u][i];
            if (visited[v]) continue;
            visited[v] = true;
            q.push_back(v);
        }
    }
}

int main(){
    cin>>n>>m;
    for (int i=1; i<=m; i++){
        int u, v;
        cin>>u>>v;
        ga[make_pair(u,v)] = true;
        ga[make_pair(v,u)] = true;
        gv[u].push_back(v);
        gv[v].push_back(u);
    }

    cout<<"DFTraverse_ga: ";
    memset(visited, false, sizeof(visited));
    DFTraverse_ga(1);
    cout<<endl;

    cout<<"BFTraverse_gv: ";
    memset(visited, false, sizeof(visited));
    BFTraverse_gv(1);
    cout<<endl;

    return 0;
}