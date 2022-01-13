//Sean Saephan
//sksaephan
//Project 3
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<algorithm>
#include<climits>
#include<utility>
#include "ugraph.h"

using namespace std;

Ugraph::Ugraph(int N){
        size = N;
        Adj.resize(size);
        distance.resize(size);
        parents.resize(size);
        colors.resize(size);
        stamps.resize(size);
        low.resize(size);
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

void Ugraph::bfs2(int s){
        for(int i = 0; i < size; i++){
                distance[i] = INT_MAX;
                parents[i] = i;
        }//for
        distance[s] = 0;
        queue<int> aq;
        aq.push(s);
        while(!aq.empty()){
                int u = aq.front();
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
} 

void Ugraph::bfs3(int s){
        for(int i = 0; i < size; i++){
                distance[i] = INT_MAX;
                parents[i] = i;
        }//for
        distance[s] = 0;
        queue<int> aq;
        aq.push(s);
        while(!aq.empty()){
                int u = aq.front();
                aq.pop();
                for(int i = 0; i < (int)Adj[u].size(); i++){
                        int v = Adj[u][i].neighbor;
                        if(distance[v] == INT_MAX && Adj[u][i].w!=-1){
                                distance[v] = distance[u] + 1;
                                parents[v] = u;
                                aq.push(v);
                        }
                }//for
        }//while
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

void Ugraph::dfsB(int u, int &t){
        colors[u] = 'G';
        stamps[u].d = t;
        low[u] = t;
        t++;
        for(int i=0;i<(int)Adj[u].size();i++){
                int v = Adj[u][i].neighbor;
                if(colors[v]=='W'){
                        parents[v] = u;
                        dfsB(v, t);
                        low[u] = min(low[u], low[v]);
                        if(low[v]==stamps[v].d){
                                cout << u << " " << v << endl;
                        }
                }else if(colors[v]=='G' || colors[v] == 'B'){
                        if(parents[u]!=v){
                                low[u] = min(low[u], stamps[v].d);
                        }
                }
        }
        colors[u] = 'B';
        stamps[u].f = t;
        t++;
}

void Ugraph::dfsCC(int v, int &t, vector<int> &p){
        colors[v] = 'G';
        stamps[v].d = t;
        t++;
        for(int i = 0; i < (int)Adj[v].size(); i++){
                int u = Adj[v][i].neighbor;
                if(colors[u] == 'W'){
                        parents[u] = v;
                        colors[u] = 'G';
                        p.push_back(u);
                        dfsCC(u, t, p);
                }
        }//for
        colors[v] = 'B';
        stamps[v].f = t;
        t++;
}

bool Ugraph::dfsTwo(int v, int &t){
        bool res = true;
        colors[v] = 'G';
        stamps[v].d = t;
        t++;
        for(int i = 0; i < (int)Adj[v].size(); i++){
                int u = Adj[v][i].neighbor;
                if(colors[u] == 'W'){
                        parents[u] = v;
                        if(color[v]== 'R'){
                                color[u] = 'B';
                        }else{
                                color[u] = 'R';
                        }
                        res = dfsTwo(u, t);
                }     
        }
        for(int i=0;i<(int)Adj[v].size();i++)
        {
                int u = Adj[v][i].neighbor;
                if(color[u] == color[v]){
                        res = false;
                }
        }
        //for
        stamps[v].f = t;
        t++;
        return res;
}

void Ugraph::printPath(int v){
        if(distance[v]!=INT_MAX){
                printPathRec(v);
                cout << endl;
        }
}

void Ugraph::printPathRec(int v){
        if(distance[v]==0){
                cout << v << " ";
                return;
        }
        printPathRec(parents[v]);
        cout << v << " ";
}

void Ugraph::printLevels(int s){
        for(int i = 0; i < size; i++){
                distance[i] = INT_MAX;
                parents[i] = i;
        }//for
        distance[s] = 0;
        queue<pair<int,int> > aq;
        aq.push(make_pair(s, distance[s]));
        int curLevel = 0;
        while(!aq.empty()){
                pair<int, int> apair = aq.front();
                int u = apair.first;
                int curDist = apair.second;
                if(curLevel != curDist){
                        cout << endl;
                        curLevel = curDist;
                }
                aq.pop();
                cout << u << " ";
                for(int i = 0; i < (int)Adj[u].size(); i++){
                        int v = Adj[u][i].neighbor;
                        if(distance[v] == INT_MAX){
                                distance[v] = distance[u] + 1;
                                parents[v] = u;
                                aq.push(make_pair(v, distance[v]));
                        }
                }//for
        }//while
        cout << endl;
}

void Ugraph::addEdge(int u, int v){
        Adj[u].push_back(edge(v, 0));
        Adj[v].push_back(edge(u, 0));
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

bool Ugraph::sameCycle(int s, int r){
        bfs3(s);
        backTrack(r);
        bfs3(r);
        if(distance[s]!=INT_MAX){
                return true;
        }
        return false;
}

void Ugraph::backTrack(int u){
        if(parents[u]==u){
                return;
        }
        int p = parents[u];
        for(int i=0;i<(int)Adj[p].size();i++){
                int v = Adj[p][i].neighbor;
                if(v==u){
                        Adj[p][i].w = -1;
                }
        }
        backTrack(parents[u]);
}

int Ugraph::longestCycle(int s){
        for(int i=0;i<(int)Adj.size();i++){
                parents[i] = i;
                colors[i] = 'W';
                distance[i] = INT_MAX;
        }
        int t = 0;
        int cur = -1;
        distance[s] = 0;
        dfsLongest(s, t, cur);
        if(cur==-1){
                return 0;
        }
        return cur;
}

void Ugraph::dfsLongest(int u, int &t, int&cur){
        colors[u] = 'G';
        stamps[u].d = t;
        t++;

        for(int i = 0; i < (int)Adj[u].size(); i++){
                int v = Adj[u][i].neighbor;
                if(colors[v] == 'W'){
                        parents[v] = u;
                        colors[v] = 'G';
                        distance[v] = distance[u]+1;
                        dfsLongest(v, t, cur);
                }else if(colors[v]=='G' && parents[v]==v){
                        int comp = distance[u]+1;
                        if(comp>cur){
                                cur = comp;
                        }
                }
        }//for
        colors[u] = 'B';
        stamps[u].f = t;
        t++;
}//dfsVi

bool Ugraph::twoPaths(int s, int r){
        bfs2(s);
        backTrack(r);
        bfs3(s);
        if(distance[r]!=INT_MAX){
                return true;
        }
        return false;
}

bool Ugraph::isOnPath(int s, int r, int q){
        bfs(s);
        if(distance[r] == INT_MAX){
                return false;
        }
        return shortestP(r, q);
}

bool Ugraph::shortestP(int u, int q){
        if(q==u){
                return true;
        }
        if(parents[u]==u){
                if(u!=q){
                        return false;
                }else{
                        return true;
                }
        }
        return shortestP(parents[u], q);
}

bool Ugraph::distinctPaths(int u, int v){
        bool res = true;
        if(twoPaths(u, v)){
                bfs2(u);
                printPath(v);
                backTrack(v);
                bfs3(u);
                printPath(v);
                return res;
        }
        res = false;
        return res;
}

void Ugraph::printBridges(){
        int time = 1;
        for(int u=0;u<size;u++){
                parents[u] = u;
                colors[u] = 'W';
                low[u] = INT_MAX;
        }
        for(int j=0;j<size;j++){
                if(colors[j]=='W'){
                        dfsB(j, time);
                }
        }
}

void Ugraph::printCC(){
        int time = 0;
        for(int i=0;i<size;i++){
                parents[i] = i;
                colors[i] = 'W';
        }
        for(int j=0;j<size;j++){
                if(colors[j] == 'W'){
                        vector<int> p;
                        colors[j] = 'G';
                        p.push_back(j);
                        dfsCC(j, time, p);
                        if(p[(int)p.size()-1] < p[(int)p.size()-2]){
                                swap(p[(int)p.size()-1], p[(int)p.size()-2]);
                        }
                        for(int u=0;u<(int)p.size();u++){
                                cout << p[u] << " ";
                        }
                        cout << endl;
                }
        }

}

bool Ugraph::twoColoring(){
        color.resize(size);
        bool res;
        int time = 0;
        for(int i=0;i<size;i++){
                distance[i] = 0;
                parents[i] = i;
                colors[i] = 'W';
                color[i] = 'R';
        }
        for(int j=0;j<size;j++){
                if(colors[j]=='W')
                {
                        color[j] = 'R';
                        res = dfsTwo(j, time);
                }
        }
        return res;
}
