#ifndef LOGIC_SYSTEM_HPP
#define LOGIC_SYSTEM_HPP

#define EVENT "EV"
#define CLIENT "CL"
#define PACKAGE "PC"

#include <iostream>
#include <fstream>
#include <sstream>
#include "AVL.hpp"
#include "Event.hpp"
#include "DinamicArray.hpp"

class LogicSystem{
    private:
        DinamicArray<Event>* _events;
        //AVL<> _packages;
        //AVL<> _clients;
    
        void ProccessLine(const std::string& line);
        void ProccessEvent(std::stringstream& string_file, long long timestamp);
        void ProccessClient(std::stringstream& string_file, long long timestamp);
        void ProccessPackage(std::stringstream& string_file, long long timestamp);
    public:
        LogicSystem(std::ifstream& inFile);
        LogicSystem();
        ~LogicSystem();

        void Run();

};

#endif