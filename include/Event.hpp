#ifndef EVENT_HPP
#define EVENT_HPP

#include <iostream>
#include <iomanip>

//Enum dos tipos de evento que um evento pode assumir
enum EventType{
    RG, //Registro
    AR, //Armazenamento
    RM, //Remocao
    UR, //Rearmazenamento
    TR, //Transporte
    EN, //Entrega
    NOT_VALID //Tipo "Nulo"
};

class Event{
    private:
        long long _time;
        EventType _type;
        int _id;

        int _origin;
        int _destiny;
        int _division;
        std::string _sender;
        std::string _receiver;

    public:
        Event(long long timestamp, std::string type, int id);
        Event();
        ~Event();
        void Print();

        long long GetTime();
        EventType GetType();
        int GetId();

        void SetOrigin(int value);
        void SetDestiny(int value);
        void SetDivision(int value);

        std::string GetSender();
        void SetSender(std::string value);

        std::string GetReceiver();
        void SetReceiver(std::string value);

        EventType StringToType(const std::string& s);

        Event& operator=(const Event& other);
        bool operator<(const Event& other);
        bool operator>(const Event& other);
};

#endif