#ifndef COLABORADOR_H  // Se o símbolo COLABORADOR_H não estiver definido...
#define COLABORADOR_H  // Define ele agora.

#include <string>
#include <vector>
#include <iostream> // Para usar cout/cin
#include <ctime>    // Para usar struct tm e time_t

#include "cargo.h"

class Colaborador { 
    private:
        static int contador_ID;
        int id;
        string nome;
        Cargo objetoCargo;
        string cpf;
        string sexo;
        struct tm data_admissao;
        struct tm data_desligamento;
        bool ativo;
        float horasTrabalhadas;

    public:
        Colaborador(); 
        
        // CORREÇÃO 3: Adicione "bool ativo_arq" ao final desta declaração
        Colaborador(int id_arquivo, string nome_arq, Cargo cargo_obj, string cpf_arq, string sexo_arq, bool ativo_arq); 

        string getNomeCargo() const;
        float getSalarioBase() const;
        void addColaborador(const vector <Cargo>& listaCargos);
        void editColaborador();

        void setHoras(float h){ this->horasTrabalhadas = h; }
        float getHoras() const {return horasTrabalhadas; }
        
        // CORREÇÃO 1: Garanta que esta linha apareça APENAS UMA VEZ
        static void deleteColaborador(std::vector<Colaborador>& lista, int idParaExcluir);
        static void buscarColaborador(const vector<Colaborador>& lista, string termoBusca);
        static void atualizarContador(const vector<Colaborador>& lista);  
        void editColaborador(std::vector<Colaborador>& lista, const std::vector<Cargo>& listaCargos);


        void setAtivo(bool estado) { ativo = estado; }
        bool isAtivo() const { return ativo; }

        int getID() const; 
        string getNome() const;
        string getCPF() const;
        string getSexo() const;
};

#endif // Fim do bloco de inclusão para COLABORADOR_H