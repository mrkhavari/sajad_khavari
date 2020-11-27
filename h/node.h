#ifndef NODE_H
#define NODE_H
#include <memory>
#include <vector>
#include <iostream>

class Node
{
    public:
        Node();
        Node(Node*,std::vector<std::vector<int>>);
        void random();
        void show();
        void make_childs();
        void make_id();
        Node* parent{nullptr};
        std::vector<std::shared_ptr<Node>> childs;
        std::vector<std::vector<int>> members;
        int id;
        
};

#endif