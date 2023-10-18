#include <iostream>
#include <cstdio> // Mesma coisa que stdio.h
#include <ctime>  // Mesma coisa que time.h
#include <cstdlib> // Mesma coisa que stdlib.h
#include <windows.h>
#include "DataArray.h"

#define LIMITE_INSERTION 20 // Define a partir de quantos termos em casa sub-array o Insertion vai agir

using std::cout; // Não utilizei o using namespace std pois swap e partition fazem parte da biblioteca std, o que ia atrapalhar o funcionamento das minhas versões a função
using std::cin;

void swap(Cliente vet[], const int i, const int j) // Faz a troca de valores
{
    Cliente aux = vet[i];
    vet[i] = vet[j];
    vet[j] = aux;
}

void ler(const Cliente vet[], const int tam) // Lê o vetor CUIDADO!!!! Essa função não funciona com valores muito grandes, usá-la desta maneira irá fechar o programa
{
    system("cls");
    cout << "==============================================================================" << endl;
    for (int i = 0; i < tam; i++) {
        cout << "   Nome: " << vet[i].name << endl;
        cout << "   Produtos Comprados: " << vet[i].qntDeItensComprados << endl;
        cout << "==============================================================================" << endl;
    }
}

Cliente escolhePivo(Cliente vet[], const int ini, const int fim)
{
    // Escolhe o pivô como o elemento do meio da partição
    int meio = vet[fim].qntDeItensComprados;

    // Ordena ini, meio e fim
    if (vet[ini].qntDeItensComprados > vet[meio].qntDeItensComprados) {
        swap(vet, ini, meio);
    }
    if (vet[ini].qntDeItensComprados > vet[fim].qntDeItensComprados) {
        swap(vet, ini, fim);
    }
    if (vet[meio].qntDeItensComprados > vet[fim].qntDeItensComprados) {
        swap(vet, meio, fim);
    }

    // Coloca o pivô na penúltima posição
    swap(vet, meio, fim - 1);

    return vet[fim - 1];
}

int partition(Cliente vet[], const int ini, const int fim)
{
    Cliente pivo = escolhePivo(vet, ini, fim);
    int i = ini;

    // Percorre o vetor procurando por termos que estão desordenados em relação ao pivô
    for (int j = ini; j < fim; j++) {
        if (vet[j].qntDeItensComprados <= pivo.qntDeItensComprados) {
            swap(vet, i, j);
            i++;
        }
    }
    // Coloca o pivô em seu local ideal
    swap(vet, i, fim - 1);

    return i;
}


void insertionSort(Cliente vet[], const int ini, const int fim) // Fará a ordenação quando o sub-array for menor que 20 elementos
{
    for (int i = ini + 1; i <= fim; i++)
    {
        Cliente chave = vet[i];
        int j = i - 1;
        while (j >= ini && vet[j].qntDeItensComprados > chave.qntDeItensComprados)
        {
            vet[j + 1] = vet[j];
            j--;
        }
        vet[j + 1] = chave;
    }
}

void quicksort(Cliente vet[],int ini,int fim, int &contador, clock_t &tempoInicio)
{
    while(ini<fim){
        if (ini >= fim) // Verifica se o vetor existe
            return;

        // Usa o Insertion Sort se o tamanho do subconjunto for menor que 20
        if (fim - ini + 1 <= LIMITE_INSERTION)
        {
            insertionSort(vet, ini, fim);
            break;
        }
        else
        {
            int pivo = partition(vet, ini, fim);

            if(pivo - ini < fim - pivo){
                quicksort(vet, ini, pivo - 1, contador, tempoInicio);
                ini = pivo + 1;
            }else{
                quicksort(vet, pivo + 1, fim, contador, tempoInicio);
                fim = pivo - 1;
            }
            // Recursôes no "final" da função, tudo abaixo das duas recursôes não afetam mais o sort, apenas atualiza o contador



            // Incrementa o contador de chamadas
            contador++;

            // Mostra o tempo decorrido a cada 10.000 chamadas
            if (contador % 10000 == 0)
            {
                // As funções clock_t, clock(), CLOCKS_PER_SEC estão inclusas na biblioteca ctime do C++
                // As funções usadas a seguir medem o tempo usando como unidade de medida os clocks do processador
                clock_t tempoDecorrido = clock() - tempoInicio;
                cout << "Processo: " << contador << " Tempo (s): " << double(tempoDecorrido) / CLOCKS_PER_SEC << "\n";

                // Também salva no arquivo CSV
                FILE *file = fopen("teste1.csv", "a");
                if (file)
                {
                    // Utilizei double para uma medida mais precisa
                    fprintf(file, "Processo: %d, Tempo (s): %f\n", contador, double(tempoDecorrido) / CLOCKS_PER_SEC);
                    fclose(file);
                }
            }
        }
    }
}

void startQuick(int tam)
{
    bool tmp = true;
    int aux;
    char sn;

    Cliente* vet = clients;

    int contador = 0;
    clock_t tempoInicio = 0;

    // Novamente, não utilize isso quando o tamanho do vetor for muito grande
    cout << "==============================================================================" << endl;
    cout << "--> Ler?" << endl;
    cout << "==============================================================================" << endl;
    cout << "Digite s ou n: ";
    cin >> sn;

    if(sn == 's')
    {
        ler(vet, tam);
    }

    // Inicializa o contador para feedback do processo
    tempoInicio = clock();
    quicksort(vet, 0, tam - 1, contador, tempoInicio);
    ler(vet, tam);
    // Termina de contar
    clock_t fim = clock();
    double tempo_corrido = double(fim - tempoInicio) / CLOCKS_PER_SEC;
    delete[] vet;
}
