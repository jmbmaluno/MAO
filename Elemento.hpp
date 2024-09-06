#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <iostream>

using namespace std;

//Como o vetor vai ter buracos. Para eu saber oq é valido ou não, fiz uma struct
//Vou contar como lixo de memoria aquilo que tiver bool = false
typedef struct{
    int chave;
    bool valido;
} Elemento;

//Coloca o vetor com os elementos espaçados adequadamente
void rebalancear(Elemento* vetor, int j, int l, int k = -1, int ant = -2){
    int qtde_validos = 0;

    for(int i = j; i <= l; i++){
        if(vetor[i].valido)
            qtde_validos++;
    }

    Elemento* fila_auxiliar;
    
    if(ant == -2){
        fila_auxiliar = new Elemento[qtde_validos];
    }
    else{
        fila_auxiliar = new Elemento[qtde_validos+1];
    }

    int pos_fila = 0;

    if(ant == -1){
        fila_auxiliar[pos_fila] = {k, true};
        pos_fila++;
    }

    for(int i = j; i <=l; i++){
        if(vetor[i].valido){
            fila_auxiliar[pos_fila] = vetor[i];
            pos_fila++;
            vetor[i].valido = false;
        }

        if(i == ant){
            fila_auxiliar[pos_fila] = {k, true};
            pos_fila++;
        }
    }
    
    //Usando a ideia do Bresenham's line algorithm
    pos_fila = 0;
    int pos;

    if(qtde_validos == 0){
        if(ant != -2){
            vetor[j] = fila_auxiliar[0];
        }
    }
    else{
        for(int passo = 0; passo <= (qtde_validos); passo++){
            pos = j + passo*(l-j)/(qtde_validos);

            vetor[pos] = fila_auxiliar[pos_fila];

            pos_fila++;
        }
    }

    delete[] fila_auxiliar;
}


#endif
