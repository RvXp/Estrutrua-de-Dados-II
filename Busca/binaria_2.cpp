#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;
    
int main(){
    //random_device seed;
    mt19937 mt(static_cast<unsigned int>(time(0)));
    uniform_int_distribution<int> dist(1, 100);

    const int size = 100;
    vector<int> my_array;
    
    int num, count = 1;
    
    for(int i = 0; i < size; i++){
        my_array.push_back(dist(mt));
    }

    sort(my_array.begin(), my_array.end());
    for(int i = 0; i < size; i++){
        cout << my_array[i] << " ";
    }
    
    cout << "\nDigite o numero que deseja buscar: ";
    cin >> num;

    int head = 0;
    int tale = my_array.size() - 1;
    int middle = 0;
    bool flag = false;
    while(head <= tale){
        middle = static_cast<int>((tale+head)/2);
        if(my_array[middle] == num){
            cout << "Valor encontrado nas posicoes: ";
            while(my_array[middle - 1] == num){
                middle--;
            }
            while(my_array[middle] == num){
                cout << middle << " ";
                middle++;
            }
            cout << "\nForam feitas " << count << " verificacoes!";
            flag = true;
            break;
        }else if(my_array[middle] > num){
            tale = middle - 1;
            count++;
        }else{
            head = middle + 1;
            count++;
        }
    }
    if(flag == false){
        cout << "Valor " << num <<  " nao encontrado!";
    }
}