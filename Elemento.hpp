#ifndef ELEMENTO_H
#define ELEMENTO_H

#include <iostream>

using namespace std;

typedef struct{
    int chave;
    bool valido;
} Elemento;

void imprimir(Elemento* v, int j, int k){
    for(int i = j; i <= k; i++){
        cout << "Chave: " << v[i].chave << " valido = " << v[i].valido << "\n";
    }
}

void rebalancear(Elemento* vetor, int j, int l){
    int qtde_validos = 0;

    for(int i = j; i <= l; i++){
        if(vetor[i].valido)
            qtde_validos++;
    }

    Elemento* fila_auxiliar = new Elemento[qtde_validos];
    int pos_fila = 0;

    for(int i = j; i <=l; i++){
        if(vetor[i].valido){
            fila_auxiliar[pos_fila] = vetor[i];
            pos_fila++;
            vetor[i].valido = false;
        }
    }

    //Usando a ideia do Bresenham's line algorithm
    pos_fila = 0;
    int pos;

    for(int passo = 0; passo <= (qtde_validos-1); passo++){
        pos = j + passo*(l-j)/(qtde_validos-1);
        
        vetor[pos] = fila_auxiliar[pos_fila];
        pos_fila++;
    }

    delete fila_auxiliar;
}


#endif
