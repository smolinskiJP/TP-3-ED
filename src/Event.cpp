#include "Event.hpp"

Event::Event(long long time, std::string type, int id) :
    _time(time), _type(StringToType(type)), _id(id){}

Event::~Event(){}

void Event::Print(){}

long long Event::GetTime(){
    return this->_time;
}
void Event::SetTime(long long value){
    this->_time = value;
}

EventType Event::GetType(){
    return this->_type;
}
void Event::SetType(EventType value){
    this->_type = value;
}

int Event::GetId(){
    return this->_id;
}
void Event::SetId(int value){
    this->_id = value;
}

int Event::GetOrigin(){
    return this->_origin;
}
void Event::SetOrigin(int value){
    this->_origin = value;
}

int Event::GetDestiny(){
    return this->_destiny;
}
void Event::SetDestiny(int value){
    this->_destiny = value;
}

int Event::GetDivision(){
    return this->_division;
}
void Event::SetDivision(int value){
    this->_division = value;
}

std::string Event::GetSender(){
    return this->_sender;
}
void Event::SetSender(std::string value){
    this->_sender = value;
}

std::string Event::GetReceiver(){
    return this->_receiver;
}
void Event::SetReceiver(std::string value){
    this->_receiver = value;
}

EventType Event::StringToType(const std::string& s){
    if(s == "RG") return RG;
    if(s == "AR") return AR;
    if(s == "RM") return RM;
    if(s == "UR") return UR;
    if(s == "TR") return TR;
    if(s == "EN") return EN;
    return NOT_VALID;
}