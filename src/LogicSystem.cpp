#include "LogicSystem.hpp"

void LogicSystem::ProccessLine(const std::string& line){
    std::stringstream string_file(line);
    long long timestamp;
    std::string line_type;
    string_file >> timestamp >> line_type;

    if(line_type == EVENT) ProccessEvent(string_file, timestamp);
    else if(line_type == CLIENT) ProccessClient(string_file, timestamp);
    else if(line_type == PACKAGE) ProccessPackage(string_file, timestamp);
}

void LogicSystem::ProccessEvent(std::stringstream& string_file, long long timestamp){
    std::string type;
    int id;
    string_file >> type >> id;
    Event event(timestamp, type, id);
    std::string sender, receiver;
    
    switch(event.GetType()){
        case RG:
            int origin, destiny;
            string_file >> sender >> receiver >> origin >> destiny;
            event.SetSender(sender); event.SetReceiver(receiver); event.SetOrigin(origin); event.SetDestiny(destiny); break;
        case AR:
        case RM:
        case UR:
            int destiny, division;
            string_file >> destiny >> division;
            event.SetDestiny(destiny); event.SetDivision(division); break;
        case TR:
            int origin, destiny;
            string_file >> origin >> destiny;
            event.SetOrigin(origin); event.SetDestiny(destiny); break;
        case EN:
            int destiny;
            string_file >> destiny;
            event.SetDestiny(destiny); break;
        default: return;
    }

    this->_events->Push(event);
    int new_index = this->_events->GetSize() - 1;
}

LogicSystem::LogicSystem(std::ifstream& inFile){
    std::string line;
    while(std::getline(inFile, line)) if(!line.empty()) ProccessLine(line);
}

LogicSystem::LogicSystem(){
    std::string line;
    while(std::getline(std::cin, line)) if(!line.empty()) ProccessLine(line);
}

LogicSystem::~LogicSystem(){
    
}

void LogicSystem::Run(){

}