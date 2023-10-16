#ifndef PARSER_HPP
#define PARSER_HPP
#include "Headers.hpp"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Parser
{
    public:
        void start(string);
        void follow(Lexer *);
        void to_tokenstring(Token*);
        vector<Token> token_string;
        int p_count = 0;
        int l_count = 0;
        bool well_formed = true;
};
int letter_count(Lexer *);


#endif