#include <iostream>
#include <memory>
#include <vector>
#include "node.h"
#include <ctime>
#include <string>
#include <sstream>
#include <cmath>

/*std::vector<int> row1 = {3,8,1};
std::vector<int> row2 = {5,7,6};
std::vector<int> row3 = {4,2,0};
std::vector<std::vector<int>> goal_members;
goal_members.push_back(row1);
goal_members.push_back(row2);
goal_members.push_back(row3);
std::shared_ptr<Node> node{std::make_shared<Node>(goal_members)};*/


/*std::shared_ptr<Node> node{std::make_shared<Node>()};
    node->random();
    node->show();*/
std::vector<Node*> solve_puzzle(std::shared_ptr<Node> node);
void solve_random_puzzle();
void solve_your_puzzle();

int main()
{  
    solve_random_puzzle();
}

std::vector<Node*> solve_puzzle(std::shared_ptr<Node> node)
{   
    int goal_id = 123456780; 
    std::vector<Node*> order;
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
            return order;
        }
        for (size_t n{0} ; n < childs_in_this_row.size() ; n++)
        {
            if (childs_in_this_row[n]->id == goal_id)
            {
                Node* _parent = childs_in_this_row[n]->parent;
                while (true)
                {
                    if (_parent == nullptr)
                    {
                        return order;
                    }
                    else
                    {
                        order.push_back(_parent);
                        _parent = _parent->parent;
                    }
                }
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
    return order;
} 

void solve_random_puzzle()
{
    std::vector<int> row1 = {1,2,3};
    std::vector<int> row2 = {4,5,6};
    std::vector<int> row3 = {7,8,0};
    std::vector<std::vector<int>> goal_members;
    goal_members.push_back(row1);
    goal_members.push_back(row2);
    goal_members.push_back(row3);
    std::shared_ptr<Node> goal_node{std::make_shared<Node>(goal_members)};

    std::shared_ptr<Node> node{std::make_shared<Node>()};
    node->random();
    std::cout << "I chose a random puzzle" << "\n" << std::endl;
    node->show();
    std::vector<Node*> order;
    order = solve_puzzle(node);
    if (order.size() == 0)
    {
        std::cout << "This Puzzle is not solvable" << std::endl;
    }
    else
    {
        std::cout << "I solved it" << "\n" << std::endl;
        for (size_t n{1} ; n < order.size() ; n++)
        {
            std::time_t start = time(0);
            while( difftime(std::time(0), start) <=0.5 );
            std::cout << "\n" << "------" << std::endl;
            std::cout << "Step : " << n << "\n" << std::endl;
            order[order.size()-n-1]->show();
        }
        std::time_t start = time(0);
        while( difftime(std::time(0), start) <=0.5 );
        std::cout << "\n" << "------" << std::endl;
        std::cout << "Step : " << order.size() << "\n" << std::endl;
        goal_node->show();
    }
}

void solve_your_puzzle()
{
    std::vector<int> row1 = {1,2,3};
    std::vector<int> row2 = {4,5,6};
    std::vector<int> row3 = {7,8,0};
    std::vector<std::vector<int>> goal_members;
    goal_members.push_back(row1);
    goal_members.push_back(row2);
    goal_members.push_back(row3);
    std::shared_ptr<Node> goal_node{std::make_shared<Node>(goal_members)};

    std::string pattern;
    std::cout << "You must enter your puzzle pattern : ";
    std::cin >> pattern;
    std::stringstream geek(pattern); 
    int id; 
    geek >> id;

    std::vector<std::vector<int>> members;
    int pow{8};
    for (int i{0} ; i < 3 ; i++)
    {
        std::vector<int> row;
        for (int j{0} ; j < 3 ; j++)
        {
            int p = std::pow(10,pow);
            int num = int(id/p);
            id = id - (p*num);
            row.push_back(num);
            pow--;
        }
        members.push_back(row);
    }
    
    std::shared_ptr<Node> node{std::make_shared<Node>(members)};
    std::cout << "This is your puzzle and I want to solve it" << "\n" << std::endl;
    node->show();
    std::vector<Node*> order;
    order = solve_puzzle(node);
    if (order.size() == 0)
    {
        std::cout << "This Puzzle is not sovable" << std::endl;
    }
    else
    {
        std::cout << "I solved it" << "\n" << std::endl;
        for (size_t n{1} ; n < order.size() ; n++)
        {
            std::time_t start = time(0);
            while( difftime(std::time(0), start) <=0.5 );
            std::cout << "\n" << "------" << std::endl;
            std::cout << "Step : " << n << "\n" << std::endl;
            order[order.size()-n-1]->show();
        }
        std::time_t start = time(0);
        while( difftime(std::time(0), start) <=0.5 );
        std::cout << "\n" << "------" << std::endl;
        std::cout << "Step : " << order.size() << "\n" << std::endl;
        goal_node->show();
    }
}