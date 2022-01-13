//Sean Saephan
//sksaephan
//Project 1 CSCI311
//People who helped: Kyle (Lab TA)
#include<iostream>
#include<time.h>
#include<math.h>
#include<chrono>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;

//int vLength = 20000; Global variable to set the vector length (5000,10000,15000,20000,25000). Only used for quick testing
bool sortFunc(vector<int> &L), sortFuncDecend(vector<int> &L);
double sampleSD(const vector<double> v), average(const vector<double> v);///Calculates the SD and mean
vector<int> bubbleSort(vector<int> &L), insertSort(vector<int> &L), selectSort(vector<int> &L), quickSort(vector<int> &L); //Sort Algorithms from pseudo code
vector<int> randomVector(int size, int low, int high);//Sets vector to a set size and set min and max number
vector<int> makeBubble(vector<int> &L, ofstream &file), makeQuick(vector<int> &L, ofstream &file), makeInsert(vector<int> &L,ofstream &file), makeSelect(vector<int> &L, ofstream &file);//Prints out the message described in the pdf
vector<int> makeWorstBub(vector<int> &L, ofstream &file), makeWorstInsert(vector<int> &L, ofstream &file), makeWorstSelect(vector<int> &L, ofstream &file), makeWorstQuick(vector<int> &L, ofstream &file);//Prints out message of worst case 
vector<int> worstBubble(vector<int> &L), worstInsert(vector<int> &L), worstSelect(vector<int> &L), worstQuick(vector<int> &L);//Worst sort alorgithms
vector<int> bestBubble(vector<int> &L, ofstream &file), bestQuick(vector<int> &L, ofstream &file), bestInsert(vector<int> &L, ofstream &file), bestSelect(vector<int> &L, ofstream &file);//Best sort alorgithms

int main(){
        srand(time(NULL));//sets the random seed
        vector<int> data;//initialize vector 
        ofstream collectData ("Best 20000.txt");//ofstream to add the vectors to txt file, replace #length to match vLength
        collectData << endl;
        collectData << "Bubble Sort:" << endl;//Lines 30-66 sends the everything to the file
        makeBubble(data, collectData);
        collectData << endl;
        collectData << "Quick Sort:" << endl;
        makeQuick(data, collectData);
        collectData << endl;
        collectData << "Insertion Sort:" << endl;
        makeInsert(data, collectData);
        collectData << endl;
        collectData << "Selection Sort:" << endl;
        makeSelect(data, collectData);

        collectData << "Worst Bubble Sort: " << endl;
        makeWorstBub(data, collectData);
        collectData << endl;
        collectData << "Worst Quick Sort:" << endl;
        makeWorstQuick(data, collectData);
        collectData << endl;
        collectData << "Worst Insertion Sort:" << endl;
        makeWorstInsert(data, collectData);
        collectData << endl;
        collectData << "Worst Selection Sort:" << endl;
        makeWorstSelect(data, collectData);
        collectData << endl;

        collectData << "Best Bubble Sort:" << endl;
        bestBubble(data, collectData);
        collectData << endl;
        collectData << "Best Quick Sort:" << endl;
        bestQuick(data, collectData);
        collectData << endl;
        collectData << "Best Insert Sort:" << endl;
        bestInsert(data, collectData);
        collectData << endl;
        collectData << "Best Select Sort:" << endl;
        bestSelect(data, collectData);
        collectData << endl;
        collectData.close();//closes the file
        return 0;
}

bool sortFunc(vector<int> &L){ //Code provided from psuedo code in lecture (should be sorting.pdf) 
        for(int i=0;i<L.size()-1;i++){ //for loop that goes through size-1
                if(L[i-1]>L[i])//compares each element.
                        return false;
        }
        return true;
}

bool sortFuncDecend(vector<int> &L){//Checks to see if sort is sorted from descending
        for(int i=0;i<L.size()-1;i++){
                if(L[i]<L[i+1]){
                        return false;
                }
        }
        return true;
}

vector<int> randomVector(int size, int low, int high){//Code provided from project1 pdf
        vector<int> v(size,0);
        for(int i=0;i<size;i++){
                v[i] = rand() % (high - low+1) +low;
        }
        return v;
}

double sampleSD(const vector<double> v){//Code provided from project1 pdf
        double mean = 0;
        for(int i=0;i<v.size();i++){//This part finds the mean
                mean += v[i];
        }
        mean = mean/v.size();
        double sd = 0;
        for(int i=0;i<v.size();i++){//Then finds the SD using the mean
                sd += (v[i]-mean)*(v[i]-mean);
        }

        sd = sd / (v.size()-1);
        return sqrt(sd);
}

double average(const vector<double> v){//This is from the sampleSD function without the SD part
        double mean = 0;
        for(int i=0;i<v.size();i++){
                mean += v[i];
        }
        mean = mean/v.size();
        return mean;
}

vector<int> bubbleSort(vector<int> &L){//Bubble Sort from pseudo code from sorting.pdf
        bool sorted = false;
        while(sorted==false){
                sorted = true;
                for(int i=1;i<=L.size()-1;i++){
                        if(L[i-1]>L[i]){
                                int temp = L[i-1];
                                L[i-1] = L[i];
                                L[i] = temp;
                                sorted = false;

                        }

                }

        }
        return L;
}

vector<int> worstBubble(vector<int> &L){//Reverse bubble sort
        bool sorted = false;
        while(sorted==false){
                sorted = true;
                for(int i=0;i<L.size();i++){
                        for(int j=0;j<L.size()-1;j++){
                                if(L[j]<L[j+1]){
                                        int temp = L[j];
                                        L[j] = L[j+1];
                                        L[j+1] = temp;
                                        sorted = false;
                                }
                        }
                }
        }
        return L;
}

vector<int> insertSort(vector<int> &L){//Insertion sort from pseudo code from sorting.pdf
        int i = 1;
        while(i<L.size()){
                int j = i;
                while(j>0 && L[j]<L[j-1]){
                        int temp = L[j-1];
                        L[j-1] = L[j];
                        L[j] = temp;
                        j=j-1;
                }
                i=i+1;
        }
        return L;
}

vector<int> worstInsert(vector<int> &L){//Reverse insert sort 
        int i = 1;
        while(i<L.size()){
                int j = i;
                while(j>0 && L[j]>L[j-1]){
                        int temp = L[j-1];
                        L[j-1] = L[j];
                        L[j] = temp;
                        j=j-1;
                }
                i=i+1;
        }
        return L;
}

vector<int> selectSort(vector<int> &L){//Selection sort from pseudo code from sorting.pdf
        for(int i=0;i<=L.size()-2;i++){
                int uMin = i;
                for(int j=i+1;j<=L.size()-1;j++){
                        if(L[j]<L[uMin]){
                                uMin = j;
                        }
                }
                int temp = L[i];
                L[i] = L[uMin];
                L[uMin] = temp;
        }
        return L;
}

vector<int> worstSelect(vector<int> &L){//Reverse select sort
        for(int i=0;i<=L.size()-2;i++){
                int uMin = i;
                for(int j=i+1;j<=L.size()-1;j++){
                        if(L[j]>L[uMin]){
                                uMin = j;
                        }
                }
                int temp = L[i];
                L[i] = L[uMin];
                L[uMin] = temp;
        }
        return L;
}

vector<int> quickSort(vector<int> &L){//Quick sort from sorting.pdf
        if(L.size()<=1){
                return L;
        }
        int pivot = L[0];
        vector<int> A, B, combine;
        for(int i=1;i<L.size();i++){
                if(L[i]<=pivot){
                        A.push_back(L[i]);
                }else{
                        B.push_back(L[i]);
                }
        }
        A = quickSort(A);//Recursive call
        B = quickSort(B);//Recursive call
        for(int i=0;i<A.size();i++){//for loop to put vector A to the left spot
                combine.push_back(A[i]);
        }
        combine.push_back(pivot);//pushes back the middle number
        for(int i=0;i<B.size();i++){
                combine.push_back(B[i]);//adds the rest of the numbers back
        }
        return combine;
}

vector<int> worstQuick(vector<int> &L){//Reverse quick sort
        if(L.size()<=1){
                return L;
        }
        int pivot = L[0];
        vector<int> A, B, combine;
        for(int i=1;i<L.size();i++){
                if(L[i]>=pivot){
                        A.push_back(L[i]);
                }else{
                        B.push_back(L[i]);
                }
        }
        A = worstQuick(A);//Recursive call
        B = worstQuick(B);//Recursive call
        for(int i=0;i<A.size();i++){//for loop to put vector A to the left spot
                combine.push_back(A[i]);
        }
        combine.push_back(pivot);//pushes back the middle number
        for(int i=0;i<B.size();i++){
                combine.push_back(B[i]);//adds the rest of the numbers back
        }
        return combine;
}

vector<int> makeQuick(vector<int> &L, ofstream &file){
        int manyVectors = 50;//Set how many vectors you want to go through
        int vLength = 5000; 
        vector<int> random;//sets vector for randomvector
        vector<int> sorted;//set vector to store the sort vector
        vector<double> insert;//this is for the time calculation
        double elapsed;//provided from the project pdf
        chrono::high_resolution_clock::time_point start;//initializes clock start
        chrono::high_resolution_clock::time_point end; //clock end
        for(int i=0;i<=manyVectors;i++){//for loop to loop through how many vectors 
                start = chrono::high_resolution_clock::now();//starts clock
                random = randomVector(vLength,1,100);//sets random numbers of length vLength
                sorted = quickSort(random);//stores and sorts the random vector
                end = chrono::high_resolution_clock::now();//ends the clock
                elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();//calculates the time
                insert.push_back(elapsed);//pushes back time on vector
        }
        cout << "*********************\n" << "Quick sort on " << manyVectors << " vectors of length " << vLength << endl; //to print out what was on the pdf
        if(sortFunc(sorted)==true){//to see if it is sorted
                cout << "Sorting Successful" << endl;
        }else{
                cout << "Sorting Unsuccessful" << endl;
        }
        cout << "Minimum: " << *min_element(insert.begin(), insert.end()) << " sec; Mean: " << average(insert);//finds the min_element from algorithm header
        cout << " sec; Standard deviation: " << sampleSD(insert) << " sec; Maximum: " << *max_element(insert.begin(), insert.end()) << " sec " << endl;//finds max_element of all of the times in the vector
        cout << "*********************" << endl;
        for(int i=0;i<insert.size();i++){
                file << insert[i] << " ";//prints the time in the file
        }
        cout << endl;
        return sorted;
}

vector<int> makeBubble(vector<int> &L, ofstream &file){
        int manyVectors = 50;
        int vLength = 5000;
        vector<int> random, sorted;
        vector<double> insert;
        double elapsed;
        chrono::high_resolution_clock::time_point start;
        chrono::high_resolution_clock::time_point end; 
        for(int i=0;i<=manyVectors;i++){
                start = chrono::high_resolution_clock::now();
                random = randomVector(vLength,1,100);
                sorted = bubbleSort(random);
                end = chrono::high_resolution_clock::now();
                elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
                insert.push_back(elapsed);
        }
        cout << "*********************\n" << "Bubble sort on " << manyVectors << " vectors of length " << vLength << endl; 
        if(sortFunc(sorted)==true){
                cout << "Sorting Successful" << endl;
        }else{
                cout << "Sorting Unsuccessful" << endl;
        }
        cout << "Minimum: " << *min_element(insert.begin(), insert.end()) << " sec; Mean: " << average(insert);
        cout << " sec; Standard deviation: " << sampleSD(insert) << " sec; Maximum: " << *max_element(insert.begin(), insert.end()) << " sec " << endl;
        cout << "*********************" << endl;
        for(int i=0;i<insert.size();i++){
                file << insert[i] << " ";
        }
        cout << endl;
        return sorted;
}

vector<int> makeInsert(vector<int> &L, ofstream &file){
        int manyVectors = 50;
        int vLength = 5000;
        vector<int> random, sorted;
        vector<double> insert;
        double elapsed;
        chrono::high_resolution_clock::time_point start;
        chrono::high_resolution_clock::time_point end; 
        for(int i=0;i<=manyVectors;i++){
                start = chrono::high_resolution_clock::now();
                random = randomVector(vLength,1,100);
                sorted = insertSort(random);
                end = chrono::high_resolution_clock::now();
                elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
                insert.push_back(elapsed);
        } 
        cout << "*********************\n" << "Insert sort on " << manyVectors << " vectors of length " << vLength << endl; 
        if(sortFunc(sorted)==true){
                cout << "Sorting Successful" << endl;
        }else{
                cout << "Sorting Unsuccessful" << endl;
        }
        cout << "Minimum: " << *min_element(insert.begin(), insert.end()) << " sec; Mean: " << average(insert);
        cout << " sec; Standard deviation: " << sampleSD(insert) << " sec; Maximum: " << *max_element(insert.begin(), insert.end()) << " sec " << endl;
        cout << "*********************" << endl;
        for(int i=0;i<insert.size();i++){
                file << insert[i] << " ";
        }
        cout << endl;
        return sorted;
}

vector<int> makeSelect(vector<int> &L, ofstream &file){
        int manyVectors = 50;
        int vLength = 5000;
        vector<int> random, sorted;
        vector<double> insert;
        double elapsed;
        chrono::high_resolution_clock::time_point start;
        chrono::high_resolution_clock::time_point end; 
        for(int i=0;i<=manyVectors;i++){
                start = chrono::high_resolution_clock::now();
                random = randomVector(vLength,1,100);
                sorted = selectSort(random);
                end = chrono::high_resolution_clock::now();
                elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
                insert.push_back(elapsed);
        }
        cout << "*********************\n" << "Selection sort on " << manyVectors << " vectors of length " << vLength << endl; 
        if(sortFunc(sorted)==true){
                cout << "Sorting Successful" << endl;
        }else{
                cout << "Sorting Unsuccessful" << endl;
        }
        cout << "Minimum: " << *min_element(insert.begin(), insert.end()) << " sec; Mean: " << average(insert);
        cout << " sec; Standard deviation: " << sampleSD(insert) << " sec; Maximum: " << *max_element(insert.begin(), insert.end()) << " sec " << endl;
        cout << "*********************" << endl;
        for(int i=0;i<insert.size();i++){
                file << insert[i] << " ";
        }

        cout << endl;
        return sorted;
}

vector<int> makeWorstBub(vector<int> &L, ofstream &file){
        int manyVectors = 50;//Set how many vectors you want to go through
        int vLength = 5000; 
        vector<int> random, sorted;
        vector<double> insert;//this is for the time calculation
        double elapsed;//provided from the project pdf
        chrono::high_resolution_clock::time_point start;//initializes clock start
        chrono::high_resolution_clock::time_point end; //clock end
        for(int i=0;i<=manyVectors;i++){//for loop to loop through how many vectors 
                start = chrono::high_resolution_clock::now();//starts clock
                random = randomVector(vLength,1,100);//sets random numbers of length vLength
                sorted = worstBubble(random);//stores and sorts the random vector
                end = chrono::high_resolution_clock::now();//ends the clock
                elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();//calculates the time
                insert.push_back(elapsed);//pushes back time on vector
        }
        cout << "*********************\n" << "Worst Bubble sort on " << manyVectors << " vectors of length " << vLength << endl; //to print out what was on the pdf
        if(sortFuncDecend(sorted)==true){//to see if it is sorted
                cout << "Sorting Successful" << endl;
        }else{
                cout << "Sorting Unsuccessful" << endl;
        }
        cout << "Minimum: " << *min_element(insert.begin(), insert.end()) << " sec; Mean: " << average(insert);//finds the min_element from algorithm header
        cout << " sec; Standard deviation: " << sampleSD(insert) << " sec; Maximum: " << *max_element(insert.begin(), insert.end()) << " sec " << endl;//finds max_element of all of the times in the vector
        cout << "*********************" << endl;
        for(int i=0;i<insert.size();i++){
                file << insert[i] << " ";//prints the time in the file
        }
        cout << endl;
        return sorted;
}

vector<int> makeWorstInsert(vector<int> &L, ofstream &file){
        int manyVectors = 50;//Set how many vectors you want to go through
        int vLength = 5000;         
        vector<int> random, sorted;//set vector to store the sort vector
        vector<double> insert;//this is for the time calculation
        double elapsed;//provided from the project pdf
        chrono::high_resolution_clock::time_point start;//initializes clock start
        chrono::high_resolution_clock::time_point end; //clock end
        for(int i=0;i<=manyVectors;i++){//for loop to loop through how many vectors 
                start = chrono::high_resolution_clock::now();//starts clock
                random = randomVector(vLength,1,100);//sets random numbers of length vLength
                sorted = worstInsert(random);//stores and sorts the random vector
                end = chrono::high_resolution_clock::now();//ends the clock
                elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();//calculates the time
                insert.push_back(elapsed);//pushes back time on vector
        }
        cout << "*********************\n" << "Worst Insert sort on " << manyVectors << " vectors of length " << vLength << endl; //to print out what was on the pdf
        if(sortFuncDecend(sorted)==true){//to see if it is sorted
                cout << "Sorting Successful" << endl;
        }else{
                cout << "Sorting Unsuccessful" << endl;
        }
        cout << "Minimum: " << *min_element(insert.begin(), insert.end()) << " sec; Mean: " << average(insert);//finds the min_element from algorithm header
        cout << " sec; Standard deviation: " << sampleSD(insert) << " sec; Maximum: " << *max_element(insert.begin(), insert.end()) << " sec " << endl;//finds max_element of all of the times in the vector
        cout << "*********************" << endl;
        for(int i=0;i<insert.size();i++){
                file << insert[i] << " ";
        }
        cout << endl;
        return sorted;
}

vector<int> makeWorstSelect(vector<int> &L, ofstream &file){
        int manyVectors = 50;//Set how many vectors you want to go through
        int vLength = 5000; 
        vector<int> random, sorted;//set vector to store the sort vector
        vector<double> insert;//this is for the time calculation
        double elapsed;//provided from the project pdf
        chrono::high_resolution_clock::time_point start;//initializes clock start
        chrono::high_resolution_clock::time_point end; //clock end
        for(int i=0;i<=manyVectors;i++){//for loop to loop through how many vectors 
                start = chrono::high_resolution_clock::now();//starts clock
                random = randomVector(vLength,1,100);//sets random numbers of length vLength
                sorted = worstSelect(random);//stores and sorts the random vector
                end = chrono::high_resolution_clock::now();//ends the clock
                elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();//calculates the time
                insert.push_back(elapsed);//pushes back time on vector
        }
        cout << "*********************\n" << "Worst Select sort on " << manyVectors << " vectors of length " << vLength << endl; //to print out what was on the pdf
        if(sortFuncDecend(sorted)==true){//to see if it is sorted
                cout << "Sorting Successful" << endl;
        }else{
                cout << "Sorting Unsuccessful" << endl;
        }
        cout << "Minimum: " << *min_element(insert.begin(), insert.end()) << " sec; Mean: " << average(insert);//finds the min_element from algorithm header
        cout << " sec; Standard deviation: " << sampleSD(insert) << " sec; Maximum: " << *max_element(insert.begin(), insert.end()) << " sec " << endl;//finds max_element of all of the times in the vector
        cout << "*********************" << endl;
        for(int i=0;i<insert.size();i++){
                file << insert[i] << " ";
        }
        cout << endl;
        return sorted;
}

vector<int> makeWorstQuick(vector<int> &L, ofstream &file){
        int manyVectors = 50;//Set how many vectors you want to go through
        int vLength = 5000; 
        vector<int> random, sorted;//set vector to store the sort vector
        vector<double> insert;//this is for the time calculation
        double elapsed;//provided from the project pdf
        chrono::high_resolution_clock::time_point start;//initializes clock start
        chrono::high_resolution_clock::time_point end; //clock end
        for(int i=0;i<=manyVectors;i++){//for loop to loop through how many vectors 
                start = chrono::high_resolution_clock::now();//starts clock
                random = randomVector(vLength,1,100);//sets random numbers of length vLength
                sorted = worstQuick(random);//stores and sorts the random vector
                end = chrono::high_resolution_clock::now();//ends the clock
                elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();//calculates the time
                insert.push_back(elapsed);//pushes back time on vector
        }
        cout << "*********************\n" << "Worst Quick sort on " << manyVectors << " vectors of length " << vLength << endl; //to print out what was on the pdf
        if(sortFuncDecend(sorted)==true){//to see if it is sorted
                cout << "Sorting Successful" << endl;
        }else{
                cout << "Sorting Unsuccessful" << endl;
        }
        cout << "Minimum: " << *min_element(insert.begin(), insert.end()) << " sec; Mean: " << average(insert);//finds the min_element from algorithm header
        cout << " sec; Standard deviation: " << sampleSD(insert) << " sec; Maximum: " << *max_element(insert.begin(), insert.end()) << " sec " << endl;//finds max_element of all of the times in the vector
        cout << "*********************" << endl;
        for(int i=0;i<insert.size();i++){
                file << insert[i] << " ";
        }
        cout << endl;
        return sorted;
}
vector<int> bestBubble(vector<int> &L, ofstream &file){
        int manyVectors = 50;//Set how many vectors you want to go through
        int vLength = 5000; 
        vector<int> random = randomVector(vLength,1,100);//sets vector for randomvector
        vector<int> sorted = bubbleSort(random);;//set vector to store the sort vector
        vector<double> insert;//this is for the time calculation
        double elapsed;//provided from the project pdf
        chrono::high_resolution_clock::time_point start;//initializes clock start
        chrono::high_resolution_clock::time_point end; //clock end
        for(int i=0;i<=manyVectors;i++){//for loop to loop through how many vectors 
                start = chrono::high_resolution_clock::now();//starts clock
                sorted = bubbleSort(random);//stores and sorts the random vector
                end = chrono::high_resolution_clock::now();
                elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
                insert.push_back(elapsed);
        }
        cout << "*********************\n" << "Best Bubble sort on " << manyVectors << " vectors of length " << vLength << endl;
        if(sortFunc(sorted)==true){
                cout << "Sorting Successful" << endl;
        }else{
                cout << "Sorting Unsuccessful" << endl;
        }
        cout << "Minimum: " << *min_element(insert.begin(), insert.end()) << " sec; Mean: " << average(insert);
        cout << " sec; Standard deviation: " << sampleSD(insert) << " sec; Maximum: " << *max_element(insert.begin(), insert.end()) << " sec " << endl;
        cout << "*********************" << endl;
        for(int i=0;i<insert.size();i++){
                file << insert[i] << " ";
        }
        cout << endl;
        return sorted;

}

vector<int> bestQuick(vector<int> &L, ofstream &file){
        int manyVectors = 50;
        int vLength = 5000;
        vector<int> random = randomVector(vLength,1,100);
        vector<int> sorted = worstQuick(random);
        vector<double> insert;
        double elapsed;
        chrono::high_resolution_clock::time_point start;
        chrono::high_resolution_clock::time_point end;
        for(int i=0;i<=manyVectors;i++){
                start = chrono::high_resolution_clock::now();
                sorted = quickSort(random);
                end = chrono::high_resolution_clock::now();
                elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
                insert.push_back(elapsed);
        }
        cout << "*********************\n" << "Best Quick sort on " << manyVectors << " vectors of length " << vLength << endl;
        if(sortFunc(sorted)==true){
                cout << "Sorting Successful" << endl;
        }else{
                cout << "Sorting Unsuccessful" << endl;
        }
        cout << "Minimum: " << *min_element(insert.begin(), insert.end()) << " sec; Mean: " << average(insert);
        cout << " sec; Standard deviation: " << sampleSD(insert) << " sec; Maximum: " << *max_element(insert.begin(), insert.end()) << " sec " << endl;
        cout << "*********************" << endl;
        for(int i=0;i<insert.size();i++){
                file << insert[i] << " ";
        }
        cout << endl;
        return sorted;

}

vector<int> bestInsert(vector<int> &L, ofstream &file){
        int manyVectors = 50;
        int vLength = 5000; 
        vector<int> random = randomVector(vLength,1,100);
        vector<int> sorted = insertSort(random);
        vector<double> insert;
        double elapsed;
        chrono::high_resolution_clock::time_point start;
        chrono::high_resolution_clock::time_point end;
        for(int i=0;i<=manyVectors;i++){
                start = chrono::high_resolution_clock::now();
                sorted = insertSort(random);
                end = chrono::high_resolution_clock::now();
                elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
                insert.push_back(elapsed);
        }
        cout << "*********************\n" << "Best Insert sort on " << manyVectors << " vectors of length " << vLength << endl;
        if(sortFunc(sorted)==true){
                cout << "Sorting Successful" << endl;
        }else{
                cout << "Sorting Unsuccessful" << endl;
        }
        cout << "Minimum: " << *min_element(insert.begin(), insert.end()) << " sec; Mean: " << average(insert);
        cout << " sec; Standard deviation: " << sampleSD(insert) << " sec; Maximum: " << *max_element(insert.begin(), insert.end()) << " sec " << endl;
        cout << "*********************" << endl;
        for(int i=0;i<insert.size();i++){
                file << insert[i] << " ";
        }
        cout << endl;
        return sorted;

} 

vector<int> bestSelect(vector<int> &L, ofstream &file){
        int manyVectors = 50;
        int vLength = 5000;
        vector<int> random = randomVector(vLength,1,100);
        vector<int> sorted = selectSort(random);
        vector<double> insert;
        double elapsed;
        chrono::high_resolution_clock::time_point start;
        chrono::high_resolution_clock::time_point end;
        for(int i=0;i<=manyVectors;i++){
                start = chrono::high_resolution_clock::now();
                sorted = selectSort(random);
                end = chrono::high_resolution_clock::now();
                elapsed = chrono::duration_cast<chrono::duration<double>>(end - start).count();
                insert.push_back(elapsed);
        }
        cout << "*********************\n" << "Best Select sort on " << manyVectors << " vectors of length " << vLength << endl;
        if(sortFunc(sorted)==true){
                cout << "Sorting Successful" << endl;
        }else{
                cout << "Sorting Unsuccessful" << endl;
        }
        cout << "Minimum: " << *min_element(insert.begin(), insert.end()) << " sec; Mean: " << average(insert);
        cout << " sec; Standard deviation: " << sampleSD(insert) << " sec; Maximum: " << *max_element(insert.begin(), insert.end()) << " sec " << endl;
        cout << "*********************" << endl;
        for(int i=0;i<insert.size();i++){
                file << insert[i] << " ";
        }
        cout << endl;
        return sorted;
}
