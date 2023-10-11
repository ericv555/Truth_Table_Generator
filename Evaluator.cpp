#include "Evaluator.hpp"
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
    bool flag=false;
    if(vec_t.front().kind == TOKEN_LEFTPARANTHESES){
            vec_t.erase(vec_t.begin());
            vec_t.shrink_to_fit();
        }
    if(vec_t.back().kind == TOKEN_RIGHTPARANTHESES){
                vec_t.erase(vec_t.end()-1);
                vec_t.shrink_to_fit();
        }
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
    Node *left = nullptr;
    Node *right= nullptr;
}
Node :: Node(vector<Token>& vec_t){
    this->vec_t = vec_t;
    void *left = malloc(6*sizeof(Node*));
    void *right = malloc(6*sizeof(Node*));
    left = &left;
    right = &right;
    
    descent();
}
Node :: Node(vector<Token>& vec_t, int letters){
    l_count=letters;
    this->vec_t = vec_t;
    Node *left = nullptr;
    Node *right= nullptr;
    descent();
}
void Node :: set_evaluation(){ // SHOULD ONLY ACCEPT ATOMICS
    if(child_op == TOKEN_AND){
        
    }
    else if(child_op == TOKEN_OR){
        
    }
    else if(child_op == TOKEN_ARROW){
        
    }
    else if(child_op == TOKEN_BIOCONDITONAL){
        
    }
    
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
        else if (tok.kind == TOKEN_NEGATION){continue;} // This will need to have its own conditions eventually) ~(p->q) needs case.
        else if((tok.kind &(TOKEN_AND | TOKEN_OR | TOKEN_ARROW | TOKEN_BIOCONDITONAL))>0)
        {
            if(is_atomic(vec_t)==true){
                cout << "Main connective found: " << token_kinderizer(tok.kind) << endl;
                cout << "EVALUATABLE" << endl;
                child_op = tok.kind;
                //set_evaluation();
                //for(Token tik : vec_t){cout <<"NODE: " <<token_kinderizer(tik.kind)<<endl;}
                //cout << "--------------" <<endl;
                break;
            }
            else if(p_count == 0){ //second term MUST be replaced
                cout << "Main connective found: " << token_kinderizer(tok.kind) << endl;
                child_op = tok.kind;
                //for(Token tik : vec_t){cout <<"NODE: " <<token_kinderizer(tik.kind)<<endl;}
                vector<Token> left_node(vec_t.begin(), vec_t.begin()+i); // CHANGE TO ITERATOR PRE FINAL VERSION
                is_wrapped(left_node);
                vector<Token> right_node(vec_t.begin()+(i+1), vec_t.end()); // CHANGE TO ITERATOR PRE FINAL VERSION
                is_wrapped(right_node);
                left = new Node{left_node,l_count};
                right =  new Node{right_node,l_count};
            }
            else{continue;}
        }
    }
}
void Evaluator:: value_generator(int n)
{

    int numlines = (1<<n);

    //n-1 is the first byte
    //0 is the last bit of the byte
    //numlines-1 is the first bit of the byte

    //uint8_t truthtable[numlines][n];
    for(int j = (numlines-1); j >=0;j--){
        for(int i=0;i<n;i++){
        //truthtable[i][j]= boost::dynamic_bitset<>(numlines, j)[i];
        cout << boost::dynamic_bitset<>(n, j)[i];
        //cout <<truthtable[i][j]; //Prints truth table
       }
       cout << endl;
    }
}
void Evaluator:: add_to_tree(Node *root)
{
    /*bool root_node=true;
    if(root_node==true){
        tree.push(*root);
        tree.push(*root->left);
        tree.push(*root->right);
    }*/
}