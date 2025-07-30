#include <stdio.h>
int mult(int n, int m){
    if(m == 1){
        return;
    }else{
        n += mult(n, m-1);
    }
    return n;
}

int main(){
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    mult(n, m);
    int res = mult(n, m);
    printf("%d", res);
}