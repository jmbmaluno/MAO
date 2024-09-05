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

    float densidade(int i, int j){
        
        //Contando a qtde de elementos validos no vetor + 1 (que é o elemento que eu quero inserir)
        int qtde_validos = 1;
        int qtde_total = 0;
        for(int k = i; k <= j; k++){
            if(vetor[k].valido){
                qtde_validos++;
            }

            qtde_total++;
        }

        return (float)qtde_validos/qtde_total;
    
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
    

    void inserir(int k, int profundidade, int pos_filho){
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
            cout << "folha: " << folha << "\n";

            int qtde_por_folha = n/log(n);

            //Calculando a posição que folha começa e termina
            int pos_inicial = qtde_por_folha*folha;

            
            int pos_final = pos_inicial + qtde_por_folha-1;

            //Calculando a densidade do intervalo
            float dens = densidade(pos_inicial, pos_final);
            cout << "dens: " << dens << "\n";


            cout << "inicial: " << pos_inicial << " final: " << pos_final << "\n";
            
            cout << "ant: "  << ant << "\n";

            if(dens <= (3*log(n) + profundidade) / (4 * log(n))){
                rebalancear(vetor, pos_inicial, pos_final, k, ant);
            }
            else{
                cout << "folha encheu, mané\n";

            }

           
        }

    }

};

#endif