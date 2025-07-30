#include <iostream>
//#include <conio.h>
using namespace std;

struct tree
{
    int num;
    tree *esq, *dir;    
};

tree* insert(tree *aux, int num){
    if (aux == NULL){
        aux = new tree();
        aux->num = num;
        aux->esq = NULL;
        aux->dir = NULL;
    }else if (num < aux->num){
        aux->esq =  insert(aux->esq, num);
    }else aux->dir = insert(aux->dir, num);
  return aux;
}

tree* remove(tree *aux, int num){
    tree *p1, *p2;
    if(aux->num == num){
        if(aux->esq == aux->dir){
            delete aux;
            return NULL;
        }else if(aux->esq == NULL){
            p1 = aux->dir;
            delete aux;
            return p1;
        }else if(aux->dir == NULL){
            p1 = aux->esq;
            delete aux;
            return p1;
        }else{
            p2 = aux->dir;
            p1 = aux->dir;
            while(p1->esq != NULL){
                p1 = p1->esq;
            }
            p1 -> esq = aux->esq;
            delete aux;
            return p2;
        }
    }else if(aux->num < num){
        aux->dir = remove(aux->dir, num);
    }else aux->esq = remove (aux->esq, num);
    return aux;
}

int consult(tree *aux, int num, int flag){
    if(aux != NULL && flag == 0){
        if(aux->num == num){
            flag = 1;
        }else if(num < aux->num){
            flag = consult(aux->esq, num, flag);
        }else flag = consult(aux->dir, num, flag);
    }return flag;
}

void in_order(tree *aux){
    if(aux != NULL){
        in_order(aux->esq);
        cout << aux->num << " ";
        in_order(aux->dir);
    }
}
void pre_order(tree *aux){
    if(aux != NULL){
        cout << aux->num << " ";
        pre_order(aux->esq);
        pre_order(aux->dir);
    }

}

void pos_order(tree *aux){
    if(aux != NULL){
        pre_order(aux->esq);
        pre_order(aux->dir);
        cout << aux->num << " ";
    }
}

int main(){
    tree *root = NULL;
    //tree *aux = NULL;
    int op, finded, num;
    do{
        cout << "MENU\n";
        cout << "(1) Inserir\n";
        cout << "(2) Consultar um nó\n";
        cout << "(3) em-ordem\n";
        cout << "(4) pré-ordem\n";
        cout << "(5) pós-ordem\n";
        cout << "(6) Excluir um nó\n";
        cout << "(0) Sair\n";
        cout << "Digite sua opção: ";
        cin >> op;
        while(op > 7 || op < 0){
            cout << "\nOpção invalida\n";
            cout << "Digite outra opção: ";
            cin >> op;
            //scanf("%d", &op);
        }
        if (op == 1){
            cout << "Digite o numero a ser inserido: ";
            cin >> num;
            root = insert(root, num);
            cout << "Numero inserido na arvore";
        }else if (op == 2){
            if (root == NULL){
                cout << "Arvore vazia!";
            }else{
                cout << "Digite o numero a ser buscado";
                cin >> num;
                finded = 0;
                finded = consult(root, num, finded);
                if(finded == 0){
                    cout << "Numero não encontrado";
                }else{
                    cout << "Numero encontrado";
                }
            }
        }else if (op == 3){
            if(root == NULL){
                cout << "Arvore vazia";
            }else{
                cout << "Listando todos os elemente:\n";
                in_order(root);
            }
        }else if (op == 4){
            if(root == NULL){
                cout << "Arvore vazia";
            }else{
                cout << "Listando todos os elemente:\n";
                pre_order(root);
            }
        }else if (op == 5){
            if(root == NULL){
                cout << "Arvore vazia";
            }else{
                cout << "Listando todos os elemente:\n";
                pos_order(root);
            }
        }else if (op == 6){
            if (root == NULL)
            {
                cout << "Arvore vazia";
            }else{
                cout << "Digite o numero que deseja remover";
                cin >> num;
                finded = 0;
                finded = consult(root, num, finded);
                if(finded == 0){
                    cout << "Numero não presente na arvore";
                }else{
                    root = remove(root, num);
                    cout<<"Numero excluido da arvore";
                }
            }

        }

    }while(op != 0);

    return 0;
}