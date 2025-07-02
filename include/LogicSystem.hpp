#ifndef LOGIC_SYSTEM_HPP
#define LOGIC_SYSTEM_HPP

#define EVENT "EV"
#define CLIENT "CL"
#define PACKAGE "PC"
#define STORAGE "AM"

#include <iostream>
#include <fstream>
#include <sstream>
#include "AVL.hpp"
#include "Event.hpp"
#include "DynamicArray.hpp"

class LogicSystem {
private:
    DynamicArray<Event> _events;
    AVL<int, DynamicArray<int>*> _packages;
    AVL<std::string, DynamicArray<int>*> _clients;

    void ProccessLine(const std::string& line);
    void ProccessEvent(std::stringstream& string_file, long long timestamp);
    void ProccessClient(std::stringstream& string_file, long long timestamp);
    void ProccessPackage(std::stringstream& string_file, long long timestamp);
    void ProccessStorage(std::stringstream& string_file, long long timestamp);
public:
    LogicSystem();
    ~LogicSystem();

    void Run();
    void Run(std::ifstream& inFile);

};

#endif