#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

struct Evento {
    string descricao;
    int quant_pess_perm;
    string data_event;
    string hora_event;
    vector<string> inscritos;
};

unordered_map<string, Evento> eventos;
string tipo_usuario = "";

void menu_inicial() {
    while (true) {
        std::cout << "************** Controle de Eventos da UniFECAF **************\n";
        std::cout << "Informe seu perfil:\n";
        std::cout << "(1) Coordenador\n(2) Aluno\n";
        int escolha;
        std::cin >> escolha;
        if (escolha == 1) {
            tipo_usuario = "coordenador";
            break;
        }
        else if (escolha == 2) {
            tipo_usuario = "aluno";
            break;
        }
        else {
            std::cout << "Opção inválida. Tente novamente.\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}
void visualizar_eventos() {
    std::cout << "Eventos Atuais:\n";
    if (eventos.empty()) {
        std::cout << "Nenhum evento cadastrado.\n";
    }
    else {
        for (const auto& par : eventos) {
            const Evento& evento = par.second;
            std::string status_vagas = evento.inscritos.size() >= evento.quant_pess_perm ? "Lotado" : "Vagas Disponíveis";
            std::cout << "Evento: " << par.first << "\n";
            std::cout << "  Descrição: " << evento.descricao << "\n";
            std::cout << "  Quantidade de pessoas permitidas: " << evento.quant_pess_perm << "\n";
            std::cout << "  Data: " << evento.data_event << "\n";
            std::cout << "  Hora: " << evento.hora_event << "\n";
            std::cout << "  Inscritos: ";
            if (evento.inscritos.empty()) {
                std::cout << "Nenhum inscrito\n";
            }
            else {
                for (const std::string& inscrito : evento.inscritos) {
                    std::cout << inscrito << " ";
                }
                std::cout << "\n";
            }
            std::cout << "  Status: " << status_vagas << "\n\n";
        }
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void criar_evento() {
    while (true) {
        std::cout << "Digite o nome do evento: ";
        std::string nome_evento;
        std::cin.ignore();
        std::getline(std::cin, nome_evento);

        std::cout << "Digite a descrição do evento: ";
        std::string descricao;
        std::getline(std::cin, descricao);

        std::cout << "Quantidade de pessoas permitidas nesse evento: ";
        int quant_pess_perm;
        std::cin >> quant_pess_perm;

        std::cout << "Informe a data do evento: ";
        std::string data_event;
        std::cin.ignore();
        std::getline(std::cin, data_event);

        std::cout << "Informe a hora do evento: ";
        std::string hora_event;
        std::getline(std::cin, hora_event);

        eventos[nome_evento] = { descricao, quant_pess_perm, data_event, hora_event, {} };

        std::cout << "Evento " << nome_evento << " marcado com sucesso.\n";

        std::cout << "Deseja adicionar outro evento? (S/N): ";
        std::string adicionar_mais;
        std::getline(std::cin, adicionar_mais);
        if (adicionar_mais != "S" && adicionar_mais != "s") {
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}
void editar_evento() {
    if (eventos.empty()) {
        std::cout << "Nenhum evento disponível para edição.\n";
        return;
    }

    std::cout << "Digite o nome do evento que deseja editar: ";
    std::string nome_evento;
    std::cin.ignore();
    std::getline(std::cin, nome_evento);

    if (eventos.find(nome_evento) != eventos.end()) {
        Evento& evento = eventos[nome_evento];
        try {
            std::cout << "Editando evento " << nome_evento << "\n";
            std::cout << "Nova descrição do evento: ";
            std::getline(std::cin, evento.descricao);
            std::cout << "Nova quantidade de pessoas permitidas: ";
            std::cin >> evento.quant_pess_perm;
            std::cout << "Nova data do evento: ";
            std::cin.ignore();
            std::getline(std::cin, evento.data_event);
            std::cout << "Nova hora do evento: ";
            std::getline(std::cin, evento.hora_event);

            std::cout << "Evento " << nome_evento << " atualizado com sucesso.\n";
        }
        catch (...) {
            std::cout << "Entrada inválida. Por favor, insira valores corretos.\n";
        }
    }
    else {
        std::cout << "O evento " << nome_evento << " não existe.\n";
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void excluir_evento() {
    if (eventos.empty()) {
        std::cout << "Nenhum evento disponível para exclusão.\n";
        return;
    }

    visualizar_eventos();
    std::cout << "Digite o nome do evento que deseja excluir: ";
    std::string nome_evento;
    std::cin.ignore();
    std::getline(std::cin, nome_evento);

    if (eventos.find(nome_evento) != eventos.end()) {
        eventos.erase(nome_evento);
        std::cout << "Evento " << nome_evento << " excluído com sucesso.\n";
    }
    else {
        std::cout << "O evento " << nome_evento << " não existe.\n";
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
}
void visualizar_inscritos() {
    if (eventos.empty()) {
        std::cout << "Nenhum evento disponível.\n";
        return;
    }

    std::cout << "Eventos Disponíveis:\n";
    for (const auto& par : eventos) {
        std::cout << "- " << par.first << "\n";
    }
    std::cout << "\n";

    std::cout << "Digite o nome do evento para visualizar os inscritos: ";
    std::string nome_evento;
    std::cin.ignore();
    std::getline(std::cin, nome_evento);

    if (eventos.find(nome_evento) != eventos.end()) {
        const Evento& evento = eventos[nome_evento];
        if (evento.inscritos.empty()) {
            std::cout << "Ninguém está cadastrado no evento " << nome_evento << ".\n";
        }
        else {
            std::cout << "Inscritos no evento " << nome_evento << ":\n";
            for (const std::string& inscrito : evento.inscritos) {
                std::cout << inscrito << "\n";
            }
        }
    }
    else {
        std::cout << "O evento " << nome_evento << " não existe.\n";
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void inscrever_aluno() {
    if (eventos.empty()) {
        std::cout << "Nenhum evento disponível para inscrição.\n";
        return;
    }

    std::cout << "Eventos Disponíveis:\n";
    for (const auto& par : eventos) {
        const Evento& evento = par.second;
        std::string status_vagas = evento.inscritos.size() >= evento.quant_pess_perm ? "Completo, não tem vagas disponíveis" : "Vagas Disponíveis";
        std::cout << "Evento: " << par.first << ", Status: " << status_vagas << "\n";
    }
    std::cout << "\n";

    std::cout << "Digite o nome do evento que deseja se inscrever: ";
    std::string nome_evento;
    std::cin.ignore();
    std::getline(std::cin, nome_evento);

    if (eventos.find(nome_evento) != eventos.end()) {
        Evento& evento = eventos[nome_evento];
        while (evento.inscritos.size() < evento.quant_pess_perm) {
            std::cout << "Digite seu nome: ";
            std::string aluno_nome;
            std::getline(std::cin, aluno_nome);
            evento.inscritos.push_back(aluno_nome);
            std::cout << aluno_nome << " inscrito com sucesso no evento " << nome_evento << ".\n";

            if (evento.inscritos.size() >= evento.quant_pess_perm) {
                std::cout << "O evento " << nome_evento << " atingiu o número máximo de inscritos.\n";
                break;
            }

            std::cout << "Deseja adicionar outra pessoa a este evento? (S/N): ";
            std::string adicionar_mais;
            std::getline(std::cin, adicionar_mais);
            if (adicionar_mais != "S" && adicionar_mais != "s") {
                break;
            }
        }
    }
    else {
        std::cout << "O evento " << nome_evento << " não existe.\n";
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
}
void menu_cordenador() {
    while (true) {
        std::cout << "Escolha a opção: \n\n (1) Visualizar Eventos\n (2) Criar Eventos\n (3) Editar Eventos\n (4) Excluir Eventos\n (5) Visualizar Inscritos\n (6) Voltar ao menu principal\n";
        int opcao_coordenador;
        std::cin >> opcao_coordenador;
        if (opcao_coordenador == 1) {
            visualizar_eventos();
        }
        else if (opcao_coordenador == 2) {
            criar_evento();
        }
        else if (opcao_coordenador == 3) {
            visualizar_eventos();
            editar_evento();
        }
        else if (opcao_coordenador == 4) {
            excluir_evento();
        }
        else if (opcao_coordenador == 5) {
            visualizar_inscritos();
        }
        else if (opcao_coordenador == 6) {
            break;
        }
        else {
            std::cout << "Opção inválida. Tente novamente.\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void menu_principal() {
    while (true) {
        std::cout << "************** Controle de Eventos da UniFECAF **************\n";
        if (tipo_usuario == "coordenador") {
            std::cout << "Escolha a opcao:\n";
            std::cout << "(1) Area do Aluno (inscrever em eventos)\n";
            std::cout << "(2) Area da Coordenacao\n";
            std::cout << "(3) Visualizar Eventos\n";
            std::cout << "(4) Voltar ao Menu Inicial\n";
        }
        else {
            std::cout << "Escolha a opcao:\n";
            std::cout << "(1) Area do Aluno (inscrever em eventos)\n";
            std::cout << "(3) Visualizar Eventos\n";
            std::cout << "(4) Voltar ao Menu Inicial\n";
        }
        int escolha_usuario;
        std::cin >> escolha_usuario;
        if (escolha_usuario == 1) {
            inscrever_aluno();
        }
        else if (escolha_usuario == 2 && tipo_usuario == "coordenador") {
            menu_cordenador();
        }
        else if (escolha_usuario == 3) {
            visualizar_eventos();
        }
        else if (escolha_usuario == 4) {
            menu_inicial();
        }
        else {
            std::cout << "Opcao invalida. Tente novamente.\n";
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int main() {
    menu_inicial();
    menu_principal();
    return 0;
}


