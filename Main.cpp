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
    cout << "The logical connectives this program uses are, v (disjunction), & (conjunction), -> (conditional), <-> (biconditonal) " << endl;
    cout << "Compound propositions require parantheses." << endl;
    cout << "Here are a few examples of valid logical expressions:"<<endl;
    cout << "p&q "<<endl<< "~(p->q)"<<endl<< "((p&q)vs)->~(p<->x)"<<endl;
    cout << "Any letters can be used as variables except for v, which is the OR operator." <<endl<<endl;
    cout << "Enter logical expression:" << endl;
    cout<< "Enter 0 to break the loop."<<endl;
    while(true){
    string sentence;
    cin >> sentence;
    if (sentence == "0"){exit(0);}
    Parser p;
    p.start(sentence);
    if(p.well_formed == false){exit(0);}
    Node root {p.token_string};
    Evaluator e;
    e.add_to_tree(&root);
    e.evaluate(p.l_count);
    int n = root.value.size();
    for(int i=n-1;i>=0;i--)
    {
        cout<<root.value[i] <<endl;
    }

    }
    return 0;   
}