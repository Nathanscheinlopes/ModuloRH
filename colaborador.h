#ifndef COLABORADOR_H
#define COLABORADOR_H

#include "cargo.h"
#include <ctime>
#include <algorithm>

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

        Colaborador(); // metodo construtor - inicializa todos os membros da classe Colaborador

        Colaborador(int id_arquivo, string nome_arq, Cargo cargo_obj, string cpf_arq, string sexo_arq); // metodo contrutor para pegar dados de arquivo

        string getNomeCargo() const;

        float getSalarioBase() const;
        
        void addColaborador(vector <Cargo>& listaCargos);
            
        void editColaborador();
            
        void deleteColaborador();
        
        int getID() const; // const no final garante que o ID nao sera alterado por outras classes

        string getNome() const;

        string getCPF() const;

        string getSexo() const;
};

#endif