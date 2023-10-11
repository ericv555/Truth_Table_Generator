#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/*
I want functional error handling
like
F(x) = There can not be a space at x
P(x,y) = symbol y cannot follow symbol x
*/
void INVALID(string s)
{
    cout << "INVALID: "<<s << endl;
}