//Atividade Semestral de Programação Orientada a Objetos
//MODULO RH//
//REVISÃO: 0
//DATA: 17/06/2024

#include <iostream>
#include <string>
#include <time.h>

using namespace std;
  
    class Colaborador
    { 
        private:

            static int contador_ID;
            int id;
            string nome;
            string cargo;
            double cpf;
            //foto - definir como fazer;            
            string sexo;
            struct tm;
                    
        public:
            
            void addColaborador()
            {
                string nome_Temp, cargo_Temp, sexo_Temp; // variaveis temporarias para guardar entradas do usuario
                double cpf_Temp; // variavel temporaria para guardar entradas do usuario

                
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

                // atribuindo os valores aos membros da classe
                
                this->nome = nome_Temp;
                this->cpf = cpf_Temp;
                this->sexo = sexo_Temp;
                this->cargo = cargo_Temp;

                // gerando ID - sequencial do sistema

                this->id = ++contador_ID; // atribui id e soma 1 ao contador

                cout << "Colaborador " << this->nome << " com ID " << this->id << " cadastrado com sucesso";

            }
             
            void editColaborador()
            {
                //desenvolver
            }          
             
            void deleteColaborador()
            {
                //desenvolver
            }
            
            int getID() const
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

            double getCPF() const
            {
                return cpf;
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
                //desenvolver
            }
             
            void recebeFinanceiro()
            {
                //desenvolver
            }
                       
            float calculaBruto(Colaborador& colaboradorA) //Acesso indireto via método público
            {
                //desenvolver
            }
                  
            float calculaLiquido()
            {
                //desenvolver
            }
    };


int main() {
    cout << "Bem-vindo ao sistema de Recursos Humanos!" << endl;
    // Aqui você pode adicionar a lógica para gerenciar funcionários, departamentos, etc.

    FolhaPagamento folhas_pagamento[10]; // vetor de objetos do tipo FolhaPagamento
    Colaborador colaboradores[10]; // vetor de objetos do tipo Colaborador

    colaboradores[0].addColaborador();
    colaboradores[1].addColaborador();


    return 0;
}