#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#define tam 100
using namespace std;

int busca_binaria(vector<unsigned int> vetor, unsigned int num, int in, int fim, int *cont);

int main()
{
    // preenchendo o vetor com numeros aleatorios
    mt19937 mt(static_cast<unsigned int>(time(0)));
    uniform_int_distribution<int> dist(1, 100);

    vector<unsigned int> vetor;
    for (int i = 0; i < tam; i++)
    {
        vetor.push_back(dist(mt));
    }
    sort(vetor.begin(), vetor.end());
    for (int i = 0; i < tam; i++)
    {
        cout << vetor[i] << " ";
    }
    // Coletando valor para ser buscado
    unsigned int num;
    cout << "Digite o numero que deseja buscar: ";
    cin >> num;

    int in = 0, fim = vetor.size() - 1;
    int cont = 0;
    int resultado = busca_binaria(vetor, num, in, fim, &cont);
    if(resultado == -1 ){
        cout << "Valor nao encontrado";
    }else{
        cout<< "Valor encontrado na posicao "<< resultado << "\nForam feitas " << cont << " comparacoes!";
    }
    return 0;
}

int busca_binaria(vector<unsigned int> vetor, unsigned int num, int in, int fim, int *cont)
{
    if (in <= fim)
    {
        int meio = static_cast<int> ((in + fim)/2);
        if (vetor[meio] == num)
        {
            return meio;
        }
        else if (vetor[meio] > num)
        {
            return busca_binaria(vetor, num, in, meio - 1, cont), (*cont)++;
        }
        else
        {
            return busca_binaria(vetor, num, meio + 1, fim, cont), (*cont)++;
        }
    }
    return -1;
}