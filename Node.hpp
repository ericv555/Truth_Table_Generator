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
        Node *Parent;
        boost::dynamic_bitset<> value;
        Node();
        Node(vector<Token>&);
        Node(vector<Token>&, int);
    private:
        void leaf_node();
        void descent();
        
};

int t_size(Node *);
bool is_atomic(vector<Token>&);
#endif