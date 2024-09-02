#include <iostream>
using namespace std;

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

    typedef struct{
        int chave;
        bool valido;
    } Elemento;
    
    typedef struct{
        float d;
        int qtde_elementos;
        int qtde_validos;
    } Densidade;


    Elemento* vetor;
    int len;


    Densidade densidade(int i, int f){
        int qtde_elementos = 0;
        int qtde_validos = 0;

        for (int j = i; j <= f; j++){
            qtde_elementos++;

            if(vetor[j].valido){
                qtde_validos++;
            }
        }

        return {qtde_validos/qtde_elementos, qtde_elementos, qtde_validos};
    }


    void rebalancear(int i, int f, Densidade d, int k){
        Elemento fila = new Elemento[d.qtde_validos];
        int pos_fila = 0;

        for (j = i; j <= f; j++){
            if(vetor[j].valido){
                fila[pos_fila] = vetor[j];
                pos_fila++;
            }
        }

        //tenho que ver como definir o intervalo a partir do espaço total e qtde de elementos já validos
        int intervalo = ;
    }

    public:

    Mao(){
        vetor = new Elemento[2];

        vetor[0] = {0, false};
        vetor[1] = {0, false};
        len = 2;
    }

    int size(){
        return len;
    }

    void imprimir(){
        for(int i = 0; i < this->size(); i++){
            if(vetor[i].valido){
                cout << vetor[i].chave;
            }
        }

        cout << "\n";
    }

    Elemento get(int pos){
        return vetor[pos];
    }

    int suc(int k){
        int i = 0;
        
        while(i < this->size() && !vetor[i].valido && vetor[i].chave <= k){
            i++;
        }



        if(i < this->size()){
            return i; 
        }

        return -1;

    }

    void incluir(int k, int profundidade){

        int s = suc(k);
        if (s == -1){
            vetor[0] = {k, true};
        }

        else{
            int l = log(this->size());
            int intervalo = s / l;
            
            //Densidade deve receber um intervalo e diz a densidade
            //Densidade = n° elementos armazenados / qtde de posições do vetor
            Densidade d = densidade(intevalo * l, (intervalo+1) * l - 1);

            //Poderia colocar a densidade para retornar logo os elementos contados e o total de elementos
            //pra facilitar na hora de rebalancear os elementos
            if(d.d <= 3/4 + 1/4*d/profundiade){
                rebalancear(intervalo*l, (intervalo+1)*l -1, d, k);
            }

        }
    }

};