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
        int neighbor;
        int w;
        edge(){
                neighbor = 0;
                w = 0;
        };
        edge(int i, int j){
                neighbor = i;
                w = j;
        };
};

class Ugraph{
        public:
                Ugraph(int N);
                void printGraph();
                void bfs(int s);
                void bfs2(int s);
                void bfs3(int s);
                void dfs();
                void dfsCC(int v, int &t, vector<int> &p);
                void dfsB(int u, int &t);
                void dfsVisit(int u, int &t);
                bool dfsTwo(int v, int &t);
                //assignment 11
                void printPath(int v);
                void printPathRec(int v);
                void printLevels(int s);
                void addEdge(int u, int v);
                void removeEdge(int u, int v);

                //assignment 12
                bool sameCycle(int s, int r);
                void backTrack(int u);
                int longestCycle(int s);
                void dfsLongest(int u, int &t, int&cur);
                bool twoPaths(int s, int r);
                void initPar(int s);
                bool isOnPath(int s, int r, int q);
                bool shortestP(int u, int q);

                //project problems
                bool distinctPaths(int u, int v);
                void printBridges();
                void printCC();
                bool twoColoring();
 
        private:
                vector<vector<edge> > Adj;
                vector<int> low; //DFS
                vector<int> distance; //for BFS
                vector<char> color;
                vector<int> parents; //BFS, DFS
                vector<char> colors; //DFS
                vector<TimeStamp> stamps; //DFS
                int size; //total nodes in the graph

};


#endif
