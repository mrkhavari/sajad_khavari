#include <iostream>
#include <memory>
#include <vector>
#include "node.h"
#include <ctime>
#include <string>
#include <sstream>
#include <cmath>

std::vector<Node*> solve_puzzle(std::shared_ptr<Node> node);
void solve_random_puzzle();
void solve_your_puzzle();
void solve_puzzle_by_your_self();


int main()
{  
    std::cout << "\033[1m\033[32m" << "\nWelcome To Sajad Puzzle Solver" << "\033[0m" << std::endl;
    while (true)
    {
        std::cout << "\033[1m\033[30m" <<  "----------------------------------------" << "\033[0m" << std::endl;
        std::cout << "\033[1m\033[36m" << "You can execute one of the following commands" << std::endl;
        std::cout << "Enter the command number for this operation" << "\033[0m" << std::endl;
        std::cout << "\033[1m\033[35m" << "1 : Solve a Random Puzzle" << std::endl;
        std::cout << "2 : Solve Your Puzzle" << std::endl;
        std::cout << "3 : Solve the puzzle by yourself" << std::endl;
        std::cout << "0 : Exit " << "\033[0m" << std::endl;
        std::cout << "\033[1m\033[34m" << "\nWhats Your Command : ";
        int command;
        std::cin >> command;
        std::cout << "\033[0m";
        if (command == 1)
        {
            solve_random_puzzle();
        }
        if (command == 2)
        {
            solve_your_puzzle();
        }
        if (command == 3)
        {
            solve_puzzle_by_your_self();
        }
        if (command == 0)
        {
            std::cout << "\033[0m";
            return 0;
        }
    }
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
    std::cout << "\033[1m\033[36m" <<  "I chose a random puzzle"<< "\n" << "\033[0m" << std::endl;
    node->show();
    std::vector<Node*> order;
    order = solve_puzzle(node);
    if (order.size() == 0)
    {
        std::cout << "\033[1m\033[31m" << "This Puzzle is not solvable" << "\033[0m" << std::endl;
    }
    else
    {
        std::cout << "\033[1m\033[32m" << "I solved it" << "\n" << "\033[0m" << std::endl;
        for (size_t n{1} ; n < order.size() ; n++)
        {
            std::time_t start = time(0);
            while( difftime(std::time(0), start) <=1 );
            std::cout << "\033[1m\033[30m" << "\n" << "--------------" << "\033[0m" << std::endl;
            std::cout << "\033[1m\033[34m" << "Step : " << n << "\n" << "\033[0m" << std::endl;
            order[order.size()-n-1]->show();
        }
        std::time_t start = time(0);
        while( difftime(std::time(0), start) <=0.5 );
        std::cout << "\033[1m\033[30m" << "\n" << "--------------" << "\033[0m" << std::endl;
        std::cout << "\033[1m\033[34m" << "Step : " << order.size() << "\n" << "\033[0m" << std::endl;
        goal_node->show();
    }
    std::cout << "\033[1m\033[32m" << "\n-------Done--------" << "\033[0m" << std::endl;
    std::time_t start = time(0);
    while( difftime(std::time(0), start) <=1);
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
    std::cout << "\033[1m\033[34m" << "You must enter your puzzle pattern : ";
    std::cin >> pattern;
    std::cout << "\033[0m";
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
    std::cout << "\033[1m\033[36m" << "This is your puzzle and I want to solve it" << "\n" << "\033[0m" << std::endl;
    node->show();
    std::vector<Node*> order;
    order = solve_puzzle(node);
    if (order.size() == 0)
    {
        std::cout << "\033[1m\033[31m" << "This Puzzle is not solvable" << "\033[0m" << std::endl;
    }
    else
    {
        std::cout << "\033[1m\033[32m" << "I solved it" << "\n" << "\033[0m" << std::endl;
        for (size_t n{1} ; n < order.size() ; n++)
        {
            std::time_t start = time(0);
            while( difftime(std::time(0), start) <=0.5 );
            std::cout << "\033[1m\033[30m" << "\n" << "--------------" << "\033[0m" << std::endl;
            std::cout << "\033[1m\033[34m" << "Step : " << n << "\n" << "\033[0m" << std::endl;
            order[order.size()-n-1]->show();
        }
        std::time_t start = time(0);
        while( difftime(std::time(0), start) <=0.5 );
        std::cout << "\033[1m\033[30m" << "\n" << "--------------" << "\033[0m" << std::endl;
        std::cout << "\033[1m\033[34m" << "Step : " << order.size() << "\n" << "\033[0m" << std::endl;
        goal_node->show();    
    }
    std::cout << "\033[1m\033[32m" << "\n-------Done--------" << "\033[0m" << std::endl;
    std::time_t start = time(0);
    while( difftime(std::time(0), start) <=1 );
}

void solve_puzzle_by_your_self()
{
    std::cout << "\033[1m\033[36m" << "I give you a puzzle and you have to solve it" << std::endl;
    std::time_t start = time(0);
    while( difftime(std::time(0), start) <=1.5);
    std::cout << "You can change the puzzle with the following guide" << "\033[0m" << std::endl;
    std::cout << "\033[1m\033[33m" << "         UP         \n         8         " << std::endl;
    std::cout << "LEFT 4         6 RIGHT" << std::endl;
    std::cout << "         2     \n        down         " << "\033[0m" << std::endl;
    std::cout << "\033[1m\033[36m" << "For example, if you select down, the number above the blank field will go down" << std::endl;
    std::cout << "If you are tired, enter 0" << std::endl;
    std::time_t start1 = time(0);
    while( difftime(std::time(0), start1) <=1.5);
    std::cout << "Let's go" << "\033[0m" << std::endl;
    std::cout << "\033[1m\033[30m" << "-----------------------------" << "\033[0m" << std::endl;
    std::cout << "\033[1m\033[35m" << "This is a puzzle that I want you to solve" << "\033[0m" << std::endl;

    int goal_id = 123456780;
    std::shared_ptr<Node> node{std::make_shared<Node>()};
    node->random();
    while (true)
    {
        node->show();
        std::cout << "\033[1m\033[30m" << "------------------------" << "\033[0m" << std::endl;
        std::cout << "\033[1m\033[34m" << "Choose a move : ";
        int cm;
        std::cin >> cm;
        std::cout << "\033[0m";
        if (cm == 0)
        {
            std::cout << "\033[1m\033[32m" << "\n-------Done--------" << "\033[0m" << std::endl;
            return;
        }
        else if (cm == 8)
        {
            if (node->zero_row == 2)
            {
                std::cout << "\033[1m\033[31m" << "This move is not available" << "\033[0m" << std::endl;
            }
            else
            {
                node->members[node->zero_row][node->zero_column] = node->members[node->zero_row+1][node->zero_column];
                node->members[node->zero_row+1][node->zero_column] =0;
                node->make_id();
            }
        }
        else if (cm == 4)
        {
            if (node->zero_column == 2)
            {
                std::cout << "\033[1m\033[31m" << "This move is not available" << "\033[0m" << std::endl;
            }
            else
            {
                node->members[node->zero_row][node->zero_column] = node->members[node->zero_row][node->zero_column+1];
                node->members[node->zero_row][node->zero_column+1] =0;
                node->make_id();
            }
        }
        else if (cm == 6)
        {
            if (node->zero_column == 0)
            {
                std::cout << "\033[1m\033[31m" << "This move is not available" << "\033[0m" << std::endl;
            }
            else
            {
                node->members[node->zero_row][node->zero_column] = node->members[node->zero_row][node->zero_column-1];
                node->members[node->zero_row][node->zero_column-1] =0;
                node->make_id();
            }
        }
        else if (cm == 2)
        {
            if (node->zero_row == 0)
            {
                std::cout << "\033[1m\033[31m" << "This move is not available" << "\033[0m" << std::endl;
            }
            else
            {
                node->members[node->zero_row][node->zero_column] = node->members[node->zero_row-1][node->zero_column];
                node->members[node->zero_row-1][node->zero_column] =0;
                node->make_id();
            }
        }
        else
        {
            std::cout << "\033[1m\033[31m" << "This command is not available" << "\033[0m" << std::endl;
        }
        if (node->id == goal_id)
        {
            std::cout << "\033[1m\033[32m" << "GOOD JOB" << "\033[0m" << std::endl;
        }
    }
}