#include "Headers.hpp"
#include "Evaluator.hpp"
#include <iostream>
using namespace std;




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
void Evaluator ::  traverse_postorder(Node* temp)
{
    if(temp->vec_t.size() == 1){
    for(Token tok: temp->vec_t){
        //string_view str(tok.text);
        //cout << "Traversal1: " << str.substr(0,tok.text_len) << endl;
        tree.push(*temp);
        cout << tree.top().vec_t.front().text<<endl;
        }
    cout << endl;
    return;
    }
    for(Token tok: temp->vec_t){
        //string_view str(tok.text);
        //cout << "Traversal2: " << str.substr(0,tok.text_len) << endl;
        }
    cout << endl;
    traverse_postorder(temp->left);
    traverse_postorder(temp->right);
}