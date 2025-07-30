#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <fstream>

#define TAM 256

using namespace std;

typedef struct huffman
{
    char caractere;
    int frequencia;
    huffman *esq, *dir;

    // metodo contrutor
    huffman(char c, int f): caractere(c), frequencia(f), esq(nullptr), dir(nullptr){}
}Huffman;

struct comparador_personalizado
{//manter a ordem da fila crescente usa esse trem (supostamente)
    bool operator()(const Huffman* a, const Huffman *b){
        return a->frequencia > b->frequencia;
    }
};
priority_queue<Huffman*, vector<Huffman*>, comparador_personalizado> cria_fila(vector<int>& tabela);
Huffman  *montar_arvore(priority_queue<Huffman*, vector<Huffman*>, comparador_personalizado> fila);
void gerar_dicionario(Huffman *raiz, string caminho, unordered_map<char, string> &dicionario);
string codificar(string txt, unordered_map<char, string> &dicionario);
string decodificar(string codigo, Huffman *raiz);

int main(){
    string txt = "Fazendo melhor em c plus plus, vlw chat gpt";

    vector<int> tabela(TAM, 0);
    preencher_tabela(txt, tabela);
    priority_queue<Huffman*, vector<Huffman*>, comparador_personalizado> fila = cria_fila(tabela);

    Huffman *arvore;
    arvore = montar_arvore(fila);

    vector<string> caractere;

    unordered_map<char, string> dicionario;
    gerar_dicionario(arvore, "", dicionario);

    string codigo = codificar(txt, dicionario);
    cout<< "Codificado = " << codigo;  

    string texto = decodificar(codigo, arvore);
    cout << "\nDocodificado =  " << texto;
    return 0;

}
void preencher_tabela(string txt, vector<int> &tabela){
    // Preenche a frequencia dos caracteres no vetor
    int i = 0;
    while(txt[i] != '\0'){
        tabela[txt[i]]++;
        i++;
    }//Printar nossos caracteres e sua frequencia
    cout << "Tabela de frequencia: \n";
    for(i = 0; i < TAM; i++){
        if(tabela[i] > 0){
            printf("\tCaractere: %c  Frequencia: %d\n", i, tabela[i]);
        }
    }
}
priority_queue<Huffman*, vector<Huffman*>, comparador_personalizado> cria_fila(vector<int>& tabela){
    priority_queue<Huffman*, vector<Huffman*>, comparador_personalizado> fila;
    for(int i = 0; i < TAM; i++){
        if(tabela[i] > 0){
            Huffman *novo = new Huffman(static_cast<char>(i), tabela[i]);
            fila.push(novo);
        }
    }
    return fila;
}
Huffman  *montar_arvore(priority_queue<Huffman*, vector<Huffman*>, comparador_personalizado> fila){
    while (fila.size() > 1)
    {   
        Huffman *no1 = fila.top();
        fila.pop();
        Huffman *no2 = fila.top();
        fila.pop();

        Huffman *novo = new Huffman('+', no1->frequencia + no2->frequencia);
        novo->esq = no1;
        novo->dir = no2;

        fila.push(novo);
    }
    return fila.top();
    
}
void gerar_dicionario(Huffman *raiz, string caminho, unordered_map<char, string> &dicionario){
    if(raiz->esq == nullptr && raiz->dir == nullptr){
        dicionario[raiz->caractere] = caminho;
    }else{
        gerar_dicionario(raiz->esq, caminho + "0", dicionario);
        gerar_dicionario(raiz->dir, caminho + "1", dicionario);
    }
}
string codificar(string txt, unordered_map<char, string> &dicionario){
    string codigo;
    for(char c: txt){
        codigo += dicionario[c];
    }return codigo;
}
string decodificar(string codigo, Huffman *raiz){
    string decodificado;
    Huffman *aux = raiz;

    for(char b: codigo){
        if(b == '0'){
            aux = aux->esq;
        }else{
            aux = aux->dir;
        }

        if(aux->esq == nullptr && aux->dir == nullptr){
            decodificado += aux->caractere;
            aux = raiz;
        }
    }
    return decodificado;
}