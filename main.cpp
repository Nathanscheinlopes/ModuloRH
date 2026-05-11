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
    string termoBusca;
    vector <Colaborador> colaboradores; // vetor de objetos do tipo Colaborador
    vector <Cargo> listaCargos; // vetor para armazenar cargos do arquivo csv
    Cargo cargos_aux; // objeto do tipo cargo para acessar os metodos desta classe
    BancoDados_RH arquivo; // objeto do tipo BancoDados_RH para acessar os metodos desta classe
    FolhaPagamento folha_pag; // objeto do tipo FolhaPagamento para acessar os metodos desta classe

    cargos_aux.extrairCargosPlanilha(listaCargos);
    arquivo.carregarPlanilha(colaboradores, listaCargos); // puxa os dados de colaboradores cadastrados anteriormente no arquivo
    // Menu de opcoes para o usuario
    do {
    
    cout << "\n";
    cout << "Bem-vindo ao sistema de Recursos Humanos!" << endl;
    cout << "Digite a operacao que deseja realizar:" << endl;
    cout << "1. Cadastrar colaborador" << endl << "2. Editar colaborador cadastrado" << endl << "3. Excluir colaborador" << endl << "4. Listar colaborador(es)" << endl;
    cout << "5. Buscar por colaborador(es)" << endl << "6. Listar horas trabalhadas" << endl << "7. Gerar Folha de Pagamento" << endl << "8. Sair" << endl;
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
            // desenvolver
        break;

        case 7:

            folha_pag.gerarFolhaPagamento(colaboradores);

        break;

        case 8:
            cout << "Encerrando..." << endl;
        break;

        default: // valor de entrada diferente das opcoes nos cases
            cout << "Opcao invalida! Tente novamente" << endl;
        break;
    }

    } while (menu_aux != 8); // loop do menu de opcoes funciona enquanto o usuario nao escolher a opcao de sair - 7

    return 0;
}