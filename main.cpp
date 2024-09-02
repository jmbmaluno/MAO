#include "Mao.hpp"


/*
IDEIA: guardar os maiores valores de cada folha e a posição deles no subspaço da folha para facilitar a busca de onde os elementos devem estar
guardando os maiores valores eu posso fazer uma busca binária neles para saber onde o valor buscado deveria estar.
*/

/*
class Mao{

    //Para marcar quais posições do vetores foram efetivamente preenchidas pelo usuário e quais são apenas lixo de memória
    //Vou fazer um vetor de uma struct Valor, que terá o valor da inclusão propriamente dito e um valor boolenado
    //Esse valor booleando é para indicar se foi feita ou não uma inclusão naquela posição de memória.
    //Nesse caso, as remoçoes se resumem a apenas trocar o valor booleano do elemento do vetor (claro, obedecendo as propriedades da MAO)
    typedef struct{
        int chave;
        bool b;
    } Valor;
    
    typedef struct {
        Valor valor;
        int pos;
    } Max;

    Valor* vetor;
    Valor* max_valores;
    int len;

    
    
    int contar_valores(int no){
        int cont = i.qtde;
        int h = log(this->size());

       
        for(int i = no*h; i < no*h + h; i++){
            if(vetor[i].b) cont++;
        }


        return cont;
    }

    //Não sei como fazer a busca ainda
    int buscar(int k, int pos){
        int h = log(this->size());

        maior = k;

        for(int i = pos * h; i < pos * h + h; i++){
            if(vetor[i].b){
                if(vetor[i].chave == k) return i;
                if(vetor[i].chave > k) maior = vetor[i].chave;
            }
        }


    }

    public: 

    //Construtor - Começando o vetor com duas posições. 
    //Quando for necessário criar um vetor com o dobro do tamanho do anterior
    Mao(){
        vetor = new Valor[2];

        vetor[0] = {0, false};
        vetor[1] = {0, false};
        len = 2;

        max_valores = new Max[2];
        max_valores[0] = {{0,false}, -1}
        max_valores[1] = {{0,false}, -1}
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
*/

int main(){

    Mao m;

    m.imprimir();
}
