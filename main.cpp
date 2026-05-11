//Atividade Semestral de Programação Orientada a Objetos
//MODULO RH//

#include <iostream>
#include <vector>
#include "cargo.h"
#include "colaborador.h"
#include "folhaPagamento.h"
#include "bancoDados_RH.h"

using namespace std;

int main() {
   
    int menu_aux = 0, addColaborador_aux = 0, editColaborador_aux = 0, deleteColaborador_aux = 0; // variaveis auxiliares para o menu de opcoes
    int idAux = 0; // variavel auxiliar para receber o ID do colaborador a ser excluido  
    bool existemAtivos = false; // Auxiliar para a mensagem de lista vazia
    int opCargo = 0;
    string termoBusca;
    vector <Colaborador> colaboradores; // vetor de objetos do tipo Colaborador
    vector <Cargo> listaCargos; // vetor para armazenar cargos do arquivo csv
    Cargo cargos_aux; // objeto do tipo cargo para acessar os metodos desta classe
    BancoDados_RH arquivo; // objeto do tipo BancoDados_RH para acessar os metodos desta classe
    FolhaPagamento folha_pag; // objeto do tipo FolhaPagamento para acessar os metodos desta classe
    Colaborador objAux;
    Cargo objCargoAux; // Objeto para chamar métodos não-estáticos
    cargos_aux.extrairCargosPlanilha(listaCargos);
    arquivo.carregarPlanilha(colaboradores, listaCargos); // puxa os dados de colaboradores cadastrados anteriormente no arquivo
    // Menu de opcoes para o usuario
    do {
    
    cout << "\n";
    cout << "Bem-vindo ao sistema de Recursos Humanos!" << endl;
    cout << "Digite a operacao que deseja realizar:" << endl;
    cout << "1. Cadastrar colaborador" << endl << "2. Editar colaborador cadastrado" << endl << "3. Excluir colaborador" << endl << "4. Listar colaborador(es)" << endl;
    cout << "5. Buscar por colaborador(es)" << endl << "6. Gerar Folha de Pagamento" << endl << "7. Gerenciar Cargos" << endl << "8. Sair" << endl;
    cin >> menu_aux;
    //arquivo.carregarPlanilha(colaboradores, listaCargos);
    Colaborador::atualizarContador(colaboradores); // Ajusta o ID para não repetir

    switch (menu_aux)
    {
        case 1:

            cout << "\n";
            cout << "Digite o numero de colaboradores que voce quer cadastrar: " << endl;
            cin >> addColaborador_aux;
            
            for(int i = 0; i < addColaborador_aux; i++)
            {
                Colaborador novo; // Cria um novo objeto na memória
                novo.addColaborador(listaCargos); // Chama o método para preencher os dados
                colaboradores.push_back(novo); // Adiciona o objeto preenchido ao vetor
            }
        
            arquivo.exportarPlanilha(colaboradores);
            cout << "\n";

        break;

        case 2:
            objAux.editColaborador(colaboradores, listaCargos); // Chama o método de edição
            arquivo.exportarPlanilha(colaboradores);
            break;
            break;
        
        case 3:
            
            cout << "\n=====Excluir colaborador=====\n";
            cout << "Digite o ID: ";
            cin >> idAux;

            // Chamada do método estático da classe
            Colaborador::deleteColaborador(colaboradores, idAux);

            // Atualiza o arquivo após a remoção
            arquivo.exportarPlanilha(colaboradores);
    

        break;      
        
        case 4:
            cout << "\n";
            cout << "=====Colaboradores cadastrados=====\n";

            existemAtivos = false;

            for(int j = 0; j < colaboradores.size(); j++)
            {
                // A mágica acontece aqui: só imprime se estiver ativo
                if(colaboradores[j].isAtivo()) 
                {
                    cout << colaboradores[j].getID() << " || ";
                    cout << colaboradores[j].getNome() << " || ";
                    cout << colaboradores[j].getNomeCargo() << " || ";
                    cout << colaboradores[j].getCPF() << " || ";
                    cout << colaboradores[j].getSexo() << "\n";
                    existemAtivos = true;
                }
            }

            // Se o vetor estiver fisicamente vazio OU se todos os itens estiverem inativos
            if(!existemAtivos)
            {
                cout << "Nenhum colaborador ativo encontrado!\n";
            }
            cout << "\n";
        break;

        case 5:
            cout << "\n=====Buscar colaborador=====\n";
            cout << "Digite o nome, ID ou CPF do colaborador que deseja buscar: ";
            cin >> ws; // limpa buffer
            getline(cin, termoBusca);

            Colaborador::buscarColaborador(colaboradores, termoBusca);       
                
        break;

        case 6:
           cout << "\n--- GERAÇÃO DE FOLHA COM HORAS TRABALHADAS ---\n";
            
            folha_pag.gerarFolhaPagamento(colaboradores); 
            // A função gerarFolhaPagamento agora pedirá as horas internamente
        break;

        case 7:  // Menu de Gestão de Cargos
                        
            do {
                cout << "\n========== GESTAO DE CARGOS ==========" << endl;
                cout << "1. Listar Cargos" << endl;
                cout << "2. Adicionar Novo Cargo" << endl;
                cout << "3. Editar Cargo" << endl;
                cout << "4. Desativar Cargo" << endl;
                cout << "0. Voltar" << endl;
                cout << "Escolha: ";
                cin >> opCargo;

                if (opCargo == 1) {
                    cout << "\nID | STATUS | NOME | SALARIO" << endl;
                    for(const auto& c : listaCargos) {
                        printf("%-2d | %-8s | %-15s | R$ %.2f\n", 
                            c.getID_Cargo(), (c.isAtivo() ? "ATIVO" : "INATIVO"), 
                            c.getNome().c_str(), c.getSalario());
                    }
                } else if (opCargo == 2) {
                    Cargo::adicionarCargo(listaCargos);
                    objCargoAux.salvarCargosPlanilha(listaCargos);
                } else if (opCargo == 3) {
                    Cargo::editarCargo(listaCargos);
                    objCargoAux.salvarCargosPlanilha(listaCargos);
                } else if (opCargo == 4) {
                    Cargo::deletarCargo(listaCargos, colaboradores);
                    objCargoAux.salvarCargosPlanilha(listaCargos);
                }
            } while (opCargo != 0);
        break;
    
        case 8:
            cout << "Encerrando..." << endl;
        break;

        default: // valor de entrada diferente das opcoes nos cases
            cout << "Opcao invalida! Tente novamente" << endl;
        break;
    }

    } while (menu_aux != 8); // loop do menu de opcoes funciona enquanto o usuario nao escolher a opcao de sair - 8

    return 0;
}