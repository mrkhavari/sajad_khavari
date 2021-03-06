#include <iostream>
#include <memory>
#include <vector>
#include "node.h"
#include <ctime>
#include <string>
#include <sstream>
#include <cmath>
#include <thread>

std::vector<std::shared_ptr<Node>> solve_puzzle_bfs(std::shared_ptr<Node> node ,int goal_id = 123456780);
std::vector<std::shared_ptr<Node>> solve_puzzle_dls(std::shared_ptr<Node> node , size_t limit = 40 ,int goal_id = 123456780) ;
std::vector<std::shared_ptr<Node>> faster(std::shared_ptr<Node> node ,int goal_id = 123456780);
std::vector<std::shared_ptr<Node>> bidirectional(std::shared_ptr<Node> node , int goal_id = 123456780);
void solve_random_puzzle();
void solve_your_puzzle();
void solve_puzzle_by_your_self();
void solve_random_puzzle_with_special_goal();
void solve_your_puzzle_with_special_goal();

bool complete = false;
std::vector<std::shared_ptr<Node>> order_bfs;
std::vector<std::shared_ptr<Node>> order_dls;

int main()

{    
   std::cout << "\033[1m\033[32m" << "\nWelcome To Sajad Puzzle Solver" << "\033[0m" << std::endl;
    while (true)
    {
        std::cout << "\033[1m\033[30m" <<  "----------------------------------------" << "\033[0m" << std::endl;
        std::cout << "\033[1m\033[36m" << "You can execute one of the following commands" << std::endl;
        std::cout << "Enter the command number for this operation" << "\033[0m" << std::endl;
        std::cout << "\033[1m\033[35m" << "1 : Solving A Random Puzzle" << std::endl;
        std::cout << "2 : Solving Your Puzzle" << std::endl;
        std::cout << "3 : Solve The Puzzle By Yourself" << std::endl;
        std::cout << "4 : Solving A Random Puzzle With Special Goal" << std::endl;
        std::cout << "5 : Solving Your Puzzle With Special Goal" << std::endl;
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
        if (command == 4)
        {
            solve_random_puzzle_with_special_goal();
        }
        if (command == 5)
        {
            solve_your_puzzle_with_special_goal();
        }
        if (command == 0)
        {
            std::cout << "\033[0m";
            return 0;
        }
    }
    return 0;
}


std::vector<std::shared_ptr<Node>> solve_puzzle_bfs(std::shared_ptr<Node> node , int goal_id)
{   
    complete = false;
    order_bfs.clear();
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
        if (complete == true)
        {
            return order_bfs;
        }   
        if (childs_in_this_row.size() == 0)
        {
            return order_bfs;
        }
        for (size_t n{0} ; n < childs_in_this_row.size() ; n++)
        {
            if (childs_in_this_row[n]->id == goal_id)
            {
                std::shared_ptr<Node> _parent = childs_in_this_row[n]->parent;
                while (true)
                {
                    if (_parent == nullptr)
                    {
                        complete = true;
                        return order_bfs;
                    }
                    else
                    {
                        order_bfs.push_back(_parent);
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
    return order_bfs;
}

std::vector<std::shared_ptr<Node>> solve_puzzle_dls(std::shared_ptr<Node> node ,size_t limit,int goal_id)
{
    complete = false;
    order_dls.clear();
    std::shared_ptr<Node> thisnode = node;
    std::vector<int> all_id;
    size_t depth = 0;
    while (true)
    {   
        if (complete == true)
        {
            return order_dls;
        }   
        if (thisnode->id == goal_id)
        {
            std::shared_ptr<Node> _parent = thisnode->parent;
            while (true)
            {
                if (_parent == nullptr)
                {
                    complete = true;
                    return order_dls;
                }
                else
                {
                    order_dls.push_back(_parent);
                    _parent = _parent->parent;
                }
            }
        }

        else
        {
            if (depth < limit)
            {
                thisnode->childs.clear();
                thisnode->make_childs();                
                if (thisnode->childs.size() > thisnode->count)
                {
                    thisnode = thisnode->childs[thisnode->count];
                    depth++;
                }

                else
                {
                    if (thisnode->parent == nullptr)
                    {
                        return order_dls;
                    }
                    thisnode->parent->count++;
                    thisnode = thisnode->parent;
                    depth--;
                }
                
            }
            
            else
            {
                thisnode->parent->count++;
                thisnode = thisnode->parent;
                depth--;   
            }
            
        }
        
    }
    
    return order_dls;
}

std::vector<std::shared_ptr<Node>> faster(std::shared_ptr<Node> node ,int goal_id)
{
    std::thread first (solve_puzzle_bfs,node,goal_id);
    std::thread second (solve_puzzle_dls,node,40,goal_id);
    first.joinable();
    second.joinable();
    first.join();
    second.join();
    if (order_bfs.size() > order_dls.size())
    {
        std::cout << "\033[1m\033[33m" << "BFS is faster" << "\033[0m" << std::endl;
        std::time_t start1 = time(0);
        while( difftime(std::time(0), start1) <=0.5);
        return order_bfs;
    }
    else 
    {
        std::cout << "\033[1m\033[33m" << "DLS is faster" << "\033[0m" << std::endl;
        std::time_t start1 = time(0);
        while( difftime(std::time(0), start1) <=0.5);
        return order_dls;
    }
}

std::vector<std::shared_ptr<Node>> bidirectional(std::shared_ptr<Node> node , int goal_id)
{
    std::vector<std::shared_ptr<Node>> order;

    node->make_childs();
    std::vector<int> all_id_source;
    all_id_source.push_back(node->id);
    std::vector<std::shared_ptr<Node>> childs_in_this_row_source{node->childs};
    std::vector<std::shared_ptr<Node>> childs_in_later_row_source;
    for (size_t i{0} ; i < childs_in_this_row_source.size() ; i++)
    {
        all_id_source.push_back(childs_in_this_row_source[i]->id);
    }

    std::vector<std::vector<int>> members;
    int pow{8};
    for (int i{0} ; i < 3 ; i++)
    {
        std::vector<int> row;
        for (int j{0} ; j < 3 ; j++)
        {
            int p = std::pow(10,pow);
            int num = int(goal_id/p);
            goal_id = goal_id - (p*num);
            row.push_back(num);
            pow--;
        }
        members.push_back(row);
    }
    
    std::shared_ptr<Node> goal_node{std::make_shared<Node>(members)};
    goal_node->make_childs();
    std::vector<int> all_id_goal;
    all_id_goal.push_back(goal_node->id);
    std::vector<std::shared_ptr<Node>> childs_in_this_row_goal{goal_node->childs};
    std::vector<std::shared_ptr<Node>> childs_in_later_row_goal;
    for (size_t i{0} ; i < childs_in_this_row_goal.size() ; i++)
    {
        all_id_goal.push_back(childs_in_this_row_goal[i]->id);
    }

    while (true)
    {
        for (size_t n{0} ; n < childs_in_this_row_source.size() ; n++)
        {
            for (size_t m{0} ; m < childs_in_this_row_goal.size() ; m++)
            {
                if (childs_in_this_row_source[n]->id == childs_in_this_row_goal[m]->id)
                {
                    std::vector<std::shared_ptr<Node>> g_order;
                    std::shared_ptr<Node> _parent = childs_in_this_row_goal[m];
                    while (true)
                    {
                        if (_parent->parent == nullptr)
                        {
                            break;
                        }
                        else
                        {
                            g_order.push_back(_parent);
                            _parent = _parent->parent;
                        }
                        
                    }

                    for (size_t n{0} ; n < g_order.size() ; n++)
                    {
                        order.push_back(g_order[g_order.size()-n-1]);
                    }

                    _parent = childs_in_this_row_source[n]->parent;
                    while (true)
                    {
                         if (_parent->parent == nullptr)
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

                if (childs_in_this_row_source[n]->id == childs_in_this_row_goal[m]->parent->id)
                {
                    std::vector<std::shared_ptr<Node>> g_order;
                    std::shared_ptr<Node> _parent = childs_in_this_row_goal[m]->parent;
                    while (true)
                    {
                        if (_parent->parent == nullptr)
                        {
                            break;
                        }
                        else
                        {
                            g_order.push_back(_parent);
                            _parent = _parent->parent;
                        }
                        
                    }

                    for (size_t n{0} ; n < g_order.size() ; n++)
                    {
                        order.push_back(g_order[g_order.size()-n-1]);
                    }

                    _parent = childs_in_this_row_source[n]->parent;
                    while (true)
                    {
                         if (_parent->parent == nullptr)
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
                
                
            }
        }

        for (size_t i{0} ; i < childs_in_this_row_source.size() ; i++)
        {
            childs_in_this_row_source[i]->make_childs();
            for (size_t j{0} ; j < childs_in_this_row_source[i]->childs.size() ; j++)
            {
                bool exist = false;
                for (size_t o{0} ; o < all_id_source.size() ; o++)
                {
                    if (all_id_source[o] == childs_in_this_row_source[i]->childs[j]->id)
                    {
                        exist = true;
                        break;
                    }
                }
                if(exist == false && childs_in_this_row_source[i]->childs[j]->id != childs_in_this_row_source[i]->parent->id ) 
                {
                    childs_in_later_row_source.push_back(childs_in_this_row_source[i]->childs[j]);
                    all_id_source.push_back(childs_in_this_row_source[i]->childs[j]->id);
                }
            }   
        }
        
        childs_in_this_row_source.clear();
        childs_in_this_row_source = childs_in_later_row_source;
        childs_in_later_row_source.clear();
        for (size_t n{0} ; n < childs_in_this_row_goal.size() ; n++)
        {
            childs_in_this_row_goal[n]->make_childs();
            for (size_t m{0} ; m < childs_in_this_row_goal[n]->childs.size() ; m++)
            {
                bool exist = false;
                for (size_t o{0} ; o < all_id_goal.size() ; o++)
                {
                    if (all_id_goal[o] == childs_in_this_row_goal[n]->childs[m]->id)
                    {
                        exist = true;
                        break;
                    }
                }
                if(exist == false && childs_in_this_row_goal[n]->childs[m]->id != childs_in_this_row_goal[n]->parent->id ) 
                {
                    childs_in_later_row_goal.push_back(childs_in_this_row_goal[n]->childs[m]);
                    all_id_goal.push_back(childs_in_this_row_goal[n]->childs[m]->id);
                }
            }   
        }
        
        childs_in_this_row_goal.clear();
        childs_in_this_row_goal = childs_in_later_row_goal;
        childs_in_later_row_goal.clear();
    }
    
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
    while (true)
    {
        node->random();
        if (node->solvable() == true)
        {
            break;
        }
    } 
    std::cout << "\033[1m\033[36m" <<  "I chose a random puzzle"<< "\n" << "\033[0m" << std::endl;
    node->show();
    if (node->solvable() == false)
    {
        std::time_t start = time(0);
        while( difftime(std::time(0), start) <=0.5 );
        std::cout << "\033[1m\033[31m" << "This Puzzle is not solvable" << "\033[0m" << std::endl;
        std::time_t start1 = time(0);
        while( difftime(std::time(0), start1) <=0.5 );
        std::cout << "\033[1m\033[32m" << "\n-------Done--------" << "\033[0m" << std::endl;
        return;
    }
    std::time_t start1 = time(0);
    while( difftime(std::time(0), start1) <=1);
    std::cout << "\033[1m\033[36m" << "Choose the solution method" << std::endl;
    std::cout << "\033[1m\033[35m" << "1 : Breath First Search (BFS)" << std::endl;
    std::cout << "2 : Depth Limited Search (DLS) " << std::endl;
    std::cout << "3 : The best algorithm to solve this puzzle (BFS or DLS)" << std::endl;
    std::cout << "4 : Bidirectional" << "\033[0m" << std::endl;
    std::cout << "\033[1m\033[34m" << "\nWhats Your Command : ";
    int type;
    std::cin >> type;
    std::cout << "\n" << "\033[0m";
    std::vector<std::shared_ptr<Node>> order;
    if (type == 1)
    {
        order = solve_puzzle_bfs(node);
    }

    if (type == 2)
    {
        size_t lim;
        std::cout << "\033[1m\033[34m" << "\nEnter the search limits : ";
        std::cin >> lim;
        std::cout << "\n" << "\033[0m";
        order = solve_puzzle_dls(node,lim);
    }

    if (type == 3)
    {
        order = faster(node);
    }

    if (type == 4)
    {
        order = bidirectional(node);
    }
    

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
    std::cout << "\033[1m\033[37m" << "for example" << std::endl;
    std::cout << "5   3   2 \n1   8   6  ------> 532186704\n7       4" << "\033[0m" << std::endl;
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
    if (node->solvable() == false)
    {
        std::time_t start = time(0);
        while( difftime(std::time(0), start) <=0.5 );
        std::cout << "\033[1m\033[31m" << "This Puzzle is not solvable" << "\033[0m" << std::endl;
        std::time_t start1 = time(0);
        while( difftime(std::time(0), start1) <=0.5 );
        std::cout << "\033[1m\033[32m" << "\n-------Done--------" << "\033[0m" << std::endl;
        return;
    }
    std::time_t start2 = time(0);
    while( difftime(std::time(0), start2) <=1);
    std::cout << "\033[1m\033[36m" << "Choose the solution method" << std::endl;
    std::cout << "\033[1m\033[35m" << "1 : Breath First Search (BFS)" << std::endl;
    std::cout << "2 : Depth Limited Search (DLS) " << std::endl;
    std::cout << "3 : The best algorithm to solve this puzzle (BFS or DLS)" << std::endl;
    std::cout << "4 : Bidirectional" << "\033[0m" << std::endl;
    std::cout << "\033[1m\033[34m" << "\nWhats Your Command : ";
    int type;
    std::cin >> type;
    std::cout << "\n" << "\033[0m";
    std::vector<std::shared_ptr<Node>> order;
    if (type == 1)
    {
        order = solve_puzzle_bfs(node);
    }

    if (type == 2)
    {
        size_t lim;
        std::cout << "\033[1m\033[34m" << "\nEnter the search limits : ";
        std::cin >> lim;
        std::cout << "\n" << "\033[0m";
        order = solve_puzzle_dls(node,lim);
    }

    if (type == 3)
    {
        order = faster(node);
    }

    if (type == 4)
    {
        order = bidirectional(node);
    }

    if (order.size() == 0)
    {
        std::cout << "\033[1m\033[31m" << "This Puzzle is not solvable" << "\033[0m" << std::endl;
        return;
    }
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

    std::cout << "\033[1m\033[32m" << "\n-------Done--------" << "\033[0m" << std::endl;
    std::time_t start3 = time(0);
    while( difftime(std::time(0), start3) <=1 );
}

void solve_puzzle_by_your_self()
{
    std::cout << "\033[1m\033[36m" << "I give you a puzzle and you have to solve it" << std::endl;
    std::time_t start = time(0);
    while( difftime(std::time(0), start) <=1.5);
    std::cout << "You can change the puzzle with the following guide" << "\033[0m" << std::endl;
    std::cout << "\033[1m\033[33m" << "            UP         \n           8,w         " << std::endl;
    std::cout << "LEFT 4,a         d,6 RIGHT" << std::endl;
    std::cout << "           2,s     \n          DOWN         " << "\033[0m" << std::endl;
    std::cout << "\033[1m\033[36m" << "For example, if you select down, the number above the blank field will go down" << std::endl;
    std::cout << "If you are tired, enter 0" << std::endl;
    std::time_t start1 = time(0);
    while( difftime(std::time(0), start1) <=1.5);
    std::cout << "Let's go" << "\033[0m" << std::endl;
    std::cout << "\033[1m\033[30m" << "-----------------------------" << "\033[0m" << std::endl;
    std::cout << "\033[1m\033[35m" << "This is a puzzle that I want you to solve" << "\033[0m" << std::endl;

    int goal_id = 123456780;
    std::shared_ptr<Node> node{std::make_shared<Node>()};
    while (true)
    {
        node->random();
        if (node->solvable() == true)
        {
            break;
        }
    }   
    while (true)
    {
        if (node->id == goal_id)
        {
            node->show();
            std::cout << "\033[1m\033[30m" << "------------------------" << "\033[0m" << std::endl;
            std::cout << "\033[1m\033[32m" << "-------GOOD JOB------" << "\033[0m" << std::endl;
            std::time_t start1 = time(0);
            while( difftime(std::time(0), start1) <=1.5);
            return;
        }
        node->show();
        std::cout << "\033[1m\033[30m" << "------------------------" << "\033[0m" << std::endl;
        std::cout << "\033[1m\033[34m" << "Choose a move : ";
        std::string cm;
        std::cin >> cm;
        std::cout << "\033[0m";
        if (cm == "0")
        {
            std::cout << "\033[1m\033[30m" << "Please wait for me to try" << "\033[0m" << std::endl;
            std::vector<int> row1 = {1,2,3};
            std::vector<int> row2 = {4,5,6};
            std::vector<int> row3 = {7,8,0};
            std::vector<std::vector<int>> goal_members;
            goal_members.push_back(row1);
            goal_members.push_back(row2);
            goal_members.push_back(row3);
            std::shared_ptr<Node> goal_node{std::make_shared<Node>(goal_members)};
            std::vector<std::shared_ptr<Node>> order;
            if (node->solvable() == false)
            {
                std::cout << "\033[1m\033[31m" << "This Puzzle is not solvable" << "\033[0m" << std::endl;
                return;                
            }
            order = bidirectional(node);
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
            while( difftime(std::time(0), start) <=1);
            return;
        }
        else if (cm == "8" || cm == "w")
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
        else if (cm == "4" || cm == "a")
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
        else if (cm == "6" || cm == "d")
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
        else if (cm == "2" || cm == "s")
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
    }
}

void solve_random_puzzle_with_special_goal()
{
    std::string pattern;
    std::cout << "\033[1m\033[37m" << "for example" << std::endl;
    std::cout << "5   3   2 \n1   8   6  ------> 532186704\n7       4" << "\033[0m" << std::endl;
    std::cout << "\033[1m\033[34m" << "You must enter your Special Goal : ";
    std::cin >> pattern;
    std::cout << "\033[0m";
    std::stringstream geek(pattern);
    int goal_id; 
    geek >> goal_id;

    int goal_id_n = goal_id;
    std::vector<std::vector<int>> members;
    int pow{8};
    for (int i{0} ; i < 3 ; i++)
    {
        std::vector<int> row;
        for (int j{0} ; j < 3 ; j++)
        {
            int p = std::pow(10,pow);
            int num = int(goal_id_n/p);
            goal_id_n = goal_id_n - (p*num);
            row.push_back(num);
            pow--;
        }
        members.push_back(row);
    }
    
    std::shared_ptr<Node> goal_node{std::make_shared<Node>(members)};

    std::shared_ptr<Node> node{std::make_shared<Node>()};
    node->random();
    std::cout << "\033[1m\033[36m" <<  "I chose a random puzzle"<< "\n" << "\033[0m" << std::endl;
    node->show();
    if (node->solvable() != goal_node->solvable())
    {
        std::time_t start1 = time(0);
        while( difftime(std::time(0), start1) <=1);
        std::cout << "\033[1m\033[31m" << "This Puzzle is not solvable" << "\033[0m" << std::endl;   
        std::cout << "\033[1m\033[32m" << "\n-------Done--------" << "\033[0m" << std::endl;
        std::time_t start2 = time(0);
        while( difftime(std::time(0), start2) <=1);
        return;
    }
    std::cout << "\033[1m\033[36m" << "Choose the solution method" << std::endl;
    std::cout << "\033[1m\033[35m" << "1 : Breath First Search (BFS)" << std::endl;
    std::cout << "2 : Depth Limited Search (DLS) " << std::endl;
    std::cout << "3 : The best algorithm to solve this puzzle (BFS or DLS)" << std::endl;
    std::cout << "4 : Bidirectional" << "\033[0m" << std::endl;
    std::cout << "\033[1m\033[34m" << "\nWhats Your Command : ";
    int type;
    std::cin >> type;
    std::cout << "\n" << "\033[0m";
    std::vector<std::shared_ptr<Node>> order;
    if (type == 1)
    {
        order = solve_puzzle_bfs(node,goal_id);
    }

    if (type == 2)
    {
        size_t lim;
        std::cout << "\033[1m\033[34m" << "\nEnter the search limits : ";
        std::cin >> lim;
        std::cout << "\n" << "\033[0m";
        order = solve_puzzle_dls(node,lim,goal_id);
    }

    if (type == 3)
    {
        order = faster(node,goal_id);
    }

    if (type == 4)
    {
        order = bidirectional(node,goal_id);
    }
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
    while( difftime(std::time(0), start) <=1);
}

void solve_your_puzzle_with_special_goal()
{
    std::string pattern;
    std::cout << "\033[1m\033[37m" << "for example" << std::endl;
    std::cout << "5   3   2 \n1   8   6  ------> 532186704\n7       4" << "\033[0m" << std::endl;
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

    std::string pattern_n;
    std::cout << "\033[1m\033[34m" << "You must enter your Special Goal : ";
    std::cin >> pattern_n;
    std::cout << "\033[0m";
    std::stringstream geek_n(pattern_n);
    int goal_id; 
    geek_n >> goal_id;

    int goal_id_n = goal_id;
    std::vector<std::vector<int>> members_n;
    int pow_n{8};
    for (int i{0} ; i < 3 ; i++)
    {
        std::vector<int> row;
        for (int j{0} ; j < 3 ; j++)
        {
            int p = std::pow(10,pow_n);
            int num = int(goal_id_n/p);
            goal_id_n = goal_id_n - (p*num);
            row.push_back(num);
            pow_n--;
        }
        members_n.push_back(row);
    }
    std::shared_ptr<Node> goal_node{std::make_shared<Node>(members_n)};
    if (node->solvable() != goal_node->solvable())
    {
        std::time_t start1 = time(0);
        while( difftime(std::time(0), start1) <=1);
        std::cout << "\033[1m\033[31m" << "This Puzzle is not solvable" << "\033[0m" << std::endl;   
        std::cout << "\033[1m\033[32m" << "\n-------Done--------" << "\033[0m" << std::endl;
        std::time_t start2 = time(0);
        while( difftime(std::time(0), start2) <=1);
        return;
    }
    std::cout << "\033[1m\033[36m" << "Choose the solution method" << std::endl;
    std::cout << "\033[1m\033[35m" << "1 : Breath First Search (BFS)" << std::endl;
    std::cout << "2 : Depth Limited Search (DLS) " << std::endl;
    std::cout << "3 : The best algorithm to solve this puzzle (BFS or DLS)" << std::endl;
    std::cout << "4 : Bidirectional" << "\033[0m" << std::endl;
    std::cout << "\033[1m\033[34m" << "\nWhats Your Command : ";
    int type;
    std::cin >> type;
    std::cout << "\n" << "\033[0m";
    std::vector<std::shared_ptr<Node>> order;
    if (type == 1)
    {
        order = solve_puzzle_bfs(node,goal_id);
    }

    if (type == 2)
    {
        size_t lim;
        std::cout << "\033[1m\033[34m" << "\nEnter the search limits : ";
        std::cin >> lim;
        std::cout << "\n" << "\033[0m";
        order = solve_puzzle_dls(node,lim,goal_id);
    }

    if (type == 3)
    {
        order = faster(node,goal_id);
    }

    if (type == 4)
    {
        order = bidirectional(node,goal_id);
    }
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
    while( difftime(std::time(0), start) <=1);
}