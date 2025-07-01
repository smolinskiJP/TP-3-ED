#ifndef LOGIC_SYSTEM_HPP
#define LOGIC_SYSTEM_HPP

#include <iostream>
#include <fstream>
#include "AVL.hpp"
#include "Event.hpp"

class LogicSystem{
    private:

    
        void ProccessLine();
        void ProccessEvent();
        void ProccessClient();
        void ProccessItem();
    public:
        LogicSystem(std::ifstream& inFile);
        LogicSystem();
        ~LogicSystem();

        void Run();

};

#endif