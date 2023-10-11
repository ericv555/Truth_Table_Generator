#include "Lexer.hpp"
#include <string>
#include <vector>
#include<iostream>
#include <fstream>
using namespace std;


const char* token_kinderizer(Token_Kind kind) // purely for readable output of tokens
{
    switch(kind)
    {
        case TOKEN_END:
            return "END OF CONTENT";
        case TOKEN_EXCEPTION:
            return "INVALID TOKEN";
        case TOKEN_LEFTPARANTHESES:
            return "LEFT PARANTHESES";
        case TOKEN_RIGHTPARANTHESES:
            return "RIGHT PARANTHESES";
        case TOKEN_LETTER:
            return "LETTER";
        case TOKEN_AND:
            return "AND OPERATOR";
        case TOKEN_OR:
            return "OR OPERATOR";
        case TOKEN_NEGATION:
            return "NEGATION OPERATOR";
        case TOKEN_ARROW:
            return "ARROW OPERATOR";
        case TOKEN_BIOCONDITONAL:
            return "BICONDITONAL OPERATOR";
        default:
            return "ERROR IN KINDERIZER"; // Does not do what I want it to

        return NULL;
        
        
    }
}

Lexer lexer_new(const char *content, size_t content_len)
{
    Lexer l{};
    l.content = content;
    l.content_len = content_len;
    return l;
}

void lexer_trim_left(Lexer *l)
{
    //make loop till no spaces
    //set bol to cursor post movemenet
    while(l->cursor < l->content_len && isspace(l->content[l->cursor]))
    {
        char x = l->content[l->cursor]; 
        l->cursor += 1;
        if (x == '\n')
        {
            l->line += 1;
            l->bol = l->cursor;
        }
    }
}

Token lexer_next(Lexer *l)
{
    lexer_trim_left(l);
    Token token = {
        .text = &l->content[l->cursor],
    };
    if (l->cursor >= l->content_len) 
    {
        token.kind = TOKEN_END;
        return token;
    }
    if(l->content[l->cursor] == '(')
    {
        l->cursor += 1;
        token.kind = TOKEN_LEFTPARANTHESES;
        token.text_len = 1;
        l->parantheses++;
        return token;
        
    }
    if(isalpha(l->content[l->cursor])==true && l->content[l->cursor] != 'v')
    {
        l->unique_letters.insert(l->content[l->cursor]);
        l->cursor += 1;
        token.kind = TOKEN_LETTER;
        token.text_len = 1;
        return token;
    }
    if(l->content[l->cursor] == '&')
    {
        l->cursor += 1;
        token.kind = TOKEN_AND;
        token.text_len = 1;
        return token;
    }
    if(l->content[l->cursor] == 'v')
    {
        l->cursor += 1;
        token.kind = TOKEN_OR;
        token.text_len = 1;
        return token;
    }
    if(l->content[l->cursor] == '~')
    {
        l->cursor +=1;
        token.kind = TOKEN_NEGATION;
        token.text_len = 1; 
        return token;

    }
    if(l->content[l->cursor] == ')')
    {
        l->cursor +=1;
        token.kind = TOKEN_RIGHTPARANTHESES;
        token.text_len = 1;
        l->parantheses--;
        return token;
    }
    if(l->content[l->cursor] == '<')
    {
        l->cursor += 1;
            lexer_trim_left(l);
            if(l->content[l->cursor] == '-') // could make is arrow and is conditonal functions to avoid nested if.
            {
                l->cursor +=1;
                lexer_trim_left(l);
                if(l->content[l->cursor] == '>')
                {
                    l->cursor +=1;
                    token.kind = TOKEN_BIOCONDITONAL;
                    token.text_len = 3;
                    return token;
                }
                else {token.kind = TOKEN_EXCEPTION; return token;}
            }
            else {token.kind = TOKEN_EXCEPTION; return token;}

    }
    else if(l->content[l->cursor] == '-')
    {
        //peak ahead to the next char since arrow is a length 2 substring
        l->cursor += 1;
        lexer_trim_left(l);
        if(l->content[l->cursor] == '>')
        {
            l->cursor +=1;
            token.kind = TOKEN_ARROW;
            token.text_len = 2;
            return token;
        }
        else{token.kind = TOKEN_EXCEPTION; return token;}
    }
    return token;


}