//Atividade Semestral de Programação Orientada a Objetos
//MODULO RH//
//REVISÃO: 2
//DATA: 26/04/2026

#include <iostream>
#include <string>
#include <ctime>
#include <fstream>
#include <vector>
#include <cctype>
#include <algorithm>

using namespace std;

    class Cargo // para a segunda avaliacao, implementar a opcao de cadastrar mais cargos ou editar os existentes
    {
        private:

            int id_cargo;
            string nome;
            float salarioBase;

        public:
            
            Cargo() // metodo construtor sem parametros
            {
                this->id_cargo = 0;
                this->nome = "Nao preenchido";
                this->salarioBase = 0;
            }

            Cargo(int id_cargo_arq, string nome_arq, float salario_arq) // metodo construtor para o metodo extrairCargosPlanilha - informacoes extraidas de arquivo csv
            {
                this->id_cargo = id_cargo_arq;
                this->nome = nome_arq;
                this->salarioBase = salario_arq;
            }

            void extrairCargosPlanilha(vector <Cargo>& cargos)
            {
                ifstream arquivo("TabelaCargos.csv"); // ifstream le dados no arquivo
                if (arquivo.is_open()) // confere se o arquivo esta aberto
                {
                    string linha; // variavel auxiliar para salvar as linhas lidas do arquivo
                    getline (arquivo, linha); // copia a primeira linha de cabecalho (eliminar)

                    while (getline(arquivo, linha)) 
                    {
                        string dados_cargos[3]; // Vetor temporário para guardar os pedaços da linha
                        size_t pos = 0;

                        for (int i = 0; i < 3; i++) 
                        {
                            pos = linha.find(";");
                            dados_cargos[i] = linha.substr(0, pos); // cria uma substring ate o ; e copia para o vetor auxiliar
                            linha.erase(0, pos + 1); // apagar o que ja foi extraido
                        }
                    int id_cargo_aux = stoi(dados_cargos[0]); // converter o ID de string para int
                    float salario_aux = stof(dados_cargos[2]);// converter o salario de string para float
                    Cargo cargo_aux(id_cargo_aux, dados_cargos[1], salario_aux);
                    cargos.push_back(cargo_aux); 
                    }
                    arquivo.close();
                    cout << "Dados de cargos carregados com sucesso!\n";
                }
                else 
                {
                    cout << "Erro ao abrir o arquivo\n";
                }   
            }

            int getID_Cargo() const 
            { 
                return id_cargo; 
            }

            string getNome() const 
            { 
                return nome; 
            }

            float getSalario() const 
            { 
                return salarioBase; 
            }      
    };
  
    class Colaborador
    { 
        private:

            static int contador_ID;
            int id;
            string nome;
            Cargo objetoCargo;
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
                this->cpf = "00000000000";
                this->sexo = "Nao preenchido";
                struct tm data_admissao = {0};
                struct tm data_desligamento = {0}; // logica da data de desligamento deve entrar no metodo deleteColaborador
            }

            Colaborador(int id_arquivo, string nome_arq, string cargo_arq, string cpf_arq, string sexo_arq) // metodo contrutor para pegar dados de arquivo
            {
                this->id = id_arquivo;
                this->nome = nome_arq;
                //this->cargo = cargo_arq;
                this->cpf = cpf_arq;
                this->sexo = sexo_arq;

                if (id_arquivo > contador_ID) {
                contador_ID = id_arquivo;
                }
            }

            string getNomeCargo() const
            {
                return objetoCargo.getNome();
            }

            float getSalarioBase() const
            {
                return objetoCargo.getSalario();                
            }
            
            void addColaborador(vector <Cargo>& listaCargos)
            {
                string nome_Temp, cargo_Temp, sexo_Temp, cpf_Temp; // variaveis temporarias para guardar entradas do usuario
                int cargo_aux;

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

                cout << "Digite o CPF (apenas numeros): ";
                cin >> cpf_Temp;

                cout << "Digite o Sexo (M/F): ";
                cin >> sexo_Temp;
                while(sexo_Temp != "m" && sexo_Temp != "M" && sexo_Temp != "f" && sexo_Temp != "F")
                {
                    cout << "Informacao invalida! Digite M ou F novamente.\n";
                    cin >> sexo_Temp;
                }
                transform(sexo_Temp.begin(), sexo_Temp.end(), sexo_Temp.begin(), ::toupper); // deixando a letra maiuscula

                cout << "Digite o numero correspondente ao cargo: \n";
                for (int i = 0; i < listaCargos.size(); i++) 
                {
                    cout << listaCargos[i].getID_Cargo() << ". " << listaCargos[i].getNome() << endl;
                }
                cin >> cargo_aux;
                while(cargo_aux < 1 || cargo_aux > listaCargos.size()) 
                {
                    cout << "Cargo invalido! Escolha entre 1 e " << listaCargos.size() << ": ";
                    cin >> cargo_aux;
                }

                this->nome = nome_Temp;
                this->cpf = cpf_Temp;
                this->sexo = sexo_Temp;
                this->objetoCargo = listaCargos[cargo_aux - 1]; // - 1 pois o vetor de cargos comeca a contar em zero

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

            //string getCargo() const
            //{
            //    return cargo;
            //}

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

    //class ColaboradorMensalista :: public Colaborador
    //{
        //desenvolver - uso de heranca (requisito do projeto)
    //}

    //class ColaboradorHorista :: public Colaborador
    //{
        //desenvolver - uso de heranca (requisito do projeto)

    //}

    class FolhaPagamento
    {
           
        private:
          
            int salario;
            float impostos;
            float total_hh;
                   
        public:
            
           void enviaFinanceiro() // inicialmente vai apenas gerar um arquivo csv com os dados e na segunda etapa envia para o financeiro
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
                  
            float calculaLiquido(Colaborador& colaboradorA)
            {
                return 0;
            }
    };

    // classe para salvar/pegar dados de colaboradores em arquivo csv ou banco de dados (implementacao futura)
    class BancoDados_RH
    {
        public:

            // salva em arquivo csv
            void exportarPlanilha(const vector <Colaborador>& colaboradores) // acessa as informacoes de um vetor de objetos do tipo Colaborador
            {
                ofstream planilha("ColaboradoresRH.csv"); // ofstream escreve dados no arquivo
                if (planilha.is_open()) // confere se o arquivo esta aberto
                {
                    planilha << "ID;Nome;Cargo;CPF;Sexo" << endl; // cabecalho do arquivo

                    for (int i = 0; i < colaboradores.size(); i++) // loop roda o mesmo numero de vezes que o numero de colaboradores que podem ser cadastrados no vetor
                    {
                        planilha << colaboradores[i].getID() << ";";
                        planilha << colaboradores[i].getNome() << ";";
                        planilha << colaboradores[i].getNomeCargo() << ";";
                        planilha << colaboradores[i].getCPF() << ";";
                        planilha << colaboradores[i].getSexo() << endl;
                    }
                    planilha.close();    
                    cout << "Dados salvos com sucesso!\n";
                } 

                else // caso o arquivo nao esteja aberto
                {
                    cout << "Erro ao abrir o arquivo!\n";
                }
}

            void carregarPlanilha(vector <Colaborador>& colaboradores) // pega informacoes em arquivo csv 
            {
                ifstream arquivo("ColaboradoresRH.csv"); // ifstream le dados no arquivo
                if (arquivo.is_open()) // confere se o arquivo esta aberto
                {
                    string linha; // variavel auxiliar para salvar as linhas lidas do arquivo
                    getline (arquivo, linha); // copia a primeira linha de cabecalho (eliminar)

                    while (getline(arquivo, linha)) {
                        string dados_colab[5]; // Vetor temporário para guardar os pedaços da linha
                        size_t pos = 0;

                        for (int i = 0; i < 4; i++) { // Faz o corte para as 4 primeiras posicoes do vetor
                            pos = linha.find(";");
                            dados_colab[i] = linha.substr(0, pos); // cria uma substring ate o ; e copia para o vetor auxiliar
                            linha.erase(0, pos + 1); // apagar o que ja foi extraido
                        }
                    
                    dados_colab[4] = linha; // O que sobrou na linha é o último dado (Sexo)

                    int id_aux = stoi(dados_colab[0]); // converter o ID de string para int
                    Colaborador colab_aux(id_aux, dados_colab[1], dados_colab[2], dados_colab[3], dados_colab[4]);
                    colaboradores.push_back(colab_aux); // atribui os dados de colab_aux para o vetor colaboradores
                    }
                    arquivo.close();
                    cout << "Dados de colaboradores carregados com sucesso!\n";
                }
                else {
                    cout << "Erro ao abrir o arquivo\n";
                }
}

            void salvarBanco() // metodo a ser desenvolvido na segunda avaliacao
            {
                return;
            }

            void carregarBanco() // metodo a ser desenvolvido na segunda avaliacao
            {
                return;
            }
    };


int main() {
   
    int menu_aux = 0, addColaborador_aux = 0; 
    vector <FolhaPagamento> folhas_pagamento; // vetor de objetos do tipo FolhaPagamento
    vector <Colaborador> colaboradores; // vetor de objetos do tipo Colaborador
    vector <Cargo> listaCargos;
    Cargo cargos_aux; // vetor para armazenar cargos do arquivo csv
    BancoDados_RH arquivo;

    arquivo.carregarPlanilha(colaboradores); // puxa os dados de colaboradores cadastrados anteriormente no arquivo
    cargos_aux.extrairCargosPlanilha(listaCargos);
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
            // desenvolver
        break;    

        case 3:
            // desenvolver
        break;      
        
        case 4:

            cout << "\n";
            cout << "=====Colaboradores cadastrados=====\n";
            for(int j = 0; j < colaboradores.size(); j++)
            {
                cout << colaboradores[j].getID() << " || ";
                cout << colaboradores[j].getNome() << " || ";
                cout << colaboradores[j].getNomeCargo() << " || ";
                cout << colaboradores[j].getCPF() << " || ";
                cout << colaboradores[j].getSexo() << "\n";
            }
            if(colaboradores.empty())
            {
                cout << "Nenhum colaborador cadastrado!\n";
            }
            cout << "\n";

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