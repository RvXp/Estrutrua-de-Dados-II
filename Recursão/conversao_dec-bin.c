#include <stdio.h>

int bin(int num){
    if(num < 1){
        return;
    }else{
        bin(num/2);
        printf("%d", num%2);        
    }
}

int main(){
    int num;
    printf("Digite um numero: ");
    scanf("%d", &num);
    bin(num);
}