#include "Event.hpp"

//Construtor padrao de evento, recebe tempo, tipo e id do pacote relacionado.
Event::Event(long long time, std::string type, int id) :
    _time(time), _type(StringToType(type)), _id(id), _origin(-1), _destiny(-1), _division(-1) {
}

//Construtor padrao de evento, inicia todos os atributos com valores padrao.
Event::Event() :
    _time(-1), _type(NOT_VALID), _id(-1), _origin(-1), _destiny(-1), _division(-1) {
}

//Destrutor padrao de evento.
Event::~Event() {}

//Funcao de impressao de um evento
void Event::Print() {
    //Com base no tipo de evento, imprime com os atributos necessarios
    switch (this->GetType()) {
        case RG: //Registro
            std::cout << std::setw(7) << std::setfill('0') << this->_time << " EV RG "
                << std::setw(3) << std::setfill('0') << this->_id << " "
                << this->_sender << " " << this->_receiver << " "
                << std::setw(3) << std::setfill('0') << this->_origin << " "
                << std::setw(3) << std::setfill('0') << this->_destiny << std::endl;
            break;
        case AR: //Armazenamento
            std::cout << std::setw(7) << std::setfill('0') << this->_time << " EV AR "
                << std::setw(3) << std::setfill('0') << this->_id << " "
                << std::setw(3) << std::setfill('0') << this->_destiny << " "
                << std::setw(3) << std::setfill('0') << this->_division << std::endl;
            break;
        case RM: //Remocao
            std::cout << std::setw(7) << std::setfill('0') << this->_time << " EV RM "
                << std::setw(3) << std::setfill('0') << this->_id << " "
                << std::setw(3) << std::setfill('0') << this->_destiny << " "
                << std::setw(3) << std::setfill('0') << this->_division << std::endl;
            break;
        case UR: //Rearmazenamento
            std::cout << std::setw(7) << std::setfill('0') << this->_time << " EV UR "
                << std::setw(3) << std::setfill('0') << this->_id << " "
                << std::setw(3) << std::setfill('0') << this->_destiny << " "
                << std::setw(3) << std::setfill('0') << this->_division << std::endl;
            break;
        case TR: //Transporte
            std::cout << std::setw(7) << std::setfill('0') << this->_time << " EV TR "
                << std::setw(3) << std::setfill('0') << this->_id << " "
                << std::setw(3) << std::setfill('0') << this->_origin << " "
                << std::setw(3) << std::setfill('0') << this->_destiny << std::endl;
            break;
        case EN: //Entrega
            std::cout << std::setw(7) << std::setfill('0') << this->_time << " EV EN "
                << std::setw(3) << std::setfill('0') << this->_id << " "
                << std::setw(3) << std::setfill('0') << this->_destiny << std::endl;
            break;
        default: break;
    }
}

//Retorna o tempo do evento
long long Event::GetTime() {
    return this->_time;
}

//Retorna o tipo do evento
EventType Event::GetType() {
    return this->_type;
}

//Retorna o identificador do pacote ligado ao evento
int Event::GetId() {
    return this->_id;
}

//Define a origem do pacote
void Event::SetOrigin(int value) {
    this->_origin = value;
}

//Define o destino do pacote
void Event::SetDestiny(int value) {
    this->_destiny = value;
}

//Define a secao de armazem do pacote
void Event::SetDivision(int value) {
    this->_division = value;
}

//Retorna o remetente do pacote
std::string Event::GetSender() {
    return this->_sender;
}

//Define o remetente do pacote
void Event::SetSender(std::string value) {
    this->_sender = value;
}

//Retorna o destinatario do pacote
std::string Event::GetReceiver() {
    return this->_receiver;
}

//Define o destinatario do pacote
void Event::SetReceiver(std::string value) {
    this->_receiver = value;
}

//Converte uma String em um tipo de evento
EventType Event::StringToType(const std::string& s) {
    if (s == "RG") return RG;
    if (s == "AR") return AR;
    if (s == "RM") return RM;
    if (s == "UR") return UR;
    if (s == "TR") return TR;
    if (s == "EN") return EN;
    return NOT_VALID;
}

//Sobrecarga da operacao de atribuicao
Event& Event::operator=(const Event& other) {
    if (this == &other) return *this;

    //Copia todos os atributos
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

//Sobrecarga da operacao de "menor que"
bool Event::operator<(const Event& other) {
    //Primeiramente verifica o tempo
    if (this->_time < other._time) return true;
    if (this->_time > other._time) return false;

    //Caso o tempo seja igual, verifica o identificador
    if (this->_id < other._id) return true;
    return false;
}

//Sobrecarga da operacao de "maior que"
bool Event::operator>(const Event& other) {
    //Primeiramente verifica o tempo
    if (this->_time > other._time) return true;
    if (this->_time < other._time) return false;

    //Caso o tempo seja igual, verifica o identificador
    if (this->_id > other._id) return true;
    return false;
}