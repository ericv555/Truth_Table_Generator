#include "Headers.hpp"
#include "Node.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <span>
#include <stdlib.h>
#include <vector>
#include <iterator>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
using namespace std;

/*
Helper Function:
Removes outer most parantheses from vector of Tokens.
*/
void unwrap(vector<Token>& vec_t){
    if(vec_t.front().kind == TOKEN_LEFTPARANTHESES){
            vec_t.erase(vec_t.begin());
            vec_t.shrink_to_fit();
        }
    if(vec_t.back().kind == TOKEN_RIGHTPARANTHESES){
                vec_t.erase(vec_t.end()-1);
                vec_t.shrink_to_fit();
        }
}
/*
Helper Function:
Returns true if the vector of tokens is a valid atomic sentence which is of the form:
LETTER BINARY_CONNECTIVE LETTER
Ignores parantheses and negations.
*/
bool is_atomic(vector<Token>& vec_t){
    int check = 0;
    for(Token i : vec_t)
    {
        if(i.kind == TOKEN_LETTER){check += 1;}
        else if(i.kind == TOKEN_AND){check -= 2;}
        else if(i.kind == TOKEN_OR){check -= 2;}
        else if(i.kind == TOKEN_ARROW){check -= 2;}
        else if(i.kind == TOKEN_BIOCONDITONAL){check -= 2;}
        else if(i.kind == TOKEN_LEFTPARANTHESES){continue;}
        else if(i.kind == TOKEN_RIGHTPARANTHESES){continue;}
        else if (i.kind == TOKEN_NEGATION){continue;}
    }
    if(check == 0){ return true;}
    else{return false;}
}
/*
Helper Function:
Used for offset of left and right vector instantiation.
Offsets the number of negations since negations can be called sequently
For example: ~~~~~~~~p or ~~p&q 
*/
size_t double_negation(vector<Token>& vec_t){
    size_t number_of_negations =0;
    for(Token tok : vec_t){
        if(tok.kind == TOKEN_NEGATION){
            number_of_negations++;
        }
        else{return number_of_negations;}
    }
    return number_of_negations;
}

Node :: Node(){
    this->left = nullptr;
    this->right = nullptr;
}
Node :: Node(vector<Token>& vec_t){
    this->vec_t = vec_t;
    left = new Node;
    right = new Node;
    
    descent();
}
void Node :: leaf_node(int i){
    int l_count=0;
    if(vec_t.size() != 3){
        vector<Token> left_node(vec_t.begin(),vec_t.begin()+i);
        vector<Token> right_node(vec_t.begin()+(i+1),vec_t.end());
        unwrap(left_node);
        unwrap(right_node);
        left = new Node{left_node};
        right = new Node{right_node};
        
    }
    else{
    vector<Token> left_letter;
    left_letter.push_back(vec_t.front());
    vector<Token> right_letter;
    right_letter.push_back(vec_t.back());
    left = new Node(left_letter);
    right = new Node(right_letter);
    }
}
/*Iterates the vector of Tokens until it finds a connective.
It does this by, for the case of binary connectives:
Stripping any outer most paranthesese and finding the connective not surround by any.
For Unary Connectives:
Looking to the next token to determine if it follows a letter, left paranatheses, or another unary connective.
*/
void Node :: descent()
{
    int p_count = 0; // Parantheses count
    int i=-1;
    
    for(Token tok : vec_t)
    {
        ++i;
        if(tok.kind == TOKEN_LEFTPARANTHESES){p_count += 1;}
        else if(tok.kind == TOKEN_RIGHTPARANTHESES){p_count -= 1;}
        else if(tok.kind == TOKEN_LETTER){continue;}
        else if(tok.kind == TOKEN_NEGATION){
            size_t number_of_negations=double_negation(vec_t);
            if(vec_t.at(i+1).kind == TOKEN_LEFTPARANTHESES && is_atomic(vec_t)==true){
                main_op = tok.kind;
                vector<Token> left_node(vec_t.begin()+1,vec_t.end());
                unwrap(left_node);
                left = new Node{left_node};
                right = nullptr;
                break;
            }
            else if(vec_t.at(i+1).kind == TOKEN_LETTER && vec_t.size()==(1+number_of_negations))
            {
                main_op=tok.kind;
                vector<Token> left_node(vec_t.begin()+1,vec_t.end());
                unwrap(left_node);
                left = new Node{left_node};
                right = nullptr;
                break;
            }
        }
        else if((tok.kind &(TOKEN_AND | TOKEN_OR | TOKEN_ARROW | TOKEN_BIOCONDITONAL))>0)
        {
            if(is_atomic(vec_t)==true){
                main_op = tok.kind;
                leaf_node(i);
           }
            else if(p_count == 0){
                main_op = tok.kind;
                vector<Token> left_node(vec_t.begin(), vec_t.begin()+i); // CHANGE TO ITERATOR PRE FINAL VERSION
                unwrap(left_node);
                vector<Token> right_node(vec_t.begin()+(i+1), vec_t.end()); // CHANGE TO ITERATOR PRE FINAL VERSION
                unwrap(right_node);
                left = new Node{left_node};
                right = new Node{right_node};
            }
            else{continue;}
        }
    }
}
