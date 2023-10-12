#ifndef NODE_HPP
#define NODE_HPP
#include <iterator>
#include <stack>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>

class Node
{
    public:
        Node *left;
        Node *right;
        vector<Token> vec_t;
        Token_Kind child_op;
        int l_count;
        int level;
        boost::dynamic_bitset<> evaluation;
        Node();
        Node(vector<Token>&);
        Node(vector<Token>&, int);
        void leaf_node();
        void descent();
        void set_evaluation();
        
};

int t_size(Node *);
bool is_atomic(vector<Token>&);
#endif