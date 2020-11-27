#include <iostream>
#include <memory>
#include <vector>
#include "node.h"

std::shared_ptr<Node> solve_random_puzzle();

int main()
{
    auto node =solve_random_puzzle();
    node->show();
}

std::shared_ptr<Node> solve_random_puzzle()
{

    int goal_id = 123456780;    

    std::vector<int> row1 = {1,2,3};
    std::vector<int> row2 = {0,1,3};
    std::vector<int> row3 = {6,8,7};
    std::vector<std::vector<int>> goal_node;
    goal_node.push_back(row1);
    goal_node.push_back(row2);
    goal_node.push_back(row3);

    std::vector<Node*> order;

    std::shared_ptr<Node> node{std::make_shared<Node>()};
    node->random();
    node->show();
    node->make_childs();
    std::vector<int> all_id;
    std::vector<std::shared_ptr<Node>> childs_in_this_row{node->childs};
    std::vector<std::shared_ptr<Node>> childs_in_later_row;
    for (size_t i{0} ; i < childs_in_this_row.size() ; i++)
    {
        all_id.push_back(childs_in_this_row[i]->id);
    }
    while(true)
    {
        if (childs_in_this_row.size() == 0)
        {
            std::cout << "nashod" << std::endl;
            node = solve_random_puzzle();
            return node;
        }
        for (size_t n{0} ; n < childs_in_this_row.size() ; n++)
        {
            if (childs_in_this_row[n]->id == goal_id)
            {
                std::cout << "its ok" << std::endl;
                Node* _parent = childs_in_this_row[n]->parent;
                size_t l{1};
                while (true)
                {
                    if (_parent == nullptr)
                    {
                        for (l ; l < order.size() ;  l++)
                        {
                            std::cout << "Step : " << l << std::endl << "\n";
                            order[order.size()-1-l]->show();
                            std::cout << "------------" << std::endl;
                        }
                        break;
                    }
                    else
                    {
                        order.push_back(_parent);
                        _parent = _parent->parent;
                    }
                }
                std::cout << "Step : " << l << std::endl << "\n";
                childs_in_this_row[n]->show();
                return node;
            }
            else
            {
                childs_in_this_row[n]->make_childs();
                for (size_t m{0} ; m < childs_in_this_row[n]->childs.size() ; m++)
                {
                    bool exist = false;
                    for (size_t o{0} ; o < all_id.size() ; o++)
                    {
                        if (all_id[o] == childs_in_this_row[n]->childs[m]->id)
                        {
                            exist = true;
                            break;
                        }
                    }
                    if(exist == false && childs_in_this_row[n]->childs[m]->id != childs_in_this_row[n]->parent->id ) 
                    {
                        childs_in_later_row.push_back(childs_in_this_row[n]->childs[m]);
                        all_id.push_back(childs_in_this_row[n]->childs[m]->id);
                    }
                }
            }
        }
        childs_in_this_row.clear();
        childs_in_this_row = childs_in_later_row;
        childs_in_later_row.clear();
    }
    return node;
} 