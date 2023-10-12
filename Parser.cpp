#include "Parser.hpp"
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <stack>
using namespace std;



int letter_count(Lexer *l){
    int temp = l->unique_letters.size();
    l->unique_letters.clear();
    return temp;
    //n=temp;
}


void Parser :: to_tokenstring(Token *t)
{
    this->token_string.push_back(*t);
}
void Parser :: start()
{
    //const char *content = "p&q";
    const char *content = "(p&q)->(p&(qvr))";
    //const char *content = "(p->q)&((p&r)v(p<->t))";
    size_t cont_len = strlen(content);
    Lexer l = lexer_new(content, cont_len);
    Token t;
    t = lexer_next(&l); // start push
    to_tokenstring(&t);

    // Three valid starting characters of a well formed formula
    if(t.kind == TOKEN_END){cout << "Invalid: WFF is empty " << endl;}
    else if(t.kind == TOKEN_LEFTPARANTHESES){follow(&l);}
    else if (t.kind == TOKEN_LETTER){follow(&l);}
    else if (t.kind == TOKEN_NEGATION){follow(&l);}
    else{cout << "Invalid: WFF cannot start with '" << t.text[0] << "'" << endl;}
};
void Parser :: follow(Lexer *l)
{
    Token t;
    t=lexer_next(l);
    while(t.kind != TOKEN_END)
    {
        this->to_tokenstring(&t);

        if(t.kind == TOKEN_LETTER)
        {
            t=lexer_next(l);
            switch(t.kind)
            {
                case TOKEN_END:
                    break;
                case TOKEN_ARROW:
                    continue;
                case TOKEN_BIOCONDITONAL:
                    continue;
                case TOKEN_OR:
                    continue;
                case TOKEN_AND:
                    continue;
                case TOKEN_RIGHTPARANTHESES:
                    continue;
                default:
                {
                    cout << "Invalid: "<< token_kinderizer(t.kind)<< " cannot be here '" <<t.text << "'" << endl;
                    break;
                }
            }
            
        }
        else if(t.kind==TOKEN_NEGATION)
        {
            t=lexer_next(l);
            switch(t.kind)
            {
                case TOKEN_LEFTPARANTHESES:
                    continue;
                case TOKEN_LETTER:
                    continue;
                case TOKEN_NEGATION:
                    continue;
                default:
                    cout << "Invalid: "<< token_kinderizer(t.kind)<< " cannot be here '" <<t.text << "'" << endl;
            }
        }
        else if(t.kind==TOKEN_LEFTPARANTHESES)
        {
            t=lexer_next(l);
            switch(t.kind)
            {
                case TOKEN_NEGATION:
                    continue;
                case TOKEN_LETTER:
                    continue;
                case TOKEN_LEFTPARANTHESES:
                    continue;
                default:
                    cout << "Invalid: "<< token_kinderizer(t.kind)<< " cannot be here '" <<t.text << "'" << endl;
            }
        }
        else if(t.kind==TOKEN_RIGHTPARANTHESES)
        {
            t=lexer_next(l);
            switch(t.kind)
            {
                case TOKEN_END:
                    break;
                case TOKEN_ARROW:
                    continue;
                case TOKEN_BIOCONDITONAL:
                    continue;
                case TOKEN_OR:
                    continue;
                case TOKEN_AND:
                    continue;
                case TOKEN_RIGHTPARANTHESES:
                    continue;
                default:
                    cout << "Invalid: "<< token_kinderizer(t.kind)<< " cannot be here '" <<t.text << "'" << endl;
            }
        }
        else if((t.kind & (TOKEN_AND | TOKEN_OR | TOKEN_ARROW | TOKEN_BIOCONDITONAL))>0)
        {
            t=lexer_next(l);
            switch(t.kind)
            {
                 case TOKEN_NEGATION:
                     continue;
                 case TOKEN_LEFTPARANTHESES:
                     continue;
                 case TOKEN_LETTER:
                     continue;
                 default:
                     cout << "Invalid: "<< token_kinderizer(t.kind)<< " cannot be here '" <<t.text << "'" << endl;
            }

        }

        else{cout << "ERROR IN PARSER.CPP" << endl;} // Even the most invalid of formula shouldnt get here.
        
    }
    if(l->parantheses != 0) {INVALID("UNEVEN PARANTHESES COUNT");}
    l_count = letter_count(l);

}


