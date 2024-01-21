#ifndef LEXER_HPP
#define LEXER_HPP
#include <stdlib.h>
#include<iostream>
#include<string>
#include<vector>
#include<unordered_set>
using namespace std;

/*
To add a new operation this is a list of places that would need to be changed:
1) Token_Kind enum would need to be updated.
2) Parser would need to be updated: 
    a)symbol added to parser start if it is a valid starting character.
    b)added to parser:
        i) must know what symbols can precede the symbol this must be rectified in the relevent else if statements.
        ii) must have a new else if statement that includes all the characters that can validly follow the new symbol.
3)Lexer would require the new symbol to be searched for & the length of that symbol
4)If it is an operation that will impact truth value it must be added to node.cpp
5)Lastly the symbol must be repsentable by binary operations and such a binary representation must be added to Evaluator.cpp
*/
typedef enum
{
    TOKEN_END = 0,
    TOKEN_AND = 1,
    TOKEN_OR = 1<<2,
    TOKEN_ARROW = 1<<3,
    TOKEN_BIOCONDITONAL= 1<<4,
    TOKEN_LETTER = 1<<5,
    TOKEN_NEGATION = 1 << 6,
    TOKEN_LEFTPARANTHESES = 1 << 7,
    TOKEN_RIGHTPARANTHESES = 1 << 8,
    TOKEN_EXCEPTION = -1
}Token_Kind;


typedef struct
{
    Token_Kind kind;
    const char *text;
    size_t text_len;
}Token;

typedef struct
{
    const char *content;
    size_t content_len;
    size_t cursor;
    size_t line; //Will be important for arguments not important for validity checking
    size_t bol; //beginning of line
    size_t parantheses;
    unordered_set<char> unique_letters;
    
}Lexer;

const char *token_kinderizer(Token_Kind kind);
Lexer lexer_new(const char *content,size_t content_len);
Token lexer_next(Lexer *l);



#endif