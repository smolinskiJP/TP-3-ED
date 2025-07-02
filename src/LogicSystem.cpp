#include "LogicSystem.hpp"

//Funcao de processar uma linha de entrada
void LogicSystem::ProccessLine(const std::string& line) {
    //Usa a linha como arquivo
    std::stringstream string_file(line);
    long long timestamp;
    std::string line_type;
    //Pega o tempo e tipo de evento a ser processado
    string_file >> timestamp >> line_type;

    //Decide se vai chamar o processador de evento, consulta de cliente ou consulta de pacote
    if (line_type == EVENT) this->ProccessEvent(string_file, timestamp);
    else if (line_type == CLIENT) this->ProccessClient(string_file, timestamp);
    else if (line_type == PACKAGE) this->ProccessPackage(string_file, timestamp);
    else if (line_type == STORAGE) this->ProccessStorage(string_file, timestamp);
}

//Funcao que processa um evento
void LogicSystem::ProccessEvent(std::stringstream& string_file, long long timestamp) {
    std::string type;
    int id;
    //Pega o tipo de evento de id do pacote
    string_file >> type >> id;
    Event event(timestamp, type, id);
    std::string sender, receiver;
    int origin, destiny, division;

    //Dado o tipo, pega as entradas restantes
    switch (event.GetType()) {
        case RG: //Registro
            string_file >> sender >> receiver >> origin >> destiny;
            event.SetSender(sender); event.SetReceiver(receiver); event.SetOrigin(origin); event.SetDestiny(destiny); break;
        case AR: //Armazenamento
        case RM: //Remocao
        case UR: //Rearmazenamento
            string_file >> destiny >> division;
            event.SetDestiny(destiny); event.SetDivision(division); break;
        case TR: //Transporte
            string_file >> origin >> destiny;
            event.SetOrigin(origin); event.SetDestiny(destiny); break;
        case EN: //Entrega
            string_file >> destiny;
            event.SetDestiny(destiny); break;
        default: return;
    }

    //Adiciona o evento no array dinamico 
    this->_events.Push(event);
    int new_index = this->_events.GetSize() - 1;

    //Tenta pegar o array de eventos relacionado ao pacote
    DynamicArray<int>* pack;
    try {
        pack = this->_packages.Find(event.GetId());
    }
    catch (const std::logic_error& e) { 
        //Caso nao exista pacote com esse id, cria o vetor
        pack = new DynamicArray<int>();
    }

    //Adiciona o index do novo evento no fim do vetor do pacote
    pack->Push(new_index);
    //Retorna o vetor de pacotes pra AVL
    this->_packages.Insert(event.GetId(), pack);

    //Se for evento novo, atualiza os clientes
    if (event.GetType() == RG) {
        //Tenta pegar o array de pacotes relacionado ao remetente
        DynamicArray<int>* sender;
        try {
            sender = this->_clients.Find(event.GetSender());
        }
        catch (const std::logic_error& e) {
            //Caso nao exista, cria o vetor relacionado ao remetente
            sender = new DynamicArray<int>();
        }

        //Adiciona o id do pacote ao fim do remetente
        sender->Push(event.GetId());
        //Retorna o remetente a AVL
        this->_clients.Insert(event.GetSender(), sender);

        //Tenta pegar o array de pacotes relacionado ao destinatario
        DynamicArray<int>* receiver;
        try {
            receiver = this->_clients.Find(event.GetReceiver());
        }
        catch (const std::logic_error& e) {
            //Caso nao exista, cria o vetor relacionado ao destinatario
            receiver = new DynamicArray<int>();
        }

        //Adiciona o id do pacote ao fim do destinatario
        receiver->Push(event.GetId());
        //Retorna o destinatario a AVL
        this->_clients.Insert(event.GetReceiver(), receiver);
    }
}

//Funcao que processa uma consulta de pacote
void LogicSystem::ProccessPackage(std::stringstream& string_file, long long timestamp) {
    int id;
    //Pega o id do pacote a ser consultado
    string_file >> id;
    //Imprime o log da "Query"
    std::cout << std::setw(6) << std::setfill('0') << timestamp << " PC " << std::setw(3) << std::setfill('0') << id << std::endl;

    //Pega o array de indices de eventos relacionado ao pacote
    DynamicArray<int>* pack;
    try {
        pack = this->_packages.Find(id);
    }
    catch (const std::logic_error& e) { 
        //Nao existe pacote com esse id, aborta consulta
        std::cout << 0 << std::endl;
        return;
    }

    //Cria o array de eventos a serem impressos
    DynamicArray<int> pack_events;
    //Para cada index de evento, verifica se sera impresso ou nao
    for (int i = 0; i < pack->GetSize(); i++) {

        //Pega o evento relacionado
        int event_index = (*pack)[i];
        Event event = this->_events[event_index];

        //Como os eventos de cada pacote esta ordenado naturalmente, quando encontra o primeiro que passou do tempo requisitado encerra a pesquisa
        if (event.GetTime() > timestamp) break;

        //Adiciona o index do evento no array a ser impresso
        pack_events.Push(event_index);
    }

    //Imprime a quantidade de linhas do log
    std::cout << pack_events.GetSize() << std::endl;
    for (int i = 0; i < pack_events.GetSize(); i++) {
        //Imprime cada evento
        this->_events[pack_events[i]].Print();
    }
}

//Funcao que processa uma consulta de cliente
void LogicSystem::ProccessClient(std::stringstream& string_file, long long timestamp) {
    std::string client_name;
    //Pega o nome do cliente
    string_file >> client_name;
    //Imprime o log da "Query"
    std::cout << std::setw(6) << std::setfill('0') << timestamp << " CL " << client_name << std::endl;

    //Tenta pegar os ids dos pacotes
    DynamicArray<int>* client;
    try {
        client = this->_clients.Find(client_name);
    }
    catch (const std::logic_error& e) {
        //Caso nao exista o cliente, aborta a consulta
        std::cout << 0 << std::endl;
        return;
    }

    //Cria o array de eventos a serem impressos
    DynamicArray<Event> client_packs;
    //Itera sobre cada pacote relacionado ao cliente
    for (int i = 0; i < client->GetSize(); i++) {
        int pack_id = (*client)[i];
        DynamicArray<int>* pack;

        //Tenta pegar o array de index de eventos do pacote
        try {
            pack = this->_packages.Find(pack_id);
        }
        catch (const std::logic_error& e) { 
            //Se nao encontrar o pacote (erro inesperado), continua sem ele
            continue;
        }

        //Adiciona o primeiro evento (registro)
        int reg_index = (*pack)[0];
        Event first = this->_events[reg_index];
        if (first.GetTime() < timestamp) client_packs.Push(first);

        //Procura o ultimo evento do pacote antes do timestamp
        Event last_seen;        
        for (int j = 1; j < pack->GetSize(); j++) {
            int event_index = (*pack)[j];
            Event event = this->_events[event_index];
            if (event.GetTime() > timestamp) break;
            last_seen = event;
        }
        //Se encontrou algum evento adiciona nos eventos a serem impressos
        if (last_seen.GetId() != -1) {
            client_packs.Push(last_seen);
        }
    }

    //Ordena os eventos em ordem cronologica
    client_packs.Sort();

    //Imprime a quantidade de linhas do log
    std::cout << client_packs.GetSize() << std::endl;
    for (int i = 0; i < client_packs.GetSize(); i++) {
        //Imprime cada evento
        client_packs[i].Print();
    }
}

//Funcao que processa uma consulta de tempo em armazem
void LogicSystem::ProccessStorage(std::stringstream& string_file, long long timestamp){
    long long start_time, stop_time;
    int store_id;
    //Pega o tempo de inicio e fim do periodo consultado alem do armazem
    string_file >> start_time >> stop_time >> store_id;
    //Imprime o log da "Query"
    std::cout << std::setw(6) << std::setfill('0') << timestamp << " AM " 
        << std::setw(6) << std::setfill('0') << start_time << " "
        << std::setw(6) << std::setfill('0') << stop_time << " "
        << std::setw(3) << std::setfill('0') << store_id << std::endl;
    
    //Cria o array de eventos a serem impressos
    DynamicArray<int> time_events;

    //O indice de inicio inicia com valor -1 como flag
    int start = -1;

    //Inicia os limites da busca binaria
    int low = 0, high = this->_events.GetSize() - 1;

    //Enquanto ainda nao convergir
    while(low <= high){
        //Acha o valor central
        int mid = (low + high) / 2;
        //Se o tempo do evento for maior do que o tempo de inicio atualiza o indice de inicio e diminui o teto da busca
        if(this->_events[mid].GetTime() >= start_time){
            start = mid;
            high = mid - 1;
        }
        else {
        //Caso contrario aumenta o piso da busca
            low = mid + 1;
        }
    }

    //Se nao tiver encontrado nenhum evento a partir do start_time imprime 0 logs
    if(start == -1){
        std::cout << 0 << std::endl;
        return;
    }

    //Todos os eventos no intervalo estao a partir do indice de inicio
    for(int i = start + 1; i < this->_events.GetSize(); i++){
        //Pega o evento relativo
        Event event = this->_events[i];

        //Se tiver passado do tempo de parada, encerra a consulta
        if(event.GetTime() > stop_time) break;


        //Dado o evento, devemos filtrar para saber se esta envolvido no armazem que desejamos
        /*Vamos considerar movimentos em um armazem:
        Eventos:
        - TR, armazem de origem (Parte do armazem).
        - RM, armazem de destino (Chega no armazem).
        - UR, armazem de destino (Chega no armazem).
        - AR, armazem de destino (Chega no armazem).
        - EN, armazem de destino (Chega no armazem).

        Para o registro, nao sera considerado uma movimentacao de armazem
        */
        switch(event.GetType()){
            case TR: //Transporte
                if(event.GetOrigin() == store_id) time_events.Push(i);
                break;
            case RM: //Remocao
            case UR: //Rearmazenamento
            case AR: //Armazenamento
            case EN: //Entrega
                if(event.GetDestiny() == store_id) time_events.Push(i);
                break;
            default: break; //Registro e outros caem aqui    
        }
    }

    //Com todos os eventos que vamos imprimir, imprimimos o numero de linhas do log
    std::cout << time_events.GetSize() << std::endl;
    for (int i = 0; i < time_events.GetSize(); i++) {
        //Imprime cada evento
        this->_events[time_events[i]].Print();
    }
}

//Construtor padrao
LogicSystem::LogicSystem() {}

//Destrutor padrao
LogicSystem::~LogicSystem() {}

//Inicia o sistema de ler do arquivo e processar a linha
void LogicSystem::Run(std::ifstream& inFile) {
    std::string line;
    //Processa linhas enquanto ainda consegue pegar elas do arquivo
    while (std::getline(inFile, line)) if (!line.empty()) ProccessLine(line);
}

//Inicia o sistema de ler do terminal e processar a linha
void LogicSystem::Run() {
    std::string line;
    //Processa linhas enquanto nao forem vazias
    while (std::getline(std::cin, line)) {
        if (!line.empty()) ProccessLine(line);
        else return;
    }
}