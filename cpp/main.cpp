#include <iostream>
#include <memory>
#include "node.h"


int main()
{
    std::cout << "salam" << std::endl;
    auto node = std::make_shared<Node>();
    node->random();
    node->show();
    node->make_childs();
    return 0;
}