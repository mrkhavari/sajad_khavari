#include "node.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>

Node::Node()
{
    std::cout << "" << std::endl;
}

Node::Node(Node* _node)
{
    members = _node->members;
    parent = _node->parent;
    childs = _node->childs;
    id = _node->id;
    zero_column = _node->zero_column;
    zero_row = _node->zero_row;
    count = _node->count;
}

Node::Node(Node* _parent,std::vector<std::vector<int>> _arr)
{
    members = _arr;
    std::shared_ptr<Node> p{std::make_shared<Node>(_parent)};
    parent = p;
    make_id();
}

Node::Node(std::vector<std::vector<int>> _arr)
{
    members = _arr;
    make_id();
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
    make_id();
}

void Node::show()
{
    for (size_t i{0} ; i < 3 ; i++)
    {
        for (size_t j{0} ; j < 3 ; j++)
        {
            if (members[i][j] == 0)
            {
                std::cout << "      " ;
            }
            else
            {
                std::cout << "\033[1m\033[33m" << members[i][j] << "     ";
            }
        }
        std::cout << "\n" << "\033[0m" << std::endl;
    } 
}

void Node::make_childs()
{
    for (int i{0} ; i < 3 ; i++)
    {
        for (int j{0} ; j < 3 ; j++)
        {
            if (std::abs(i - zero_row) + std::abs(j - zero_column) == 1 )
            {
                std::vector<std::vector<int>> new_arr = members;
                new_arr[zero_row][zero_column] = new_arr[i][j];
                new_arr[i][j] = 0;
                if (parent == nullptr || (parent !=nullptr && new_arr != parent->members))
                {
                    std::shared_ptr<Node> child_node{std::make_shared<Node>(this,new_arr)};
                    childs.push_back(child_node);
                }
            }
        }
    }
}

void Node::make_id()
{
    id = 0;
    size_t p=8;
    for (size_t i{0} ; i < 3 ; i++)
    {
        for (size_t j{0} ; j < 3 ; j++)
        {
            if (members[i][j] == 0)
            {
                zero_row = i;
                zero_column =j;
            }
            id = id + (members[i][j] * (std::pow(10,p)));
            p--;
        }
    }
}

bool Node::solvable()
{
    std::vector<int> compare;
    int size{0};
    for (size_t i{0} ; i < 3 ; i++)
    {
        for (size_t j{0} ; j < 3 ; j++)
        {
            for (size_t n{0} ; n < compare.size() ; n++)
            {
                if (members[i][j] < compare[n] && members[i][j] !=0)
                {
                    size++;
                }
            }
            compare.push_back(members[i][j]);
        }
    }
    if (size % 2 == 0)
    {
        return true;
    }
    return false;
}