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
    add_to_tree(root->left);
    add_to_tree(root->right);
}
void Evaluator:: value_generator(Node *node, int n, int total)
{
    int numlines = (1<<total);
    for(int j = numlines-1; j >=0;j--){
        boost::dynamic_bitset<> nbyte(n,j);
        //cout << jerry[n-1] << endl;
        //cout << endl;
        node->value.push_back(nbyte[n-1]);
    }
    node->value.flip(); // To format from 1 to 0 (personal preference)
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
            int index =total_letters;
            if (unique_letters.empty() == true)
            {
                unique_letters.push_back(top_letter());
                value_generator(tree.top(),total_letters,total_letters);
                //cout <<"1. " <<tree.top()->value << endl;
                tree.pop();
            }
            else{
                
                for(char special : unique_letters){
                    if(special == top_letter()){
                        value_generator(tree.top(),index,total_letters);
                        //cout <<"2. "<<tree.top()->value << endl;
                        is_unique=false;
                    }
                    index--;
                }
                if(is_unique !=false){
                        unique_letters.push_back(top_letter());
                        value_generator(tree.top(),index,total_letters);
                        //cout <<"3. "<<tree.top()->value << endl;
                    }
            tree.pop();
            }
        }
        // Only two primary controls paths are needed since node vector will either have one character or more than one
        else{
            if(tree.top()->child_op == TOKEN_AND){
                tree.top()->value = (tree.top()->left->value & tree.top()->right->value);
            }
            else if(tree.top()->child_op == TOKEN_OR){
                tree.top()->value = (tree.top()->left->value | tree.top()->right->value);
            }
            else if(tree.top()->child_op == TOKEN_ARROW){
                tree.top()->value = (((tree.top()->left->value)) | ~tree.top()->right->value);
            }
            else if(tree.top()->child_op == TOKEN_BIOCONDITONAL){
                tree.top()->value = ((tree.top()->left->value ^ tree.top()->right->value).flip());
            }
            else if(tree.top()->child_op == TOKEN_NEGATION){
                //UNIMPLEMENTED
            }
            else{cout << "ERROR OCCURED IN EVALUATION"<<endl; exit(2);} // I dont think anything can get this far.
            //cout << tree.top()->value << endl;
            tree.pop();
        }
    }

    
        
}