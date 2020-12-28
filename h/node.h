#ifndef NODE_H
#define NODE_H
#include <memory>
#include <vector>
#include <iostream>

class Node
{
    public:
        Node();
        Node(Node*);
        Node(Node*,std::vector<std::vector<int>>);
        Node(std::vector<std::vector<int>>);
        void random();
        void show();
        void make_childs();
        void make_id();
        bool solvable();
        std::shared_ptr<Node> parent{nullptr};
        std::vector<std::shared_ptr<Node>> childs;
        std::vector<std::vector<int>> members;
        int id;
        int zero_row;
        int zero_column;
        size_t count = 0;
};

#endif