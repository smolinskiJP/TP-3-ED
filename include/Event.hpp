#ifndef EVENT_HPP
#define EVENT_HPP

#include <iostream>

enum EventType{
    RG,
    AR,
    RM,
    UR,
    TR,
    EN,
    NOT_VALID
};

class Event{
    private:
        long long _time;
        EventType _type;
        int _id;
        std::string _client;

        int _origin;
        int _destiny;
        int _division;
        std::string _sender;
        std::string _receiver;

    public:
        Event(long long timestamp, std::string type, int id);
        ~Event();
        void Print();

        long long GetTime();
        void SetTime(long long value);

        EventType GetType();
        void SetType(EventType value);
        
        int GetId();
        void SetId(int value);

        int GetOrigin();
        void SetOrigin(int value);
        
        int GetDestiny();
        void SetDestiny(int value);
        
        int GetDivision();
        void SetDivision(int value);

        std::string GetSender();
        void SetSender(std::string value);

        std::string GetReceiver();
        void SetReceiver(std::string value);

        EventType StringToType(const std::string& s);
        
};

#endif