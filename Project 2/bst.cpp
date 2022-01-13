//Sean Saephan
//sksaephan
//Project 2
#include<iostream>
using namespace std;

#include "bst.h"

Tnode* BST::restoreBalance(Tnode* cur){ //restoreBalance that came with project 2 tar
        if(cur == NULL)
                return cur;
        int bf = balanceFactor(cur);
        if(bf > 1){//left subtree is higher
                if(balanceFactor(cur->left) >= 0){
                        cur = rightRotation(cur);//height is updated
                }//outside case
                else{
                        cur->left = leftRotation(cur->left);
                        cur = rightRotation(cur);
                }//inside case
        }//bf = 2
        else if(bf < -1){
                if(balanceFactor(cur->right) <= 0){
                        cur = leftRotation(cur);
                }//outside case
                else{
                        cur->right = rightRotation(cur->right);
                        cur = leftRotation(cur);
                }
        }//if bf = -2
        return cur;
}
Tnode* BST::remove(Tnode* cur, string ak){//remove function from project 2 tar
        if(cur == NULL)
                return NULL;
        if(ak < cur->key){
                cur->left = remove(cur->left, ak);

        }else if(ak > cur->key){
                cur->right = remove(cur->right, ak);

        }else{//found the key
                if(cur->left == NULL){
                        Tnode* temp = cur->right;
                        delete cur;
                        return temp;
                }else if(cur->right == NULL){
                        Tnode* temp = cur->left;
                        delete cur;
                        return temp;
                }else{
                        Tnode *leftMost = getleftmost(cur->right);
                        cur->key = leftMost->key;
                        cur->value = leftMost->value;
                        cur->right = remove(cur->right, leftMost->key);

                }//two children

        }//found key
        int bf = balanceFactor(cur);
        if(bf > 1 || bf < -1){//left subtree is higher
                cur = restoreBalance(cur);
        }//if bf = -2
        updateHeight(cur);
        updateSize(cur);//updated remove function so that it can update size
        return cur;
}//remove

Tnode* BST::getleftmost(Tnode* cur){//from project 2 tar
        if(cur == NULL)
                return NULL;
        if(cur->left == NULL)
                return cur;
        return getleftmost(cur->left);
}//getleftmost

void BST::printBF(Tnode *cur){//from project 2 tar
        if(cur != NULL){
                printBF(cur->left);
                int bf = balanceFactor(cur);
                cout << bf << " " ;
                printBF(cur->right);
        }//if
}//printBF

void BST::updateHeight(Tnode *cur){//from project 2 tar
        if(cur == NULL)
                return;
        int hl = getHeight(cur->left);
        int hr = getHeight(cur->right);
        cur->height = (hl > hr) ? (hl + 1) : (hr + 1);

}//updateHeight

int BST::balanceFactor(Tnode *cur){//from project 2 tar
        if(cur == NULL)
                return 0;

        return getHeight(cur->left) - getHeight(cur->right);
}

Tnode* BST::rightRotation(Tnode *cur){
        Tnode *L = cur->left;
        cur->left = L->right;
        updateHeight(cur);
        updateSize(cur);//updated rightRotation function so that it can update size
        L->right = cur;
        updateHeight(L);
        updateSize(L);//updated size
        return L;
}

Tnode* BST::leftRotation(Tnode *cur){
        Tnode *R = cur->right;
        cur->right = R->left;
        updateHeight(cur);
        updateSize(cur);//updated size
        R->left = cur;
        updateHeight(R);
        updateSize(R);//update size
        return R;
}

void BST::heightPrint(Tnode *cur){//from project 2 tar
        if(cur != NULL){
                heightPrint(cur->left);
                cout << cur->height << " ";
                heightPrint(cur->right);
        }

}
void BST::findPrint(Tnode *cur, string akey){//from project 2 tar
        if(cur != NULL){
                if(cur->key == akey){
                        int asize = (int)(cur->value).size();
                        for(int i = 0; i < asize ; i++)
                                cout << (cur->value)[i] << " ";
                        cout << endl;
                        return;
                }else if(akey < cur->key)
                        findPrint(cur->left, akey);
                else
                        findPrint(cur->right, akey);
        }
}//findPrint()

void BST::print_inorder(Tnode *cur){//from project 2 tar
        if(cur == NULL)
                return;
        print_inorder(cur->left);
        cout << "(" << cur->key << "){";
        int asize = (int)(cur->value).size();
        for(int i = 0; i < asize; i++)
                cout << (cur->value)[i] << " " ;
        cout << "} ";
        print_inorder(cur->right);
}//print_inorder


void BST::clean(Tnode *cur){//from project 2 tar
        if(cur == NULL)
                return;
        clean(cur->left);
        clean(cur->right);
        delete cur;
}//clean()

Tnode* BST::insert(Tnode *cur, string akey, string aval){//from project 2 tar
        if(akey < cur->key){
                if(cur->left == NULL){
                        cur->left = new Tnode(akey, aval);
                }//if found place
                else{
                        cur->left = insert(cur->left, akey, aval);

                }//else

        }//if 
        else if(akey > cur->key){
                if(cur->right == NULL){
                        cur->right = new Tnode(akey, aval);
                        updateHeight(cur);
                        updateSize(cur);//update size where ever there is an updateheight

                }
                else{
                        cur->right = insert(cur->right, akey, aval);						
                }

        }//else if
        else{
                (cur->value).push_back(aval);


        }
        int bf = balanceFactor(cur);
        if(bf > 1 || bf < -1){//left subtree is higher
                cur = restoreBalance(cur);
        }//if bf = -2
        updateHeight(cur);
        updateSize(cur);//updated size
        return cur;

}//insert()

void BST::updateSize(Tnode* cur){//updates the size of the subtree rooted at cur
        if(cur==NULL){
                return;
        }
        cur->size = getSize(cur->left) + getSize(cur->right) + 1;
}

void BST::printSize(Tnode* cur){//traverses the tree using in-order traversal
        if(cur == NULL){
                return;
        }
        printSize(cur->left);
        int size = getSize(cur);
        cout << size << " " ;//prints size at each node
        printSize(cur->right);
}

void BST::collect(Tnode* cur, string k, vector<string>& v){//collect function from lecture
        if(cur==NULL){
                return;
        }
        v.push_back(cur->key);//pushes the elements of the tree to the vector
        if(k<cur->key){
                collect(cur->left, k, v);
        }else if(k>cur->key){
                collect(cur->right, k, v);
        }
}

string BST::LCAscan(vector<string> v1, vector<string> v2){//scans the findLCA
        for(int i=0;i<v1.size();i++){
                if(v1[i]!=v2[i]){
                        return v1[i-1];
                }
        }
        return " ";
}

bool BST::findK(Tnode* cur, string k){//helper function for findLCA, need to find if they exists
        if(cur==NULL){
                return false;
        }
        if(cur->key > k){
                findK(cur->left, k);
        }else if(cur->key < k){
                findK(cur->right, k);
        }
        return true;
}

void BST::fillV(Tnode* cur, vector<string> &v){//function to fill the vector of the subtree
        if(cur==NULL){
                return;
        }
        fillV(cur->left, v);
        v.push_back(cur->key);
        fillV(cur->right,v);
}

void BST::collectSubtree(Tnode* cur, string akey, vector<string> &v){//function that takes an empty vector as parameter
        if(cur==NULL){
                return;
        }
        if(cur->key > akey){
                collectSubtree(cur->left, akey, v);
        }else if(cur->key < akey){
                collectSubtree(cur->right, akey, v);
        }else{
                fillV(cur, v);
        }
}

string BST::findKthSmallest(Tnode* cur, int k){//returns the k-th smallest key in the avl tree
        if(cur==NULL){
                return " ";//empty string
        }
        if(k <= getSize(cur->left)){//each node stores size
                return findKthSmallest(cur->left, k);
        }else if(k == getSize(cur->left)+1){
                return cur->key;
        }else if(k > getSize(cur->left)){
                return findKthSmallest(cur->right, (k-(getSize(cur->left))-1));
        }
        return " ";
}

void BST::printLongestPath(Tnode* cur){//prints the longest path from the root to a deepest leaf in the tree
        if(cur==NULL){
                return;
        }
        if(getHeight(cur->left)>getHeight(cur->right)){
                cout << cur->key << " ";
                printLongestPath(cur->left);
        }else if(getHeight(cur->left)<getHeight(cur->right)){
                cout << cur->key << " ";
                printLongestPath(cur->right);
        }else{     
                cout << cur->key << " ";
                printLongestPath(cur->left);
        }
}
