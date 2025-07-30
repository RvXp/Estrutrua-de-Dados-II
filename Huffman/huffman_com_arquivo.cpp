// BIBLIOTECAS
#include <iostream> // basica para entrada e saida em console
#include <string> // para manipulação de string (atraves de uma classe string)
#include <vector> // para implementação de vetores dinamicos
#include <queue> // para fila dinamica
#include <unordered_map> // que implementa mapas (tabelas hash)
#include <fstream> // para manipulação de arquivos
#include <bitset> // para manipular sequencia de bits

#define TAM 256 
using namespace std; // permite abreviar o codigo e evitar a utilização do std::

typedef struct huffman // struct que define os Nós da arvore
{
    char caractere;
    int frequencia;
    huffman *esq, *dir;

    // Construtor
    huffman(char c, int f, huffman *e, huffman *d) : caractere(c), frequencia(f), esq(e), dir(d) {}
} Huffman;

struct comparador_personalizado // struct utilizado para definir o tipo de ordenação da fila
{
    bool operator()(const Huffman *a, const Huffman *b)
    {
        return a->frequencia > b->frequencia;
    }
};

void ler_arquivo(string &conteudo);
void preencher_tabela(string txt, vector<int> &tabela);
priority_queue<Huffman *, vector<Huffman *>, comparador_personalizado> cria_fila(vector<int> &tabela);
Huffman *montar_arvore(priority_queue<Huffman *, vector<Huffman *>, comparador_personalizado> fila);
void gerar_dicionario(Huffman *raiz, string caminho, unordered_map<char, string> &dicionario);
string codificar(string txt, unordered_map<char, string> &dicionario);
void criar_arquivo_compactado(string &codigo, Huffman *arvore);
void escrever_arvore(Huffman *raiz, ofstream &arquivo);
void criar_arquivo_descompactado(string codigo);
string decodificar(string codigo, Huffman *raiz);
Huffman *ler_arvore(ifstream &arquivo);

void main()
{
    string txt;     // lê um arquivo txt
    ler_arquivo(txt);

    vector<int> tabela(TAM, 0); // cria a tabela de frequencia 
    preencher_tabela(txt, tabela);

    priority_queue<Huffman *, vector<Huffman *>, comparador_personalizado> fila = cria_fila(tabela); // cria a fila ordenada (baseada na frquencia em ordem crescente)
    Huffman *arvore;
    arvore = montar_arvore(fila); // cria minha arvore de Huffman

    unordered_map<char, string> dicionario; // cria um dicionario percorrendo minha arvore
    gerar_dicionario(arvore, "", dicionario);

    string codigo = codificar(txt, dicionario); // cria uma sequencia de bit reduzida do meu texto baseado no dicionario
    cout << "Codificado = " << codigo;

    criar_arquivo_compactado(codigo, arvore); // cria um arquivo compactado, contendo a sequencia de bits armazenado na variavel codigo, e "codifica" a arvore para ser enviada no arquivo

    criar_arquivo_descompactado(codigo); // Cria o arquivo descompactado

    //return 0;
}

// LER O ARQUIVO A SER COMPACTADO
void ler_arquivo(string &conteudo)
{
    ifstream arquivo("teste.txt");
    if (arquivo.is_open())
    {
        char caractere;
        while (arquivo.get(caractere))
        {
            conteudo += caractere;
        }
        arquivo.close();
    }
    else
    {
        cout << "Erro ao abrir aquivo no procedimento ler_arquivo";
    }
}

// TABELA DE FRQUENCIA
void preencher_tabela(string txt, vector<int> &tabela)
{
    int i = 0;
    while (txt[i] != '\0')
    {
        tabela[txt[i]]++;
        i++;
    }
    cout << "Tabela de frequencia: \n";
    for (i = 0; i < TAM; i++)
    {
        if (tabela[i] > 0)
        {
            printf("\tCaractere: %c  Frequencia: %d\n", i, tabela[i]);
        }
    }
}

// FILA ORDENADA
priority_queue<Huffman *, vector<Huffman *>, comparador_personalizado> cria_fila(vector<int> &tabela)
{
    priority_queue<Huffman *, vector<Huffman *>, comparador_personalizado> fila;
    for (int i = 0; i < TAM; i++)
    {
        if (tabela[i] > 0)
        {
            Huffman *novo = new Huffman(static_cast<char>(i), tabela[i], nullptr, nullptr);
            fila.push(novo);
        }
    }
    return fila;
}

// ARVORE DE HUFFMAN
Huffman *montar_arvore(priority_queue<Huffman *, vector<Huffman *>, comparador_personalizado> fila)
{
    while (fila.size() > 1)
    {
        Huffman *no1 = fila.top();
        fila.pop();
        Huffman *no2 = fila.top();
        fila.pop();

        Huffman *novo = new Huffman('+', no1->frequencia + no2->frequencia, no1, no2);
        fila.push(novo);
    }
    return fila.top();
}

// DICIONARIO 
void gerar_dicionario(Huffman *raiz, string caminho, unordered_map<char, string> &dicionario)
{
    if (raiz->esq == nullptr && raiz->dir == nullptr)
    {
        dicionario[raiz->caractere] = caminho;
    }
    else
    {
        gerar_dicionario(raiz->esq, caminho + "0", dicionario);
        gerar_dicionario(raiz->dir, caminho + "1", dicionario);
    }
}

// TEXTO CODIFICADO
string codificar(string txt, unordered_map<char, string> &dicionario)
{
    string codigo;
    for (char c : txt)
    {
        codigo += dicionario[c];
    }
    return codigo;
}

// CRIA UM ARQUIVO COMPACTADO
void criar_arquivo_compactado(string &codigo, Huffman *arvore) // Cria o arquivo compactado
{
    ofstream arquivo("compactado.wg", ios::binary);
    if (arquivo.is_open())
    {
        escrever_arvore(arvore, arquivo); // ESCREVE A ARVORE EM BINARIO, PARA SER ENVIADA JUNTO AO ARQUIVO, COLOCA BEM NO COMECINHO DELE

        bitset<8> byte;
        for (char bit : codigo)
        {
            byte <<= 1;
            byte[0] = (bit = '1') ? 1 : 0;
            if (byte.count() == 8)
            {
                arquivo.write(reinterpret_cast<const char *>(&byte), 1);
                byte.reset();
            }
        }
        if (byte.count() > 0)
        {
            arquivo.write(reinterpret_cast<const char *>(&byte), 1);
        }
        arquivo.close();
        cout << "\n\n\tArquivo compactado com sucesso!";
    }
    else
    {
        cout << "\n\n\tErro ao criar arquivo compactado";
    }
}

// ESCREVE A ARVORE
void escrever_arvore(Huffman *raiz, ofstream &arquivo)
{
    if (raiz->esq == nullptr && raiz->dir == nullptr)
    {
        arquivo.write("1", 1); // indica se o no é folha, ou seja, um caractere
        arquivo.write(reinterpret_cast<const char *>(&(raiz->caractere)), 1);
    }
    else
    {
        arquivo.write("0", 1); // indica se o no é um no intermediario
        escrever_arvore(raiz->esq, arquivo);
        escrever_arvore(raiz->dir, arquivo);
    }
}

// ARQUIVO COMPACTADO
void criar_arquivo_descompactado(string codigo)
{
    ofstream arquivo("descompactado.txt");
    if (arquivo.is_open())
    {
        ifstream arquivo_compactado("compactado.wg", ios::binary);
        Huffman *arvore_compactada = ler_arvore(arquivo_compactado);

        string decodificado = decodificar(codigo, arvore_compactada);

        arquivo << decodificado;
        arquivo.close();
        cout << "\n\n\tArquivo descompactado com sucesso!";
    }
    else
    {
        cout << "\n\n\tErro ao criar arquivo descompacta.txt";
        exit(EXIT_FAILURE);
    }
}

//TEXTO DECODIFICADO
string decodificar(string codigo, Huffman *raiz)
{
    string decodificado;
    Huffman *aux = raiz;

    for (char b : codigo)
    {
        if (b == '0')
        {
            aux = aux->esq;
        }
        else
        {
            aux = aux->dir;
        }

        if (aux->esq == nullptr && aux->dir == nullptr)
        {
            decodificado += aux->caractere;
            aux = raiz;
        }
    }
    return decodificado;
}

// LE A ARVORE QUE ESTA JUNTO AO ARQUIVO
Huffman *ler_arvore(ifstream &arquivo)
{
    char indicador;
    arquivo.read(&indicador, 1);

    if (indicador == '1')
    {
        char caractere;
        arquivo.read(&caractere, 1);
        return new Huffman(caractere, 0, nullptr, nullptr);
    }
    else
    {
        Huffman *esq = ler_arvore(arquivo);
        Huffman *dir = ler_arvore(arquivo);
        return new Huffman('+', 0, esq, dir);
    }
}