#include<iostream>
#include<bitset>
#include<string>
using namespace std;
//What if there was one evalutor for each connective and they used function overloading
// as well as a specially made type for each connective
//otherwise it could be some kind of if else tower
const size_t n =3;
const size_t numlines = (1<<n);
/*
Connective binary Equivalents:
pvq ---- p|q
p&q ---- p&q
> ---- p&~q
*/

void checker(bool truthtable[][numlines], char s)
{
    bool eval[numlines];
    for(int i=(numlines-1); i>=0; i--)
    {
        eval[i]=(truthtable[n-1][i] & truthtable[n-2][i]); // eval is the truth value of composite prop (p&q)
        // maybe a recursive function?
        // Procedure: go through numlines items pass the evaluation to a bitset/array then pass the bitset to function
        //continue this until n=0
    }
    for(int i=(numlines-1); i>=0; i--)
    {
        eval[i]=(eval[i]&(truthtable[n-3][i]));
        cout << eval[i];
    }
    cout << endl;
}