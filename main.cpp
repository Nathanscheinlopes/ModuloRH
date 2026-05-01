//Atividade Semestral de Programação Orientada a Objetos
//MODULO RH//
//REVISÃO: 2
//DATA: 26/04/2026

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>

using namespace std;
  
    class Colaborador
    { 
        private:

            static int contador_ID;
            int id;
            string nome;
            string cargo;
            string cpf;
            //foto - definir como fazer;            
            string sexo;
            struct tm data_admissao; // struct padrao da biblioteca ctime
            struct tm data_desligamento; // struct padrao da biblioteca ctime     

        public:

            Colaborador() // metodo construtor - inicializa todos os membros da classe Colaborador
            {
                this->id = ++contador_ID; // atribui id e soma 1 ao contador (id sequencial do sistema)
                this->nome = "Nao preenchido";
                this->cargo = "Nao preenchido";
                this->cpf = "00000000000";
                this->sexo = "Nao preenchido";
                struct tm data_admissao = {0};
                struct tm data_desligamento = {0};
            }
            
            void addColaborador()
            {
                string nome_Temp, cargo_Temp, sexo_Temp, cpf_Temp; // variaveis temporarias para guardar entradas do usuario
               
                // Lógica para obter a data atual e salvar no membro data de admissao
                time_t tempoBruto = time(0); // Pega o tempo agora
                struct tm* dataAtual = localtime(&tempoBruto); // Converte para struct tm
                this->data_admissao = *dataAtual; // atribui ao membro da classe
                char data_admissao_aux[100]; // variavel auxiliar para salvar a data atual
                strftime(data_admissao_aux, 100, "%d/%m/%Y", &this->data_admissao); // converter os elementos da struct tm na data formatada
                
                // dados de entrada do usuario salvos em variaveis temporarias
                cout << "=====Cadastro de novo colaborador=====" << endl;
                cout << "Digite o Nome: ";
                getline(cin >> ws, nome_Temp); // 'ws' limpa o buffer para aceitar espaços
                cout << "Digite o CPF: ";
                cin >> cpf_Temp;
                cout << "Digite o Sexo: ";
                cin >> sexo_Temp;
                cout << "Digite o Cargo: ";
                getline(cin >> ws, cargo_Temp); // 'ws' limpa o buffer para aceitar espaços
              
                this->nome = nome_Temp;
                this->cpf = cpf_Temp;
                this->sexo = sexo_Temp;
                this->cargo = cargo_Temp;

                cout << "Colaborador " << this->nome << " com ID " << this->id << " cadastrado com sucesso. Admissao em: " << data_admissao_aux << endl;
            }
             
            void editColaborador()
            {
                return;
            }          
             
            void deleteColaborador()
            {
                return;
            }
            
            int getID() const // const no final garante que o ID nao sera alterado por outras classes
            {
                return id;
            }

            string getNome() const
            {
                return nome;
            }

            string getCargo() const
            {
                return cargo;
            }

            string getCPF() const
            {
                return cpf;
            }

            string getSexo() const
            {
                return sexo;
            }
    };

    int Colaborador::contador_ID = 0; //inicializa o contador de IDs

    class FolhaPagamento
    {
           
        private:
          
            int salario;
            float impostos;
            float total_hh;
                   
        public:
            
           void enviaFinanceiro()
            {
                return;
            }
             
            void recebeFinanceiro()
            {
                return;
            }
                       
            float calculaBruto(Colaborador& colaboradorA) //Acesso indireto via método público
            {
                return 0;
            }
                  
            float calculaLiquido()
            {
                return 0;
            }
    };

    // classe para salvar/pegar dados de colaboradores em arquivo txt / csv ou banco de dados (implementacao futura)
    class BancoDados_RH
    {
        public:

            // salva em arquivo txt/csv
            void salvarArquivo(const vector <Colaborador>& colaboradores) // acessa as informacoes de um vetor de objetos do tipo Colaborador
            {
                ofstream arquivo; // cria um objeto ofstream
                arquivo.open("ColaboradoresRH.csv"); // abre um arquivo e cria ele caso nao exista

                if (arquivo.is_open()) // confere se o arquivo esta aberto
                {
                    arquivo << "ID;Nome;Cargo;CPF;Sexo" << endl; // cabecalho do arquivo

                    for (int i = 0; i < colaboradores.size(); i++) // loop roda o mesmo numero de vezes que o numero de colaboradores que podem ser cadastrados no vetor
                    {
                        arquivo << colaboradores[i].getID() << ";";
                        arquivo << colaboradores[i].getNome() << ";";
                        arquivo << colaboradores[i].getCargo() << ";";
                        arquivo << colaboradores[i].getCPF() << ";";
                        arquivo << colaboradores[i].getSexo() << endl;

                        }
                    arquivo.close();    
                    cout << "Dados salvos com sucesso!\n";
                } 

                else // caso o arquivo nao esteja aberto
                {
                    cout << "Erro ao abrir o arquivo!\n";
                }
}

            void carregarArquivo(vector <Colaborador>& colaboradores) // pega informacoes em arquivo txt/csv TERMINAR DE DESENVOLVER
            {
                ifstream arquivo("ColaboradoresRH.csv"); // ifstream le dados no arquivo
                arquivo.open("ColaboradoresRH.csv"); // abre um arquivo e cria ele caso nao exista

                if (arquivo.is_open()) // confere se o arquivo esta aberto
                {
                    string linha; // variavel auxiliar para salvar as linhas lidas do arquivo
                    getline(arquivo, linha, ';'); // le a linha ate encontrar ; e salva na variavel auxiliar
                    cout << linha;                          
                }
            }

            void salvarBanco() // segunda avaliacao
            {
                return;
            }

            void carregarBanco() // segunda avaliacao
            {
                return;
            }
    };


int main() {
   
    int menu_aux = 0, addColaborador_aux = 0; 
    vector <FolhaPagamento> folhas_pagamento; // vetor de objetos do tipo FolhaPagamento
    vector <Colaborador> colaboradores; // vetor de objetos do tipo Colaborador
    BancoDados_RH arquivo;

    // Menu de opcoes para o usuario
    do {
    cout << "Bem-vindo ao sistema de Recursos Humanos!" << endl;
    cout << "Digite a operacao que deseja realizar:" << endl;
    cout << "1. Cadastrar colaborador" << endl << "2. Editar colaborador cadastrado" << endl << "3. Excluir colaborador" << endl << "4. Listar colaborador(es)" << endl;
    cout << "5. Buscar por colaborador(es)" << endl << "6. Listar horas trabalhadas" << endl << "7. Sair" << endl;
    cin >> menu_aux;

    switch (menu_aux)
    {
        case 1:
            //arquivo.carregarArquivo(colaboradores);
            cout << "Digite o numero de colaboradores que voce quer cadastrar: " << endl;
            cin >> addColaborador_aux;
            for(int i = 0; i < addColaborador_aux; i++)
            {
            Colaborador novo; // Cria um novo objeto na memória
            novo.addColaborador(); // Chama o método para preencher os dados
            colaboradores.push_back(novo); // Adiciona o objeto preenchido ao vetor
            }
        
        arquivo.salvarArquivo(colaboradores);
        break;

        case 2:
            // desenvolver
        break;    

        case 3:
            // desenvolver
        break;      
        
        case 4:
            // desenvolver
        break;

        case 5:
            // desenvolver
        break;

        case 6:
            // desenvolver
        break;

        case 7:
            cout << "Encerrando..." << endl;
        break;

        default: // valor de entrada diferente das opcoes nos cases
            cout << "Opcao invalida! Tente novamente" << endl;
        break;
    }

    } while (menu_aux != 7); // loop do menu de opcoes funciona enquanto o usuario nao escolher a opcao de sair - 7

    return 0;
}