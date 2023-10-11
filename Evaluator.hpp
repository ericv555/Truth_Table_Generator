#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP
#include "Headers.hpp"
#include <iterator>
#include<stack>
#include<boost/dynamic_bitset/dynamic_bitset.hpp>

class Node
{
    public:
        Node *left;
        Node *right;
        vector<Token> vec_t;
        Token parent_op;
        Token_Kind child_op;
        int l_count;
        boost::dynamic_bitset<> evaluation;
        Node();
        Node(vector<Token>&);
        Node(vector<Token>&, int);
        void descent();
        void set_evaluation();
        
};
class Evaluator
{
    public:
        stack<Node> tree;
        void add_to_tree(Node*);
        void value_generator(int);
        void tree_height(Node*);
};

int t_size(Node *);
bool is_atomic(vector<Token>&);
#endif