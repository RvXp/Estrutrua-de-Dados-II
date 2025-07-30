#include <iostream>
#include <random>
#include <vector>

using namespace std;

int main(){
    random_device seed;
    mt19937 mt(seed());
    uniform_int_distribution<int> dist(1, 100);

    const int size = 100;
    vector<int> my_array;
    int num, count = 1, j;

    for(int i = 0; i < size; i++){
        my_array.push_back(dist(mt));
    }

    for(int i = 0; i < size; i++){
        cout << my_array[i] << " ";
    }

    cout << "Digite o numero que deseja buscar: ";
    cin >> num;

    for(int i = 0; i < size; i++){
        if (my_array[i] == num){
            cout << "Valor encontrado na posicao " << i << " , foram realuzadas " << count << " comparacoes\n";
            break;
        }else{
            count++;
        }
    }
    count = 0;

    for(j = 0; j < size; j++){
        if(my_array[j] == num){
            count++;
        }
    }
    cout << "O valor apareceu " << count << " vezes e foram realizadas " << j << " comparacoes";
    return 0;
}