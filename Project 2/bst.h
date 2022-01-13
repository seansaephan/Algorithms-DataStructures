//Sean Saephan
//sksaephan
//Project 2
#include<iostream>
#include<string>
#include<vector>
using namespace std;

#include "tnode.h"
#ifndef BST_H
#define BST_H

class BST{
        public:
                BST():  root(NULL) {};
                ~BST(){ clean(root); root = NULL; };
                
				void insert(string akey, string aval){
					if(root == NULL){
						root = new Tnode(akey, aval);
						return;
					}
					root = insert(root, akey, aval);
					
				};
				void print_inorder(){ print_inorder(root);
                        cout << endl;
				};
				void findPrint(string akey){ findPrint(root, akey); };
				void heightPrint(){ 
					heightPrint(root); 
					cout << endl;
				};
				void printBF(){
					printBF(root);
					cout << endl;
				}
				void remove(string ak){
					root = remove(root, ak);
				};
                void printSize(){
                        printSize(root);
                        cout << endl;
                }
                void collectSubtree(string akey, vector<string> &v){
                        collectSubtree(root, akey, v);
                }
                string findLCA(string k1, string k2){
                        if(findK(root, k1)==false || findK(root, k2) == false){//finds if empty
                                return " ";
                        }
                        vector<string> v1, v2;
                        collect(root, k1, v1);//collects
                        collect(root, k2, v2);//collects
                        return LCAscan(v1, v2);//scan to find lca
                }
                string findKthSmallest(int k){
                        return findKthSmallest(root, k);
                };
                void printLongestPath(){
                        printLongestPath(root);
                };
		private:
			Tnode* remove(Tnode* cur, string ak);
			Tnode* getleftmost(Tnode* cur);

			void printBF(Tnode *cur);
			int getHeight(Tnode *cur){
				if(cur == NULL)
					return -1;
				else
					return cur->height;
			};
				void updateHeight(Tnode *cur);
				int balanceFactor(Tnode *cur);
				Tnode* rightRotation(Tnode *cur);
				Tnode* leftRotation(Tnode *cur);
				void heightPrint(Tnode *cur);
				Tnode* insert(Tnode *cur, string akey, string aval);
				void print_inorder(Tnode *cur);
				Tnode *root = NULL;
				void clean(Tnode* cur);
				Tnode* copy(Tnode* cur);
				void findPrint(Tnode* cur, string key);
				Tnode* restoreBalance(Tnode* cur);
                int getSize(Tnode* cur){
                        if(cur==NULL){
                                return 0;
                        }
                        return cur->size;
                };
                void updateSize(Tnode* cur);
                void printSize(Tnode* cur);
                void collectSubtree(Tnode* cur, string akey, vector<string> &v);
                bool findK(Tnode* cur, string k);
                void collect(Tnode* cur, string k, vector<string> &v);
                void fillV(Tnode* cur, vector<string> &v);
                string LCAscan(vector<string> v1, vector<string> v2);
                string findKthSmallest(Tnode* cur, int k);
                void printLongestPath(Tnode* cur);
};


#endif
