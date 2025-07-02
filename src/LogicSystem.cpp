#include "LogicSystem.hpp"

void LogicSystem::ProccessLine(const std::string& line) {
    std::stringstream string_file(line);
    long long timestamp;
    std::string line_type;
    string_file >> timestamp >> line_type;

    if (line_type == EVENT) ProccessEvent(string_file, timestamp);
    else if (line_type == CLIENT) ProccessClient(string_file, timestamp);
    else if (line_type == PACKAGE) ProccessPackage(string_file, timestamp);
}

void LogicSystem::ProccessEvent(std::stringstream& string_file, long long timestamp) {
    std::string type;
    int id;
    string_file >> type >> id;
    Event event(timestamp, type, id);
    std::string sender, receiver;
    int origin, destiny, division;

    switch (event.GetType()) {
        case RG:
            string_file >> sender >> receiver >> origin >> destiny;
            event.SetSender(sender); event.SetReceiver(receiver); event.SetOrigin(origin); event.SetDestiny(destiny); break;
        case AR:
        case RM:
        case UR:
            string_file >> destiny >> division;
            event.SetDestiny(destiny); event.SetDivision(division); break;
        case TR:
            string_file >> origin >> destiny;
            event.SetOrigin(origin); event.SetDestiny(destiny); break;
        case EN:
            string_file >> destiny;
            event.SetDestiny(destiny); break;
        default: return;
    }

    this->_events.Push(event);
    int new_index = this->_events.GetSize() - 1;
    DynamicArray<int>* pack;
    try {
        pack = this->_packages.Find(event.GetId());
    }
    catch (const std::logic_error& e) { //Nao existe pacote com esse id (cria seu vetor)
        pack = new DynamicArray<int>();
    }

    pack->Push(new_index);
    this->_packages.Insert(event.GetId(), pack);

    //Se for evento novo, atualiza os clientes
    if (event.GetType() == RG) {
        DynamicArray<int>* sender;
        try {
            sender = this->_clients.Find(event.GetSender());
        }
        catch (const std::logic_error& e) { //Nao existe cliente com esse nome (cria seu vetor)
            sender = new DynamicArray<int>();
        }

        sender->Push(event.GetId());
        this->_clients.Insert(event.GetSender(), sender);

        DynamicArray<int>* receiver;
        try {
            receiver = this->_clients.Find(event.GetReceiver());
        }
        catch (const std::logic_error& e) { //Nao existe cliente com esse nome (cria seu vetor)
            receiver = new DynamicArray<int>();
        }

        receiver->Push(event.GetId());
        this->_clients.Insert(event.GetReceiver(), receiver);
    }
}

void LogicSystem::ProccessPackage(std::stringstream& string_file, long long timestamp) {
    int id;
    string_file >> id;
    std::cout << std::setw(7) << std::setfill('0') << timestamp << " PC " << std::setw(3) << std::setfill('0') << id << std::endl;

    DynamicArray<int>* pack;
    try {
        pack = this->_packages.Find(id);
    }
    catch (const std::logic_error& e) { //Nao existe pacote com esse id, aborta consulta
        std::cout << 0 << std::endl;
        return;
    }

    DynamicArray<int> pack_events;
    for (int i = 0; i < pack->GetSize(); i++) {
        int event_index = (*pack)[i];
        Event event = this->_events[event_index];
        if (event.GetTime() > timestamp) break;
        pack_events.Push(event_index);
    }

    std::cout << pack_events.GetSize() << std::endl;
    for(int i = 0; i < pack_events.GetSize(); i++){
        this->_events[pack_events[i]].Print();
    }
}

void LogicSystem::ProccessClient(std::stringstream& string_file, long long timestamp){
    std::string client_name;
    string_file >> client_name;
    std::cout << std::setw(7) << std::setfill('0') << timestamp << " CL " << client_name << std::endl;

    DynamicArray<int>* client;
    try{
        client = this->_clients.Find(client_name);
    }
    catch(const std::logic_error& e){
        std::cout << 0 << std::endl;
        return;
    }

    DynamicArray<int> client_packs;
    for(int i = 0; i < client->GetSize(); i++){
        int pack_id = (*client)[i];
        DynamicArray<int>* pack;

        try {
            pack = this->_packages.Find(pack_id);
        }
        catch (const std::logic_error& e){ //Se nao encontrar o pacote (erro inesperado), continua sem ele
            continue;
        }

        //Adiciona o primeiro evento (registro)
        int reg_index = (*pack)[0];
        Event first = this->_events[reg_index];
        if(first.GetTime() < timestamp) client_packs.Push(reg_index);
    }

    for(int i = 0; i < client->GetSize(); i++){
        int pack_id = (*client)[i];
        DynamicArray<int>* pack;

        try {
            pack = this->_packages.Find(pack_id);
        }
        catch (const std::logic_error& e){ //Se nao encontrar o pacote (erro inesperado), continua sem ele
            continue;
        }
        if(pack->GetSize() == 1) continue; //Sem outro evento

        int last_seen = -1;
        for(int j = 1; j < pack->GetSize(); j++){  
            int event_index = (*pack)[i];
            Event event = this->_events[event_index];
            if (event.GetTime() > timestamp) break;
            last_seen = event_index;
        }
        if(last_seen != -1){
            client_packs.Push(last_seen);
        }
    }

    std::cout << client_packs.GetSize() << std::endl;
    for(int i = 0; i < client_packs.GetSize(); i++){
        this->_events[client_packs[i]].Print();
    }
}

LogicSystem::LogicSystem() {}


LogicSystem::~LogicSystem() {

}

void LogicSystem::Run(std::ifstream& inFile) {
    std::string line;
    while (std::getline(inFile, line)) if (!line.empty()) ProccessLine(line);
}

void LogicSystem::Run() {
    std::string line;
    while (std::getline(std::cin, line)) if (!line.empty()) ProccessLine(line);
}