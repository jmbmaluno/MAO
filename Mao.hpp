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
        float qtde_elementos;
        float qtde_validos;
    } Densidade;


    Elemento* vetor;
    int len;
    int altura;


    Densidade densidade(int i, int f){
        float qtde_elementos = 0;
        float qtde_validos = 0;

        for (int j = i; j <= f; j++){
            qtde_elementos++;

            if(vetor[j].valido){
                qtde_validos++;
            }
        }

        return {(qtde_validos+1)/qtde_elementos, qtde_elementos, qtde_validos};
    }


    void rebalancear(int i, int f, Densidade d, int k){

        int qtde_v = (int)d.qtde_validos;
        Elemento* fila = new Elemento[qtde_v];
        int pos_fila = 0;

        for (int j = i; j <= f; j++){
            if(vetor[j].valido){
                fila[pos_fila] = vetor[j];
            }
        }

    
        for(int j = i; j <= f; j++){
            if(pos_fila < d.qtde_validos){
                vetor[j] = fila[pos_fila];
                pos_fila++;
            }
            else{
                vetor[j] = {0,false};
            }
        }

        vetor[qtde_v] = vetor[qtde_v-1];
        vetor[qtde_v-1] = {k, true};

        delete[] fila;
    }


    void preencher_folha(int i, Elemento* fila, int& pos_fila, int qtde_por_folha){
        int pos_inicial = log(this->size()) * i;

        while(qtde_por_folha > 0){
            vetor[pos_inicial] = fila[pos_fila];
            pos_fila++;
            pos_inicial++;
            qtde_por_folha--;
        }
    }

    public:

    Mao(){
        vetor = new Elemento[2];

        vetor[0] = {0, false};
        vetor[1] = {0, false};
        len = 2;
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
            Densidade d = densidade(intervalo * l, (intervalo+1) * l - 1);

            //Poderia colocar a densidade para retornar logo os elementos contados e o total de elementos
            //pra facilitar na hora de rebalancear os elementos
            if(d.d <= 3/4 + 1/4*profundidade/altura){
                rebalancear(intervalo*l, (intervalo+1)*l -1, d, k);
            }

            else{
                if(profundidade < 0){
                    cout << "tive que vim aqui e fica por isso mermo\n";

                    //Contar quantos elementos tem e guardar em uma fila
                    int qtde_validos = 0;

                    for (int j = 1; j < len; j++){
                        if(vetor[j].valido){
                            qtde_validos++;
                        }
                    }                 
                    
                    Elemento* fila = new Elemento[qtde_validos];
                    int pos = 0;

                    for(int j = 1; j < len; j++){
                        if(vetor[j].valido){
                            fila[pos] = vetor[j];
                            pos++;
                        }
                    }

                    //Dobrar o tamanho do vetor
                    delete[] vetor;
                    len = 2*len;
                    vetor = new Elemento[len];
                    altura = log(len);

                    //Dividir a quantidade de elementos pela quantidade de folhas
                    int qtde_folhas = len/log(len);
                    int qtde_por_folha = qtde_validos/qtde_folhas;
                    
                    //Colocar cada quantidade em cada folha
                    int pos_fila = 0;

                    for(int i = 0; i < qtde_folhas; i++){
                        preencher_folha(i, fila, pos_fila, qtde_por_folha);
                    }

                    delete[] fila;
                }

                else{
                    incluir(k, profundidade - 1);
                }
            }

        }
    }

    void teste(){
        rebalancear(0,1,{0,0,1},2);
    }
};