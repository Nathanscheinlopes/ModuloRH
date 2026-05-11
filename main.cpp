#include <iostream>
#include <vector>
#include <iomanip>
#include "cargo.h"
#include "colaborador.h"
#include "folhaPagamento.h"
#include "bancoDados_RH.h"

using namespace std;

int main() {
    // --- Variáveis de Controle ---
    int menu_aux = 0, opCargo = 0;
    string termoBusca;
    bool existemAtivos = false;

    // --- Instanciação de Objetos e Vetores ---
    vector<Colaborador> colaboradores;
    vector<Cargo> listaCargos;
    
    Cargo objCargoAux; 
    Colaborador objColabAux;
    BancoDados_RH banco; 
    FolhaPagamento folha_pag;

    // --- Inicialização do Sistema ---
    // 1. Carrega dados dos arquivos para a memória
    objCargoAux.extrairCargosPlanilha(listaCargos);
    banco.carregarPlanilha(colaboradores, listaCargos);

    // 2. Sincroniza os contadores de ID para evitar duplicidade
    Cargo::atualizarContador(listaCargos);
    Colaborador::atualizarContador(colaboradores);

    // --- Menu Principal ---
    do {
        cout << "\n========================================" << endl;
        cout << "      SISTEMA DE RECURSOS HUMANOS       " << endl;
        cout << "========================================" << endl;
        cout << "1. Cadastrar Colaborador" << endl;
        cout << "2. Editar Colaborador" << endl;
        cout << "3. Excluir Colaborador (Soft Delete)" << endl;
        cout << "4. Listar Colaboradores Ativos" << endl;
        cout << "5. Buscar Colaborador (Filtro)" << endl;
        cout << "6. Gerar Folha de Pagamento" << endl;
        cout << "7. Gerenciar Cargos" << endl;
        cout << "8. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> menu_aux;

        switch (menu_aux) {
            case 1: { // Cadastrar
                int qtd;
                cout << "\nQuantos colaboradores deseja cadastrar? ";
                cin >> qtd;
                
                for(int i = 0; i < qtd; i++) {
                    Colaborador novo;
                    novo.addColaborador(listaCargos);
                    colaboradores.push_back(novo);
                }
                banco.exportarPlanilha(colaboradores);
                break;
            }

            case 2: // Editar
                objColabAux.editColaborador(colaboradores, listaCargos);
                banco.exportarPlanilha(colaboradores);
                break;
            
            case 3: { // Excluir
                int idDel;
                cout << "\n===== EXCLUIR COLABORADOR =====" << endl;
                cout << "Digite o ID para desativar: ";
                cin >> idDel;
                Colaborador::deleteColaborador(colaboradores, idDel);
                banco.exportarPlanilha(colaboradores);
                break;
            }

            case 4: // Listar
                cout << "\n" << string(80, '=') << endl;
                cout << "         LISTA DE COLABORADORES ATIVOS         " << endl;
                cout << string(80, '-') << endl;
                printf("%-4s | %-20s | %-15s | %-12s\n", "ID", "NOME", "CARGO", "CPF");
                cout << string(80, '-') << endl;

                existemAtivos = false;
                for(const auto& colab : colaboradores) {
                    if(colab.isAtivo()) {
                        printf("%-4d | %-20s | %-15s | %-12s\n", 
                               colab.getID(), colab.getNome().c_str(), 
                               colab.getNomeCargo().c_str(), colab.getCPF().c_str());
                        existemAtivos = true;
                    }
                }

                if(!existemAtivos) cout << "Nenhum colaborador ativo encontrado no sistema." << endl;
                cout << string(80, '=') << endl;
                break;

            case 5: // Buscar - Nome, ID ou CPF
                cout << "\nDigite o Nome, ID ou CPF para busca: ";
                cin >> ws;
                getline(cin, termoBusca);
                Colaborador::buscarColaborador(colaboradores, termoBusca);
                break;

            case 6: // Folha de Pagamento
                folha_pag.gerarFolhaPagamento(colaboradores);
                break;

            case 7: // Submenu Cargos
                do {
                    cout << "\n---------- GESTAO DE CARGOS ----------" << endl;
                    cout << "1. Listar Cargos\n2. Adicionar Cargo\n3. Editar Cargo\n4. Ativar/Desativar\n0. Voltar\nEscolha: ";
                    cin >> opCargo;

                    if (opCargo == 1) { // Listar Cargos
                        cout << "\nID | STATUS   | NOME            | SALARIO" << endl;
                        for(const auto& c : listaCargos) {
                            printf("%-2d | %-8s | %-15s | R$ %.2f\n", 
                                c.getID_Cargo(), (c.isAtivo() ? "ATIVO" : "INATIVO"), 
                                c.getNome().c_str(), c.getSalario());
                        }
                    } else if (opCargo == 2) { // Adicionar Cargo
                        Cargo::adicionarCargo(listaCargos);
                        objCargoAux.salvarCargosPlanilha(listaCargos);
                    } else if (opCargo == 3) { // Editar Cargo
                        Cargo::editarCargo(listaCargos);
                        objCargoAux.salvarCargosPlanilha(listaCargos);
                    } else if (opCargo == 4) { // Ativar/Desativar Cargo
                        Cargo::deletarCargo(listaCargos, colaboradores);
                        objCargoAux.salvarCargosPlanilha(listaCargos);
                    }
                } while (opCargo != 0);
                break;
        
            case 8:
                cout << "\n[SISTEMA] Salvando dados e encerrando..." << endl;
                break;

            default:
                cout << "[!] Opcao invalida. Tente novamente." << endl;
                break;
        }

    } while (menu_aux != 8);

    return 0;
}