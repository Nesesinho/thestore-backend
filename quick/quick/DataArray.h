#ifndef DATAARRAY_H_INCLUDED
#define DATAARRAY_H_INCLUDED

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>

using namespace std;

class Produto {
public:
    string name;
    int preco;
    int quantidade;
};

class Cliente {
public:
    string name;
    int idade;
    int qntDeItensComprados;
    Produto *itensComprados = new Produto[1000];
    int valorTotal;
};

Cliente *clients = new Cliente[1000];
int clientsTamanho = 0;

int montarArray(Cliente* ClientsArray, int* tamVar) {
    ifstream arquivo("dados.txt");

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo." << endl;
        return 1;
    }

    string linha;

    while (getline(arquivo, linha)) {
        if (linha == "--end") {
            // Se encontrou a tag "--end", terminar o processamento
            break;
        }

        istringstream stream(linha); // Criar um novo istringstream com a linha atual

        Cliente temp;
        int quantidadeDeProdutos;
        string fim;

        getline(stream, temp.name, '|');
        stream >> temp.idade;
        stream.ignore(1);
        stream >> quantidadeDeProdutos;
        stream.ignore(1);
        stream >> temp.qntDeItensComprados;
        stream.ignore(1);
        stream >> temp.valorTotal;
        stream.ignore(1);

        for (int i = 0; i < quantidadeDeProdutos; i++) {
            getline(stream, temp.itensComprados[i].name, '-');
            stream >> temp.itensComprados[i].quantidade;
            stream.ignore(1);
            stream >> temp.itensComprados[i].preco;

            if (i < quantidadeDeProdutos) {
                stream.ignore(1);
            }
        }

        getline(stream, fim, '\\');

//        cout << "Nome: " << temp.name << endl;
//        cout << "Idade: " << temp.idade << endl;
//        for (int i = 0; i < quantidadeDeProdutos; i++) {
//            cout << "Produto " << i + 1 << " - Nome: " << temp.itensComprados[i].name << ", Quantidade: " << temp.itensComprados[i].quantidade << ", Preço: " << temp.itensComprados[i].preco << endl;
//        }
//        cout << "Fim: " << fim << endl;

        ClientsArray[*tamVar] = temp;
        (*tamVar)++;
    }

    arquivo.close();
    return 0;
}

void mostrarClients() {
    montarArray(clients, &clientsTamanho);
    system("cls");
    cout << "==============================================================================" << endl;
    for (int i = 0; i < clientsTamanho; i++) {
        cout << "   Nome: " << clients[i].name << endl;
        cout << "   Idade: " << clients[i].idade << endl;
        cout << "   Produtos Comprados: " << clients[i].qntDeItensComprados << endl;
        cout << "   Valor da Compra: " << clients[i].valorTotal << endl;
        cout << "==============================================================================" << endl;
    }
}

#endif
