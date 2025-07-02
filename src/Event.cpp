#include "Event.hpp"

Event::Event(long long time, std::string type, int id) :
    _time(time), _type(StringToType(type)), _id(id), _origin(-1), _destiny(-1), _division(-1) {
}

Event::Event() :
    _time(-1), _type(NOT_VALID), _id(-1), _origin(-1), _destiny(-1), _division(-1) {
}


Event::~Event() {}

void Event::Print() {
    switch (this->GetType()) {
    case RG:
        std::cout << std::setw(7) << std::setfill('0') << this->_time << " EV RG "
            << std::setw(3) << std::setfill('0') << this->_id << " "
            << this->_sender << " " << this->_receiver << " "
            << std::setw(3) << std::setfill('0') << this->_origin << " "
            << std::setw(3) << std::setfill('0') << this->_destiny << std::endl;
        break;
    case AR:
        std::cout << std::setw(7) << std::setfill('0') << this->_time << " EV AR "
            << std::setw(3) << std::setfill('0') << this->_id << " "
            << std::setw(3) << std::setfill('0') << this->_destiny << " "
            << std::setw(3) << std::setfill('0') << this->_division << std::endl;
        break;
    case RM:
        std::cout << std::setw(7) << std::setfill('0') << this->_time << " EV RM "
            << std::setw(3) << std::setfill('0') << this->_id << " "
            << std::setw(3) << std::setfill('0') << this->_destiny << " "
            << std::setw(3) << std::setfill('0') << this->_division << std::endl;
        break;
    case UR:
        std::cout << std::setw(7) << std::setfill('0') << this->_time << " EV UR "
            << std::setw(3) << std::setfill('0') << this->_id << " "
            << std::setw(3) << std::setfill('0') << this->_destiny << " "
            << std::setw(3) << std::setfill('0') << this->_division << std::endl;
        break;
    case TR:
        std::cout << std::setw(7) << std::setfill('0') << this->_time << " EV TR "
            << std::setw(3) << std::setfill('0') << this->_id << " "
            << std::setw(3) << std::setfill('0') << this->_origin << " "
            << std::setw(3) << std::setfill('0') << this->_destiny << std::endl;
        break;
    case EN:
        std::cout << std::setw(7) << std::setfill('0') << this->_time << " EV EN "
            << std::setw(3) << std::setfill('0') << this->_id << " "
            << std::setw(3) << std::setfill('0') << this->_destiny << std::endl;
        break;
    default: break;
    }
}

long long Event::GetTime() {
    return this->_time;
}
void Event::SetTime(long long value) {
    this->_time = value;
}

EventType Event::GetType() {
    return this->_type;
}
void Event::SetType(EventType value) {
    this->_type = value;
}

int Event::GetId() {
    return this->_id;
}
void Event::SetId(int value) {
    this->_id = value;
}

int Event::GetOrigin() {
    return this->_origin;
}
void Event::SetOrigin(int value) {
    this->_origin = value;
}

int Event::GetDestiny() {
    return this->_destiny;
}
void Event::SetDestiny(int value) {
    this->_destiny = value;
}

int Event::GetDivision() {
    return this->_division;
}
void Event::SetDivision(int value) {
    this->_division = value;
}

std::string Event::GetSender() {
    return this->_sender;
}
void Event::SetSender(std::string value) {
    this->_sender = value;
}

std::string Event::GetReceiver() {
    return this->_receiver;
}
void Event::SetReceiver(std::string value) {
    this->_receiver = value;
}

EventType Event::StringToType(const std::string& s) {
    if (s == "RG") return RG;
    if (s == "AR") return AR;
    if (s == "RM") return RM;
    if (s == "UR") return UR;
    if (s == "TR") return TR;
    if (s == "EN") return EN;
    return NOT_VALID;
}

Event& Event::operator=(const Event& other) {
    if (this == &other) return *this;

    this->_time = other._time;
    this->_type = other._type;
    this->_id = other._id;
    this->_origin = other._origin;
    this->_destiny = other._destiny;
    this->_division = other._division;
    this->_sender = other._sender;
    this->_receiver = other._receiver;

    return *this;
}

bool Event::operator<(const Event& other) {
    if (this->_time < other._time) return true;
    if (this->_time > other._time) return false;

    if (this->_id < other._id) return true;
    return false;
}

bool Event::operator>(const Event& other) {
    if (this->_time > other._time) return true;
    if (this->_time < other._time) return false;

    if (this->_id > other._id) return true;
    return false;
}