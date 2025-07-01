#include <iostream>
#include <fstream>

#define SUCESSO 0

int main(int argv, char ** argc){
    //Pega o arquivo passado por parâmetro (se existir)
    std::ifstream inFile(argc[1]);

    try{
        //Se nao tiver arquivo de entrada, chama o construtor de terminal
        if(!inFile.is_open());
        else;
    }
    catch (const std::runtime_error &e) {std::cerr << "Erro de leitura: " << e.what() << std::endl;}
    catch (const std::invalid_argument &e) {std::cerr << "Argumento invalido: " << e.what() << std::endl;}
    catch (const std::logic_error &e) {std::cerr << "Erro de logica: " << e.what() << std::endl;}
    catch (const std::exception &e) {std::cerr << "Erro de excecao: " << e.what() << std::endl;}


    //Fecha o arquivo
    inFile.close();

    //Encerra o programa com sucesso
    return SUCESSO;
}