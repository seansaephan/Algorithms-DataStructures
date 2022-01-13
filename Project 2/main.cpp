//Sean Saephan
//sksaephan
//Project 2
#include <stdlib.h>
#include<iostream>
#include<string>
#include<iomanip>
#include<stdio.h>
#include<cstdio>
#include<cmath>
#include<fstream>
using namespace std;

#include "bst.h"


int main(int argc, char* argv[]){

	
    BST numbers;
	string command;
	while(cin >> command){
		if(command == "print_inorder"){
			numbers.print_inorder();
			cout << endl;
		}else if(command == "printLongestPath"){
			numbers.printLongestPath();
			cout << endl;
		}else if(command == "heightPrint"){
			numbers.heightPrint();
			cout << endl;
		}else if(command == "printBF"){
			numbers.printBF();
			cout << endl;
		}else if(command == "printSize"){
			numbers.printSize();
			cout << endl;
		}
		else if(command == "findPrint"){
			string akey;
			cin >> akey;
			numbers.findPrint(akey);
		}else if(command == "insert"){
			string word;
			cin >> word;
			int len ;
			cin >> len;
			string akey = word.substr(0, len);
			numbers.insert(akey, word);
		}else if(command == "remove"){
			string akey;
			cin >> akey;
			numbers.remove(akey);
		}else if(command == "findLCA"){
			string akey1, akey2;
			cin >> akey1 >> akey2;
			string result = numbers.findLCA(akey1, akey2);
						cout << result << endl;
		}else if(command == "findKthSmallest"){
			int k;
			cin >> k;
			string result = numbers.findKthSmallest(k);
			cout << result << endl;
		}else if(command == "collectSubtree"){
			string akey;
			cin >> akey;
			vector<string> v;
			numbers.collectSubtree(akey, v);
			if(!v.empty()){
				for(int i = 0; i < (int)v.size(); i++)
					cout << v[i] << " " ;
				cout << endl;
			}
		}else{
			cerr << "ERROR: command " << command << " is not found." << endl;
		}
	}//while

    return 0;

}//main()
