#include "Parser.hpp"
#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <stack>
using namespace std;


void traverse_postorder(Node*, Evaluator*);
//void start();
//void follow();
//void badlogic();
//void breakitup();
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
    const char *content = "(p&q)->(p&(qvr))";
    //const char *content = "(p->q)&((p&r)v(p<->t))";
    size_t cont_len = strlen(content);
    Lexer l = lexer_new(content, cont_len);
    Token t;
    t = lexer_next(&l); // start push
    //cout << token_kinderizer(t.kind) << endl;
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
        //cout << token_kinderizer(t.kind) << endl;
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
    int l_count = letter_count(l);
    //e.add_to_tree(root);
    //for(Token tok : root.right->vec_t){cout << "NODE:" <<token_kinderizer(tok.kind) << endl;}
    //cout << root.left->right<< endl;
    //t_size(&root);
    Node root {token_string,l_count}; // Change of scope ???
    Evaluator e;

    //cout << root.left->left->left<< endl;
    //cout << "hi" << endl;
    traverse_postorder(&root,&e);




}
int i =0;
void traverse_postorder(Node* temp, Evaluator* e)
{
    cout <<++i<<endl;
    if(temp->vec_t.size() == 1){
    for(Token tok: temp->vec_t){
        //string_view str(tok.text);
        //cout << "Traversal1: " << str.substr(0,tok.text_len) << endl;
        e->tree.push(*temp);
        cout << e->tree.top().vec_t.front().text<<endl;
        }
    cout << endl;
    return;
    }
    for(Token tok: temp->vec_t){
        //string_view str(tok.text);
        //cout << "Traversal2: " << str.substr(0,tok.text_len) << endl;
        }
    cout << endl;
    traverse_postorder(temp->left,e);
    traverse_postorder(temp->right,e);
}

