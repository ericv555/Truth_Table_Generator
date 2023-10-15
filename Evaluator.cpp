#include "Headers.hpp"
#include "Evaluator.hpp"
#include <iostream>
#include <algorithm>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
using namespace std;


void Evaluator:: add_to_tree(Node *root)
{
    if(root->vec_t.size() == 1){
        tree.push(root);
        return;
    }
    tree.push(root);
    if(root->left != nullptr){
    add_to_tree(root->left);}
    if(root->right != nullptr){
    add_to_tree(root->right);}
}
void Evaluator:: value_generator(Node *node, int n, int total)
{
    int numlines = (1<<total);
    for(int j = 0; j <numlines;j++){
        boost::dynamic_bitset<> nbyte(n,j);
        node->value.push_back(nbyte[n-1]);
    }
}
char Evaluator :: top_letter(){
    return (tree.top()->vec_t.front().text[0]);
}
void Evaluator :: evaluate(int n){
    static int total_letters = n;
    vector<char> unique_letters;
    while(tree.empty() != true) // Change to while tree is not empty after implementation
    {
        bool is_unique=true;
        if(tree.top()->vec_t.size()==1) // Single Letter assignment block
        {
            int index =1;
            if (unique_letters.empty() == true)
            {
                unique_letters.push_back(top_letter());
                value_generator(tree.top(),1,total_letters);
                tree.pop();
            }
            else{
                
                for(char special : unique_letters){
                    if(special == top_letter()){
                        value_generator(tree.top(),index,total_letters);
                        is_unique=false;
                    }
                    index++;
                }
                if(is_unique !=false){
                        unique_letters.push_back(top_letter());
                        value_generator(tree.top(),index,total_letters);
                    }
            tree.pop();
            }
        }
        // Only two primary controls paths are needed since node vector will either have one character or more than one
        else{
            if(tree.top()->main_op == TOKEN_AND){
                tree.top()->value = (tree.top()->left->value & tree.top()->right->value);
            }
            else if(tree.top()->main_op == TOKEN_OR){
                tree.top()->value = (tree.top()->left->value | tree.top()->right->value);
            }
            else if(tree.top()->main_op == TOKEN_ARROW){
                tree.top()->value = ((~(tree.top()->left->value)) | (tree.top()->right->value));
            }
            else if(tree.top()->main_op == TOKEN_BIOCONDITONAL){
                tree.top()->value = ((tree.top()->left->value ^ tree.top()->right->value).flip());
            }
            else if(tree.top()->main_op == TOKEN_NEGATION){
                tree.top()->value =  ~(tree.top()->left->value);
            }
            else{cout << "ERROR OCCURED IN EVALUATION"<<endl; exit(2);}
            tree.pop();
        }
    }

    
        
}