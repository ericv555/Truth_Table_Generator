#ifndef PARSER_HPP
#define PARSER_HPP
#include "Lexer.hpp"
#include "Headers.hpp"
#include "ErrorHandling.hpp"
#include "Evaluator.hpp"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Parser
{
    public:
        void start();
        void follow(Lexer *);
        void to_tokenstring(Token*);
        vector<Token> token_string;
        int p_count = 0;
};
int letter_count(Lexer *);


#endif