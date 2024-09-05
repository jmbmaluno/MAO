#ifndef MAO_H
#define MAO_H

#include "Elemento.hpp"



//Calcula o piso do log de k na base 2
int log(int k){
    int res = 0;

    while (k != 1){
        k = k >> 1;
        res++;
    }

    return res;

}


class Mao{

    Elemento* vetor;
    int len;
    int altura;

    public:

    Mao(){
        vetor = new Elemento[2];

        vetor[0] = {0, false};
        vetor[1] = {0, false};
        len = 2;
        altura = log(len);
    }

    Mao(Elemento* v, int l){
        vetor = v;
        len = l;
        altura = log(len);
    }

    int size(){
        return len;
    }

    void imprimir(){
        for(int i = 0; i < this->size(); i++){
            if(vetor[i].valido){
                cout << vetor[i].chave << " ";
            }
        }

        cout << "\n";
    }

};

#endif