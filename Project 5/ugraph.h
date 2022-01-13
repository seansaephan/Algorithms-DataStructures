//Sean Saephan
//sksaephan
//Project 3
#include<iostream>
#include<string>
#include<vector>
using namespace std;
#include "timestamp.h"

#ifndef UGRAPH_H
#define UGRAPH_H

struct edge{
        int source;
        int neighbor;
        int w;
        edge(){
                source =  0;
                neighbor = 0;
                w = 0;
        };
        edge(int i, int j){
                source = 0;
                neighbor = i;
                w = j;
        };
        edge(int from, int to, int aweight){
                source = from;
                neighbor = to;
                w = aweight;
        };
        bool operator<(edge y){return (this->w < y.w) ? true : false; };
};

class Ugraph{
        public:
                Ugraph(int N);
                void printGraph();
                void bfs(int s);
                void dfs();
                void dfsVisit(int u, int&t);
                void addEdge(int u, int v);
                void addEdge(int u, int v, int aweight);
                void removeEdge(int u, int v);

                void dijkstra(int s);
                int findSet(int v);
                void combine(int x, int y);
                void kruskal();
                void printMST();
                int weightMST();
                void printPath(int u, int v);
                int lenghtShortestW(int u, int v);

                void printDistance(){
                        for(int i=0;i<size;i++){
                                cout << distance[i] << " ";
                        }
                        cout << endl;
                }
                void printParents(){
                        for(int i=0;i<size;i++){
                                cout << parents[i] << " ";
                        }
                        cout << endl;
                }


 
        private:
                vector<vector<edge> > Adj;
                vector<vector<edge> > mst;
                vector<int> distance; //for BFS
                vector<char> color;
                vector<int> parents; //BFS, DFS
                vector<char> colors; //DFS
                vector<TimeStamp> stamps; //DFS
                int size; //total nodes in the graph

};


#endif
