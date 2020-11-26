#include "node.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>

Node::Node()
{
    std::cout << "Node Constructor" << std::endl;
}

Node::Node(Node _parent , std::vector<std::vector<int>> _arr)
{
    std::cout << "constructor" << std::endl;
    members = _arr;
    parent {_parent};
}

void Node::random()
{
    std::vector<int> numbers = {0,1,2,3,4,5,6,7,8};   
    srand(time(0));
    for (size_t i{0} ; i < 3 ; i++)
    {
        std::vector<int> row;
        for (size_t j{0} ; j < 3 ; j++)
        {
            int r =rand();
            int index = r % numbers.size();
            row.push_back(numbers[index]);
            numbers.erase(numbers.begin()+index);
        }
        members.push_back(row);
    }
}

void Node::show()
{
    for (size_t i{0} ; i < 3 ; i++)
    {
        for (size_t j{0} ; j < 3 ; j++)
        {
            if (members[i][j] == 0)
            {
                std::cout << "  " ;
            }
            else
            {
                std::cout << members[i][j] << " ";
            }
        }
        std::cout << std::endl;
    } 
}

void Node::make_childs()
{
    int zero_row{0};
    int zero_column{0};
    for (size_t i{0} ; i < 3 ; i++)
    {
        for (size_t j{0} ; j < 3 ; j++)
        {
            if (members[i][j] == 0)
            {
                zero_row = i;
                zero_column = j;
                break;
            }
        }
    }

    for (int i{0} ; i < 3 ; i++)
    {
        for (int j{0} ; j < 3 ; j++)
        {
            if (std::abs(i - zero_row) + std::abs(j - zero_column) == 1 )
            {
                std::vector<std::vector<int>> new_arr = members;
                new_arr[zero_row][zero_column] = new_arr[i][j];
                new_arr[i][j] = 0;
                auto child_node = std::make_shared<Node>(*this,new_arr);
            }
        }
    }
}