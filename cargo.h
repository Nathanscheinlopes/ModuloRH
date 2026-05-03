#ifndef CARGO_H
#define CARGO_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Cargo // para a segunda avaliacao, implementar a opcao de cadastrar mais cargos ou editar os existentes
{
    private:

        int id_cargo;
        string nome;
        float salarioBase;

    public:
        
        Cargo(); // metodo construtor sem parametros

        Cargo(int id_cargo_arq, string nome_arq, float salario_arq); // metodo construtor para o metodo extrairCargosPlanilha - informacoes extraidas de arquivo csv

        void extrairCargosPlanilha(vector <Cargo>& cargos);

        int getID_Cargo() const;

        string getNome() const;

        float getSalario() const;
};

#endif