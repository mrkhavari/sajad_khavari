#include <iostream>
#include <memory>
#include <vector>
#include "node.h"

void solve_random_puzzle();

int main()
{
    solve_random_puzzle();
    return 0;
}

void solve_random_puzzle()
{
    std::vector<int> row1 = {1,2,3};
    std::vector<int> row2 = {4,5,6};
    std::vector<int> row3 = {7,8,0};
    std::vector<std::vector<int>> goal_node;
    goal_node.push_back(row1);
    goal_node.push_back(row2);
    goal_node.push_back(row3);

    std::vector<int> rrow1 = {2,6,8};
    std::vector<int> rrow2 = {4,1,7};
    std::vector<int> rrow3 = {0,5,3};
    std::vector<std::vector<int>> goal_node1;
    goal_node1.push_back(rrow1);
    goal_node1.push_back(rrow2);
    goal_node1.push_back(rrow3);

    std::vector<Node> order;

    Node node{};
    node.random();
    node.make_childs();
    node.show();
    std::vector<std::vector<Node>> childs_in_this_row;
    std::vector<std::vector<Node>> childs_in_later_row;
    childs_in_this_row.push_back(node.childs);
    
    
    
    while(true)
    {
        childs_in_this_row[0][0].parent->show(); 
        std::cout <<"in row:" <<  childs_in_this_row.size() << std::endl;
        for (size_t i{0} ; i < childs_in_this_row.size() ; i++)
        {
            for (size_t j{0} ; j < childs_in_this_row[i].size() ; j++)
            {
                if (childs_in_this_row[i][j].members == goal_node)
                {
                    std::cout << "its ok" << std::endl;
                    return;
                }
                else
                {
                    childs_in_this_row[i][j].make_childs();
                    childs_in_later_row.push_back(childs_in_this_row[i][j].childs);
                }
            }   
        }
        std::cout << "last row :" <<  childs_in_later_row.size() << std::endl;
        std::cout << "--------------" << std::endl;
        childs_in_later_row[0][0].parent->show();
        childs_in_this_row.clear();
        childs_in_this_row = childs_in_later_row;
         
        childs_in_later_row.clear();        
    }
} 