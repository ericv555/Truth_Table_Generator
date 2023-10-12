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
      
void is_wrapped(vector<Token>& vec_t){
    if(vec_t.front().kind == TOKEN_LEFTPARANTHESES){
            vec_t.erase(vec_t.begin());
            vec_t.shrink_to_fit();
        }
    if(vec_t.back().kind == TOKEN_RIGHTPARANTHESES){
                vec_t.erase(vec_t.end()-1);
                vec_t.shrink_to_fit();
        }
}
void Node :: leaf_node(){
    int l_count=0;
    vector<Token> left_letter;
    left_letter.push_back(vec_t.front());
    vector<Token> right_letter;
    right_letter.push_back(vec_t.back());
    left = new Node(left_letter);
    right = new Node(right_letter);

}

bool is_atomic(vector<Token>& vec_t){
    int check = 0;
    for(Token i : vec_t)
    {
        if(i.kind == TOKEN_LETTER){check += 1;}
        else if(i.kind == (TOKEN_AND)){check -= 2;}
        else if(i.kind == (TOKEN_OR)){check -= 2;}
        else if(i.kind == (TOKEN_ARROW)){check -= 2;}
        else if(i.kind == (TOKEN_BIOCONDITONAL)){check -= 2;}
        else if(i.kind == TOKEN_LEFTPARANTHESES){continue;}
        else if(i.kind == TOKEN_RIGHTPARANTHESES){continue;}
    }
    if(check == 0){ return true;}
    else{return false;}
}
int t_size(Node* node){
    if(node==nullptr){return 0;}
    else{
    return (1+ t_size(node->left) + t_size(node->right));}
}

Node :: Node(){
    //cout << "Default Constructor" << endl;
    this->left = nullptr;
    this->right= nullptr;
}
Node :: Node(vector<Token>& vec_t){
    this->vec_t = vec_t;
    left = new Node;
    right = new Node;
    
    descent();
}
Node :: Node(vector<Token>& vec_t, int letters){
    level=0;
    l_count=letters;
    this->vec_t = vec_t;
    left = new Node;
    right = new Node;
    descent();
}
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
        else if (tok.kind == TOKEN_NEGATION){continue;} // This will need to have its own conditions eventually ~(p->q) needs case.
        else if((tok.kind &(TOKEN_AND | TOKEN_OR | TOKEN_ARROW | TOKEN_BIOCONDITONAL))>0)
        {
            if(is_atomic(vec_t)==true){
                child_op = tok.kind;
                leaf_node();
                break;
           }
            else if(p_count == 0){
                child_op = tok.kind;
                vector<Token> left_node(vec_t.begin(), vec_t.begin()+i); // CHANGE TO ITERATOR PRE FINAL VERSION
                is_wrapped(left_node);
                vector<Token> right_node(vec_t.begin()+(i+1), vec_t.end()); // CHANGE TO ITERATOR PRE FINAL VERSION
                is_wrapped(right_node);
                left = new Node{left_node};
                right =  new Node{right_node};
            }
            else{continue;}
        }
    }
}
