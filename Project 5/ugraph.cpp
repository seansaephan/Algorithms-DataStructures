//Sean Saephan
//sksaephan
//Project 4
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>
#include<climits>
#include<utility>
#include "ugraph.h"
#include "priorityqueue.h"
#include "item.h"

using namespace std;

Ugraph::Ugraph(int N){
        size = N;
        Adj.resize(size);
        distance.resize(size);
        parents.resize(size);
        colors.resize(size);
        stamps.resize(size);
        mst.resize(size);

        for(int i=0;i<size;i++){
                distance[i] = INT_MAX;
                parents[i] = i;
                colors[i] = 'W';
        }
}

void Ugraph::printGraph(){
        for(int u=0;u<size;u++){
                //cout << u << ": ";
                for(int j=0;j<(int)Adj[u].size();j++){
                        int neighbor = Adj[u][j].neighbor;
                        cout << neighbor << " ";
                }//for adjacency list of u
                cout << endl;
        }//for all nodes u
}

void Ugraph::bfs(int s){
        for(int i = 0; i < size; i++){
                distance[i] = INT_MAX;
                parents[i] = i;
        }//for
        distance[s] = 0;
        queue<int> aq;
        aq.push(s);
        while(!aq.empty()){
                int u = aq.front();
                cout << u << " ";
                aq.pop();
                for(int i = 0; i < (int)Adj[u].size(); i++){
                        int v = Adj[u][i].neighbor;
                        if(distance[v] == INT_MAX){
                                distance[v] = distance[u] + 1;
                                parents[v] = u;
                                aq.push(v);
                        }
                }//for
        }//while
        cout << endl;
}

void Ugraph::dfs(){
        for(int i = 0; i < size; i++){
                parents[i] = i;
                colors[i] = 'W';
        }	
        int t = 0;

        for(int i = 0; i < size; i++){
                if(colors[i] == 'W'){
                        //color[i] = 'G';
                        dfsVisit(i, t);
                }//if
        }//for
        cout << endl;
}

void Ugraph::dfsVisit(int u, int &t){
        colors[u] = 'G';
        stamps[u].d = t;
        t++;
        cout << u << " ";
        for(int i = 0; i < (int)Adj[u].size(); i++){
                int v = Adj[u][i].neighbor;
                if(colors[v] == 'W'){
                        parents[v] = u;
                        colors[v] = 'G';
                        dfsVisit(v, t);
                }
        }//for
        colors[u] = 'B';
        stamps[u].f = t;
        t++;
}
void Ugraph::addEdge(int u, int v){
        edge one(u, 0);
        edge two(v, 0);
        Adj[u].push_back(two);
        Adj[v].push_back(one);
}

void Ugraph::removeEdge(int u, int v){
        int sizeU = (int)Adj[u].size();
        for(int i=0;i<sizeU;i++){
                if(Adj[u][i].neighbor == v){
                        Adj[u][i].neighbor = Adj[u][sizeU-1].neighbor;
                        Adj[u].resize(sizeU - 1);
                        break;
                }
        }
        int sizeV = (int)Adj[v].size();
        for(int j=0;j<sizeV;j++){
                if(Adj[v][j].neighbor == u){
                        Adj[v][j].neighbor = Adj[v][sizeV-1].neighbor;
                        Adj[v].resize(sizeV - 1);
                        break;
                }
        }
}

void Ugraph::addEdge(int u, int v, int aweight){
        edge one(u, v, aweight);
        edge two(v, u, aweight);
        Adj[u].push_back(one);
        Adj[v].push_back(two);
}

void Ugraph::dijkstra(int s){
        for(int i=0;i<size;i++){
                distance[i] = INT_MAX;
                parents[i] = i;
        }
        distance[s] = 0;
        PriorityQueue Q;
        for(int i=0;i<size;i++){
                Q.push(i, distance[i]);
        }

        while(Q.getSize() > 0){
                Item anitem = Q.getMin();
                Q.pop();
                int u = anitem.key;
                int distU = distance[u];
                if(distU != INT_MAX){
                        for(int j=0;j<(int)Adj[u].size();j++){
                                int v = Adj[u][j].neighbor;
                                int fromU = distance[u] + Adj[u][j].w;
                                if(fromU < distance[v]){
                                        distance[v] = fromU;
                                        parents[v] = u;
                                        Q.updatePriority(v, distance[v]);
                                }
                        }
                }

        }
}

void Ugraph::printPath(int u, int v){
        if(u==v){
                cout << u << " ";
                return;
        }
        printPath(u, parents[v]);
        cout << v << " ";
}

int Ugraph::lenghtShortestW(int u, int v){
        dijkstra(u);
        printPath(u, v);
        cout << endl;
        return distance[v];
}

int Ugraph::findSet(int v){
        if(parents[v]==v){
                return v;
        }
        parents[v] = findSet(parents[v]);
        return parents[v];
}

void Ugraph::combine(int x, int y){
        int rankX = distance[x];
        int rankY = distance[y];
        if(rankX>rankY){
                parents[y] = x;
        }else{
                parents[x] = y;
                if(rankX==rankY){
                        distance[y]++;
                }
        }
}

bool lessThan(const edge &x, const edge &y){ return (x.w < y.w) ? true : false; }

void Ugraph::kruskal(){
        for(int i=0;i<size;i++){
                parents[i] = i;
                distance[i] = 0;
        }
        vector<edge> edgesAll;
        for(int u=0;u<size;u++){
                for(int j=0;j<(int)Adj[u].size();j++){
                        int v = Adj[u][j].neighbor;
                        if(u<v){
                                edgesAll.push_back(Adj[u][j]);
                        }
                }
        }
        sort(edgesAll.begin(), edgesAll.end(), lessThan);
        int countEdges = 0;
        for(int i=0;i<(int)edgesAll.size();i++){
                int u = edgesAll[i].source;
                int v = edgesAll[i].neighbor;
                int w = edgesAll[i].w;
                int representativeU = findSet(u);
                int representativeV = findSet(v);
                if(representativeU != representativeV){
                        mst[u].push_back(edgesAll[i]);
                        mst[v].push_back(edge(v, u, w));
                        combine(representativeU, representativeV);
                        countEdges++;
                        if(countEdges == size -1){
                                break;
                        }
                }
        }

}
void Ugraph::printMST(){
        for(int u=0;u<size;u++){
                for(int j=0;j<(int)mst[u].size();j++){
                        int v = mst[u][j].neighbor;
                        cout << v << " ";
                }
                cout << endl;
        }
}

int Ugraph::weightMST(){
        int W = 0;
        for(int u=0;u<size;u++){
                for(int j=0;j<(int)mst[u].size();j++){
                        int v = mst[u][j].neighbor;
                        if(u<v){
                                W += mst[u][j].w;
                        }
                }
        }
        return W;
}

