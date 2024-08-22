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

    //Para marcar quais posições do vetores foram efetivamente preenchidas pelo usuário e quais são apenas lixo de memória
    //Vou fazer um vetor de uma struct Valor, que terá o valor da inclusão propriamente dito e um valor boolenado
    //Esse valor booleando é para indicar se foi feita ou não uma inclusão naquela posição de memória.
    //Nesse caso, as remoçoes se resumem a apenas trocar o valor booleano do elemento do vetor (claro, obedecendo as propriedades da MAO)
    typedef struct{
        int chave;
        bool b;
    } Valor;

    Valor* vetor;
    int len;

    typedef struct {
        int direcao;
        int qtde;
    } Intevalo;
    
    int contar_valores(int no, int profundidade, Intervalo i){
        int cont = i.qtde;
        int h = log(this->size());

        int total_espaço = ( h - profundidade + 1) * h 

        int pos_inicio;

        if(i.direcao = 0){
            pos_inicio = no*h;
        }
        else{
            //cont = cont + contar_valores((no << 1) -1 * i.direcao, profundidade-1;  )
        }
    }

    
    /*
    int encontrar_pos(int k, int folha_atual, int target){
        int d = densidade(folha_atual, log(this->size()), {-1,0});
    }
    */

    public: 

    //Construtor - Começando o vetor com duas posições. 
    //Quando for necessário criar um vetor com o dobro do tamanho do anterior
    Mao(){
        vetor = new Valor[2];

        vetor[0] = {0, false};
        vetor[1] = {0, false};
        len = 2;
    }

    //Retorna o tamanho do vetor atualmente
    int size(){
        return len;
    }


    //Imprimir em ordem apenas os valores cujo booleano é diferente de false
    void imprimir(){
        for (int i = 0; i < this->size(); i++){
            if(vetor[i].b){
                cout << vetor[i].chave << "\n";
            }
        }

    }

    void incluir(int k){
        int folha_atual = 0; //guarda a folha em que estou
        int cont = 0;
        int n = this->size();
        int l = log(n);

        int target = -1; //pos que guarda o menor valor maior do quê k

        int i = 0; //iterador

        while(i < n){

            cont++;

            if(cont == l){
                folha_atual++;
            }

            if(vetor[i].b){

                if(vetor[i].chave >= k){
                    target = i;
                    i = n;
                }
            }

            i++;
        }

        //Depois dessa busca folha_atual marca a folha em que eu devo inserir o novo valor
        
        /*
        if(target == -1){
            cout << "fui até o final do vetor e n achei alguém maior\n";
            cout << folha_atual << "\n";
        }
        else{
            cout << "a posição " << target << " tem um valor maior ou igual ao que quero incluir e está na folha " << folha_atual << "\n";

        }
        */
        
        //Retorna a posição do vetor já redistribuido em que k deve ser incluido
        //int pos = encontrar_pos(k, folha_atual, target);

        //vetor[pos] = k;
    }

};

int main(){

    Mao m;

    m.incluir(3);
}
