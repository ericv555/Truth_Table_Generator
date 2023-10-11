//#include <boost/dynamic_bitset.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <bitset>
#include <stdlib.h>
#include <chrono>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
using namespace std;

//g++ -std=c++17 -pedantic -g -O3 -I /Users/ericv/Documents/VScode/Proof_Checker/boost_1_62_0 ValueGenerator.cpp
//g++ -std=c++17 -pedantic -g -O3 -I 
//g++ -std=c++17 -pedantic -g -O3 ValueGenerator.cpp
// When 18 variables are present their will be 4.7 million elements in the array



int main()
{
const int n=2;
const int numlines = (1<<n);

    //n-1 is the first byte
    //0 is the last bit of the byte
    //numlines-1 is the first bit of the byte

    //uint8_t truthtable[numlines][n];
    // n rows and numlines columns
    // rows are bytes
    for(int j = (numlines-1); j >=0;j--){
        for(int i=0;i<n;i++){
        //truthtable[i][j]= boost::dynamic_bitset<>(numlines, j)[i];
        cout << boost::dynamic_bitset<>(n, j)[i];
        //cout <<truthtable[i][j]; //Prints truth table
       }
       cout << endl;
    }
}



