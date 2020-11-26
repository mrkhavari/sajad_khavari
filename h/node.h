#ifndef NODE_H
#define NODE_H
#include <memory>
#include <vector>
#include <iostream>

class Node
{
    public:
        Node();
        Node(Node , std::vector<std::vector<int>>);
        void random();
        void show();
        void make_childs();
        std::vector<std::shared_ptr<Node>> childs;
        std::shared_ptr<Node> parent;
        std::vector<std::vector<int>> members;
};


#endif