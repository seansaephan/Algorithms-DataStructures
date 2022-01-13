//Sean Saephan
//sksaephan
//Project 2
#include<iostream>
#include<vector>
#include<string>
using namespace std;

#ifndef TNODE_H
#define TNODE_H


class Tnode{
        public:
                Tnode(): left(NULL), right(NULL) {};
				Tnode(string akey, string aval){
					key = akey;
					value.push_back(aval);
					height = 0;
                    size = 1;//added integer size
					left = NULL;
					right = NULL;
				};
                string key;
				vector<string> value;
				int height;
                int size;//added integer size
                Tnode* left;
                Tnode* right;
};

#endif
