#include "Headers.hpp"
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <bitset>
#include <stdlib.h>
#include <stdio.h>


using namespace std;

//g++ -std=c++17 -pedantic -g -O3 -I Main.cpp
//g++ -std=c++17 -g -O3 -I Main.cpp



/*int main()
{d
    cout<< "What would you like to see." <<endl;
    cout << "Option 1: Evaluate formula and get final truth values" << endl;
    cout << "Option 2: Given a formula will give Tautology, Contradiction, Contingency." << endl;
    cout << "Option 3: Check if two formulas are equivalent" << endl;
    cout << "Option 3: Given an argument, will print whether the argument is valid or invalid." << endl;

    return  0;
}*/



int main()
{
    while(true){
    cout << "Enter logical expression" << endl;
    string sentence;
    cin >> sentence;
    Parser p;
    p.start(sentence);
    if(p.well_formed == false){break;}
    Node root {p.token_string};
    Evaluator e;
    e.add_to_tree(&root);
    e.evaluate(p.l_count);
    cout << root.value << endl;
    }
    return 0;   
}