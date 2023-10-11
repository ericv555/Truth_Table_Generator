#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP
#include "Headers.hpp"

class Evaluator
{
    public:
        stack<Node> tree;
        void add_to_tree(Node*);
        void value_generator(int);
        void tree_height(Node*);
};

#endif