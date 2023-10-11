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
    if(vec_t.front().kind == TOKEN_LEFTPARANTHESES){
            vec_t.erase(vec_t.begin());
            vec_t.shrink_to_fit();
        }
    if(vec_t.back().kind == TOKEN_RIGHTPARANTHESES){
                vec_t.erase(vec_t.end()-1);
                vec_t.shrink_to_fit();
        }
}
void leaf_node(Node *node){
    int l_count=0;
    vector<Token> left_letter;
    left_letter.push_back(node->vec_t.front());
    vector<Token> right_letter;
    right_letter.push_back(node->vec_t.back());
    node->left = new Node(left_letter);
    node->right = new Node(right_letter);
    //for(Token tik : left_letter){cout <<"LLeft: " <<token_kinderizer(tik.kind)<<endl;}
    //cout << token_kinderizer(node->child_op) << endl;
    //for(Token tik : right_letter){cout <<"LRight: " <<token_kinderizer(tik.kind)<<endl;}

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
        else if (tok.kind == TOKEN_NEGATION){continue;} // This will need to have its own conditions eventually) ~(p->q) needs case.
        else if((tok.kind &(TOKEN_AND | TOKEN_OR | TOKEN_ARROW | TOKEN_BIOCONDITONAL))>0)
        {
            if(is_atomic(vec_t)==true){
                //cout << "Main connective found: " << token_kinderizer(tok.kind) << endl;
                //cout << "EVALUATABLE" << endl;
                child_op = tok.kind;
                leaf_node(this);
                //set_evaluation();
                //for(Token tik : vec_t){cout <<"NODE: " <<token_kinderizer(tik.kind)<<endl;}
                //cout << "--------------" <<endl;
                break;
           }
            else if(p_count == 0){ //second term MUST be replaced
                //cout << "Main connective found: " << token_kinderizer(tok.kind) << endl;
                child_op = tok.kind;
                vector<Token> left_node(vec_t.begin(), vec_t.begin()+i); // CHANGE TO ITERATOR PRE FINAL VERSION
                is_wrapped(left_node);
                vector<Token> right_node(vec_t.begin()+(i+1), vec_t.end()); // CHANGE TO ITERATOR PRE FINAL VERSION
                is_wrapped(right_node);
                //for(Token tik : left_node){cout <<"Left: " <<token_kinderizer(tik.kind)<<endl;}
                //for(Token tik : right_node){cout <<"Right: " <<token_kinderizer(tik.kind)<<endl;}
                left = new Node{left_node};
                right =  new Node{right_node};
            }
            else{continue;}
        }
    }
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