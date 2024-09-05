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

//Calcula 2^k
int pow_2(int k){
    int res = 1;

    while(k > 0){
        res = res << 1;
        k--;
    }

    return res;
}

class Mao{

    Elemento* vetor;
    int len;
    int altura;

    int densidade(int i, int j){
        return 1;
    }

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
    

    void inserir(int k, int profunidade, int pos_filho){
        int n = this->size();

        //Se tá tentando inserir na folha
        if(profunidade == log(n)){

            //int qtde_folhas = n / log(n);

            //posição do elemento anterior
            int ant = 0;

            //posição do elemento sucesosr
            int i = 0;

            
            //Procurar entre quais posições o elemento vai ficar
            //Logo, vou procurar enquanto o elemento visto for invalido ou enquanto ele for valido e menor do que a chave que quero inserir
            while(i < n && (vetor[i].valido == false || (vetor[i].valido && vetor[i].chave < k))){
                if(vetor[i].valido && vetor[i].chave < k && vetor[i].chave>= vetor[ant].chave){
                    ant = i;
                }

                i++;
            }

            if(i >= n){
                cout << "cheguei até o final\n";
                cout << "ant: " << ant << "\n";

                //Vou incluir na folha do anterior
                int folha = ant/log(n);

                //Calculando a posição que folha começa e termina
                int pos_inicial = pow_2(folha);

                int qtde_por_folha = n/log(n);
                int pos_final = pos_inicial + qtde_por_folha-1;

                //Calculando a densidade do intervalo
                int dens = densidade(pos_inicial, pos_final);
            }
            else{
                cout << "não cheguei ao final e o elemento vai ficar entre " << ant << " e " << i << "\n";
            }
        }

    }

};

#endif