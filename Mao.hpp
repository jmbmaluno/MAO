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

    typedef struct{
        float d;
        int validos;
        int total;
    } Densidade;

    Densidade densidade(int i, int j, int validos = 0, int total = 0){
        
        //Contando a qtde de elementos validos no vetor + 1 (que é o elemento que eu quero inserir)
        int qtde_validos = 1;
        int qtde_total = 0;

        if(validos != 0 && total != 0){
            qtde_validos = validos;
            qtde_total = total;
        }

        for(int k = i; k <= j; k++){
            if(vetor[k].valido){
                qtde_validos++;
            }

            qtde_total++;
        }

        return {(float)qtde_validos/qtde_total, qtde_validos, qtde_total};
    
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
    

    void inserir(int k, int profundidade, int pos_filho = 0, int qtde_validos = 0, int qtde_total = 0, int ant = 0){
        int n = this->size();

        //Se tá tentando inserir na folha
        if(profundidade == log(n)){

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


            //Vou incluir na folha do anterior
            int folha = ant/log(n);

            int qtde_por_folha = n/log(n);

            //Calculando a posição que folha começa e termina
            int pos_inicial = qtde_por_folha*folha;

            
            int pos_final = pos_inicial + qtde_por_folha-1;

            //Calculando a densidade do intervalo
            Densidade dens = densidade(pos_inicial, pos_final);


            if(dens.d <= (3*log(n) + profundidade) / (4 * log(n))){
                rebalancear(vetor, pos_inicial, pos_final, k, ant);
            }
            else{
                inserir(k, profundidade-1, folha, dens.validos, dens.total, ant);
            }

           
        }
        else{
            if(profundidade >= 0){
                //Se meu filho é par, então tenho que fazer o scan para direita
                //Se meu filho é impar, então tenho que fazer o scan para esquerda

                int no = pos_filho >> 1;
                int pos_inicial = no * 2 * qtde_total;;
                int pos_final = pos_inicial + (2*qtde_total) -1;

                int inicial_filho = pos_filho * qtde_total;
                int final_filho = inicial_filho + qtde_total - 1;

                Densidade dens;

                //Caso do filho par
                if(pos_filho % 2 == 0){
                    dens = densidade(final_filho + 1,pos_final, qtde_validos, qtde_total);
                }

                //Caso do filho impar
                else{
                    dens = densidade(pos_inicial, inicial_filho - 1, qtde_validos, qtde_total);
                }

                if(dens.d <= (float)(3*log(n) + profundidade) / (4 * log(n))){
                    rebalancear(vetor, pos_inicial, pos_final, k, ant);
                }

                else{
                    inserir(k, profundidade-1, no, dens.validos, dens.total, ant);
                }
            }

            else{
                len = 2*len;
                altura = log(len);
                Elemento* vetor_auxiliar = new Elemento[len];

                for(int i = 0; i < (len/2); i++){
                    vetor_auxiliar[i] = vetor[i];
                }

                //delete [] vetor;

                rebalancear(vetor_auxiliar, 0, len-1, k, ant);

                vetor = vetor_auxiliar;
            }
        }

    }

    void teste(){
        imprimir2(vetor, 0, len-1);
    }

};


/*
FALTA:
- Adicionar options no inserir. Options no profundidade e no pos_filho
- Falta subir na árvore
*/
#endif