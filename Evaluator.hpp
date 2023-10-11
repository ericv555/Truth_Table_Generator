#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP


class Evaluator
{
    public:
        stack<Node> tree;
        void add_to_tree(Node*);
        void value_generator(int);
        void tree_height(Node*);
        void traverse_postorder(Node*);
};

#endif