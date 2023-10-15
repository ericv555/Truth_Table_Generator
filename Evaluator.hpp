#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP


class Evaluator
{
    public:
        stack<Node*> tree;
        void add_to_tree(Node*);
        void evaluate(int);
        int numlines;
    private:
        void value_generator(Node*, int,int);
        char top_letter();
};


class ES {
    public:
        vector<Token> vec_t;
        bool isEvaluated;
        int value;
        bool isAtomic;
        ES *leftSide;
        ES *rightSide;
        Token_Kind connective;
};
#endif