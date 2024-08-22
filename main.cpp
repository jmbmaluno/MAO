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
    
    int contar_valores(int no){
        int cont = i.qtde;
        int h = log(this->size());

       
        for(int i = no*h; i < no*h + h; i++){
            if(vetor[i].b) cont++;
        }


        return cont;
    }


    public: 

    //Construtor - Começando o vetor com duas posições. 
    //Quando for necessário criar um vetor com o dobro do tamanho do anterior
    Mao(){
        vetor = new Valor[2];

        vetor[0] = {0, false};
        vetor[1] = {2, true};
        len = 2;
    }

    //Retorna o tamanho do vetor atualmente
    int size(){
        return len;
    }


    void inserir(int k){
        //Fazer busca binária no vetor
        //Mas como faz quando vc encontra um espaço vazio?
        //ACHO que posso olhar a vizinhança 
    }

    //Imprimir em ordem apenas os valores cujo booleano é diferente de false
    void imprimir(){
        for (int i = 0; i < this->size(); i++){
            if(vetor[i].b){
                cout << vetor[i].chave << "\n";
            }
        }

    }

    void teste(){
        cout << contar_valores(0) << "\n";
    }
    

};

int main(){

    Mao m;

    m.teste();
}
